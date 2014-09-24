#include <EEPROM.h>

//EEPROM data
#define PROGRAMMED			0
#define CARD_ADDRESS		1
#define PROGRAMMED_VALUE	128

//definition of slot id pins
#define D0  A2
#define D1  A0
#define D2  A1

//output pins definition
#define Y0	2
#define Y1	3
#define Y2	4
#define Y3	5
#define Y4	6
#define Y5	7
#define Y6	8
#define Y7	9

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

  //setup outputs
  pinMode(Y0, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(Y4, OUTPUT);
  pinMode(Y5, OUTPUT);
  pinMode(Y6, OUTPUT);
  pinMode(Y7, OUTPUT);

  //set outputs for the first time
  digitalWrite(Y0, HIGH);
  digitalWrite(Y1, HIGH);
  digitalWrite(Y2, HIGH);
  digitalWrite(Y3, HIGH);
  digitalWrite(Y4, HIGH);
  digitalWrite(Y5, HIGH);
  digitalWrite(Y6, HIGH);
  digitalWrite(Y7, HIGH);

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
      case SET_OUTPUT:
        setOutput();
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
      0x02, //discrete output card
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

void setOutput()
{
  if (address == myAddress)
  {
    int a = 0, b = Y0; //indexers
    //set each output according to data received
    while (b <= Y7)
    {
      digitalWrite(b, !bitRead(data[0], a));
      a++;
      b++;
    }
    OPLC_send(1, SET_OUTPUT, address, data); //dataSize, function, address, data
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
