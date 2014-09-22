/*************************************************************
*                     OPLC PROTOCOL                          *
*                                                            *
* The OpenPLC protocol stablishes the way that               *
* messages are sent from one board to another.               *
* These messages must obey the following format:             *
*                                                            *
* MESSAGE STRUCTURE                                          *
*  START | SIZE | FUNCTION | ADDRESS | DATA                  *
*                                                            *
* START    = 0x7E                                            *
* SIZE     = size of the DATA field (in bytes)               *
* FUNCTION = function to be executed                         *
* ADDRESS  = address of the target                           *
* DATA     = data sent or received 	                     *
*                                                            *
*                 FUNCTIONS | ARGUMENTS	        	     *
*  0x01 = ask for the card's type                            *
*  0x02 = change card address                                *
*  0x03 = read discrete inputs                               *
*  0x04 = set discrete outputs                               *
*  0x05 = error message                                      *
*                                                            *
**************************************************************
*/
#define OPLC_TIMEOUT			5
#define MAX_FUNCTION_NUMBER		0x05
#define MAX_DATA_SIZE			10

//OPLC functions
#define CARD_TYPE		0x01
#define CHANGE_ADDRESS	0x02
#define READ_INPUT		0x03
#define SET_OUTPUT		0x04
#define MSG_ERROR		0x05

void OPLC_send(byte dataSize, byte function, byte address, byte * data)
{
  byte header[4];
  header[0] = 0x7E; //start message
  header[1] = dataSize; //message size
  header[2] = function; //function code
  header[3] = address; //address

  //send the header first
  int i;
  for (i = 0; i < 4; i++)
  {
    Serial1.write(header[i]);
  }
  //send the data
  for (i = 0; i < dataSize; i++)
  {
    Serial1.write(data[i]);
  }

  //wait until all data is sent
  Serial1.flush();
}

boolean OPLC_receive(byte * dataSize, byte * function, byte * address, byte * data)
{
  long timeout;
  byte byteIndex = 0;
  byte message[MAX_DATA_SIZE];

  //start timeout counter
  timeout = millis();

  //enable receiving data through the bus
  digitalWrite(DE_PIN, LOW);

  //waiting for the start bit
  while (true)
  {
    if ((millis() - timeout) > OPLC_TIMEOUT)
    {
      //disable receiving data through the bus
      digitalWrite(DE_PIN, HIGH);
      delay(1);
      return (0); //no message received
    }
    if (Serial1.available())
    {
      if (Serial1.read() == 0x7E)
      {
        break; //the start bit was received. Get out of the loop.
      }
    }
  }

  timeout = millis(); //reset counter

  //getting message size
  while (true)
  {
    if ((millis() - timeout) > OPLC_TIMEOUT)
    {
      //disable receiving data through the bus
      digitalWrite(DE_PIN, HIGH);
      delayMicroseconds(500);
      return (0); //no message received
    }
    if (Serial1.available())
    {
      *dataSize = Serial1.read();
      if (*dataSize > MAX_DATA_SIZE) //maximum data size is 10 bytes
      {
        *function = 0x05; //error function
        //disable receiving data through the bus
        digitalWrite(DE_PIN, HIGH);
        delayMicroseconds(500);
        return (1); //received a message but with errors
      }
      break; //get out of the loop
    }
  }

  //getting message function
  while (true)
  {
    if ((millis() - timeout) > OPLC_TIMEOUT)
    {
      //disable receiving data through the bus
      digitalWrite(DE_PIN, HIGH);
      delayMicroseconds(500);
      return (0); //no message received
    }
    if (Serial1.available())
    {
      *function = Serial1.read();
      if (*function > MAX_FUNCTION_NUMBER) //wrong function
      {
        *function = 0x05; //error function
        //disable receiving data through the bus
        digitalWrite(DE_PIN, HIGH);
        delayMicroseconds(500);
        return (1); //received a message but with errors
      }
      break; //get out of the loop
    }
  }

  //getting address byte
  while (true)
  {
    if ((millis() - timeout) > OPLC_TIMEOUT)
    {
      //disable receiving data through the bus
      digitalWrite(DE_PIN, HIGH);
      delayMicroseconds(500);
      return (0); //no message received
    }
    if (Serial1.available()) //if received the address byte
    {
      *address = Serial1.read(); //read address
      break; //finish loop
    }
  }

  //getting data
  byteIndex = 0;
  while (byteIndex < *dataSize)
  {
    if ((millis() - timeout) > OPLC_TIMEOUT)
    {
      //disable receiving data through the bus
      digitalWrite(DE_PIN, HIGH);
      delayMicroseconds(500);
      return (0); //no message received
    }
    if (Serial1.available())
    {
      data[byteIndex] = Serial1.read();
      byteIndex++;
    }
  }

  //disable receiving data through the bus
  digitalWrite(DE_PIN, HIGH);
  delayMicroseconds(500);
  return (1); //message received with no errors
}
