#include <EEPROM.h>

//EEPROM data
#define PROGRAMMED			0
#define CARD_ADDRESS		1
#define PROGRAMMED_VALUE	128

//definition of slot id pins
#define D0  A2
#define D1  A0
#define D2  A1

//input pins definition
#define X0	2
#define X1	3
#define X2	4
#define X3	5
#define X4	6
#define X5	7
#define X6	8
#define X7	9

//definition of the BUS Enable pin
#define DE_PIN	A5

#include "OPLC_Protocol.h"

byte dataSize, function, address, data[MAX_DATA_SIZE];
byte myAddress = 0x01; //default address

int slotNumber = 0;

void setup()
{
  // initialize serial:
  Serial.begin(57600);
  //Serial.begin(115200);

  pinMode(DE_PIN, OUTPUT);

  // make the slot pins inputs:
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  //calculate slot number
  slotNumber = (4 * digitalRead(D2)) + (2 * digitalRead(D1)) + (1 * digitalRead(D0)); //get the slot number

  //setup inputs
  pinMode(X0, INPUT);
  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  pinMode(X3, INPUT);
  pinMode(X4, INPUT);
  pinMode(X5, INPUT);
  pinMode(X6, INPUT);
  pinMode(X7, INPUT);

  //verify if the address is already programmed
  if (EEPROM.read(PROGRAMMED) != PROGRAMMED_VALUE) //Blank EEPROM, must programm address on it for the first use
  {
    EEPROM.write(PROGRAMMED, PROGRAMMED_VALUE); //Sinalize that the EEPROM is now programmed
    EEPROM.write(CARD_ADDRESS, 0x01); //default card address
  }

  //read address
  myAddress = EEPROM.read(CARD_ADDRESS);
}

void loop()
{
  if (OPLC_receive(&dataSize, &function, &address, data)) //if received something
  {
    switch (function)
    {
      case CARD_TYPE:
        sendCardType();
        break;
      case CHANGE_ADDRESS:
        changeCardAddress();
        break;
      case READ_INPUT:
        sendInput();
        break;
      case MSG_ERROR:
        sendLastMsg();
        break;
      default:
        //sendErrorMsg();
        break;
    }
  }
}

void sendCardType()
{
  if (address == slotNumber) //the message is for me
  {
    byte dataResponse[2] =	{
      0x01, //discrete input card
      myAddress //actual card address
    };
    OPLC_send(2, CARD_TYPE, address, dataResponse); //dataSize, function, address, data
  }
}

void changeCardAddress()
{
  if (address == slotNumber)
  {
    if (data[0] > 0 && data[0] < 9) //new address validation
    {
      EEPROM.write(CARD_ADDRESS, data[0]); //update eeprom
      myAddress = data[0]; //update local variable

      //return a confirmation message
      OPLC_send(1, CHANGE_ADDRESS, address, data); //dataSize, function, address, data
    }
    else
    {
      OPLC_send(0, MSG_ERROR, address, 0); //dataSize, function, address, data
    }
  }
}

void sendInput()
{
  if (address == myAddress)
  {
    int a = 0, b = X0; //indexers
    byte dataResponse[1];
    while (b <= X7)
    {
      bitWrite(dataResponse[0], a, digitalRead(b)); //writes 0 or 1 to a specific bit inside dataResponse[0]
      a++;
      b++;
    }
    OPLC_send(1, READ_INPUT, address, dataResponse); //dataSize, function, address, data
  }
}

void sendErrorMsg()
{
  if (address == myAddress)
  {
    OPLC_send(0, MSG_ERROR, address, 0x00); //dataSize, function, address, data
  }
}

void sendLastMsg()
{
}
