#include "OpenPLC.h" //definitions
#include "Globals.h" //global variables
#include "OPLC_Protocol.h" //OPLC Protocol Library v0.1
#include "Cards_Comm.h" //Communication with the slave cards
#include "PC_Comm.h" //Communication with the PC Software
#include "Special_functions.h" //Ladder special functions

void ModbusInit()
{
  uint8_t mac[6], ip[4], gateway[4], subnet[4];
  int	index;
  if (EEPROM.read(PROGRAMMED) != PROGRAMMED_VALUE) //Blank EEPROM, must programm IP on it for the first use
  {
    EEPROM.write(PROGRAMMED, PROGRAMMED_VALUE); //Sinalize that the EEPROM is now programmed
    //SAVING MAC ADDRESS ON EEPROM
    EEPROM.write(MAC, 0x90); //First byte
    EEPROM.write(MAC + 1, 0xA2); //Second byte
    EEPROM.write(MAC + 2, 0xDA); //Third byte
    EEPROM.write(MAC + 3, 0x00); //Fourth byte
    EEPROM.write(MAC + 4, 0x51); //Fifth byte
    EEPROM.write(MAC + 5, 0x06); //Sixth byte
    //SAVING IP ON EEPROM
    EEPROM.write(IP, 192); //First byte
    EEPROM.write(IP + 1, 168); //Second byte
    EEPROM.write(IP + 2, 123); //Third byte
    EEPROM.write(IP + 3, 134); //Fourth byte
    //SAVING GATEWAY ON EEPROM
    EEPROM.write(GATEWAY, 192); //First byte
    EEPROM.write(GATEWAY + 1, 168); //Second byte
    EEPROM.write(GATEWAY + 2, 123); //Third byte
    EEPROM.write(GATEWAY + 3, 254); //Fourth byte
    //SAVING SUBNET ON EEPROM
    EEPROM.write(SUBNET, 255); //First byte
    EEPROM.write(SUBNET + 1, 255); //Second byte
    EEPROM.write(SUBNET + 2, 255); //Third byte
    EEPROM.write(SUBNET + 3, 0); //Fourth byte
  }
  //Reading MAC
  for (index = 0; index < 6; index++)
  {
    mac[index] = EEPROM.read(index + 1);
  }
  //Reading IP, GATEWAY, SUBNET at the same time
  for (index = 0; index < 4; index++)
  {
    ip[index] = EEPROM.read(index + IP);
    gateway[index] = EEPROM.read(index + GATEWAY);
    subnet[index] = EEPROM.read(index + SUBNET);
  }
  //Starting ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  //delay(2000); //wait until ethernet finish starting
}

void ModbusCycle()
{
  /*************************************************
  *                 MODBUS CYCLE                   *
  *                                                *
  * This is the modbus cycle. It will run at least *
  * once at each plc cycle. During the modbus      *
  * cycle, the modbus buffers of inputs and        *
  * outputs are updated, a check is made at the    *
    * ethernet buffer to see if any modbus message   *
    * was received, and an update of the local       *
  * output buffer is made if there are any modbus  *
  * request to write coils - FC5 or FC15.          *
  **************************************************
  */
  int modbusIndex = 0, plcIndex = X1_0;
  //update modbus input and output buffers
  while (plcIndex <= X8_7) //go through all inputs
  {
    modbus.I[modbusIndex] = readInput(plcIndex);  //update modbus discrete input buffer
    modbusIndex++;
    plcIndex++;
  }
  plcIndex = Y1_0; //set the index to the first output
  modbusIndex = 0;
  while (plcIndex <= Y8_7) //go through all outputs
  {
    modbus.C[modbusIndex] = readOutput(plcIndex); //update modbus coils buffer
    modbusIndex++;
    plcIndex++;
  }

  //check to see if there are new modbus messages and process them
  modbus.Run();

  //update the local output buffer according to the modbus coils buffer. If there are any modbus message to write on a coil, the output state of that coil will be changed now
  plcIndex = Y1_0; //set the index to the first output
  modbusIndex = 0;
  while (plcIndex <= Y8_7) //go through all outputs
  {
    setOutput(plcIndex, modbus.C[modbusIndex]); //change each output according to the modbus coils buffer
    plcIndex++;
    modbusIndex++;
  }
}

void OpenPLCcycle()
{
  readPLCSwitch(); //read the switch to determine the PLC status
  setStatusLeds(); //set the leds according to PLC status
  if (PLCstatus == RUN)
  {
    updateInput(); //read the state of each input card connected
    ModbusCycle(); //check modbus messages
    PlcCycle(); //run the ladder program once
    updateOutput(); //update output state of each output card connected according to the internal output buffer
  }
  else if (PLCstatus == STOP)
  {
    clearOutputs(); //certify that all outputs are turned off
    CheckSerial(); //check to see if there are any serial messages received
    ProcessMessage(); //if there are messages at the serial buffer, process them
  }
  else if (PLCstatus == HALTED)
  {
    clearOutputs(); //certify that all outputs are turned off
  }
  //verify if it's possible to clear errors
  if (errorCount > 0 && PLCstatus != HALTED)
  {
    if (millis() - lastError > ERROR_TIMEOUT)
    {
      errorCount = 0;
    }
  }
  countTimers(); //special function timers
}

void readPLCSwitch()
{
  if (!digitalRead(RUN_PIN))
  {
    PLCstatus = RUN;
    //clear serial buffer to ignore messages during RUNtime
    while (Serial.available())
    {
      Serial.read();
    }
  }
  if (!digitalRead(STOP_PIN))
  {
    PLCstatus = STOP;
  }
  if (!digitalRead(AUTO_PIN))
  {
    if (Serial.available())
    {
      PLCstatus = STOP;
    }
    else
    {
      PLCstatus = RUN;
    }
  }
  if (errorCount > MAX_ERROR)
  {
    PLCstatus = HALTED;
  }
}

void setStatusLeds()
{
  if (PLCstatus == RUN)
  {
    digitalWrite(RUN_LED, HIGH);
    digitalWrite(ERROR_LED, LOW);
  }
  else if (PLCstatus == STOP)
  {
    digitalWrite(RUN_LED, LOW);
    digitalWrite(ERROR_LED, LOW);
  }
  else if (PLCstatus == HALTED)
  {
    digitalWrite(RUN_LED, LOW);
    digitalWrite(ERROR_LED, HIGH);
  }
}

int readInput(int input)
{
  if (input < 0 || input > MAX_INPUT) //invalid input
    return (ERROR_MSG); //return error
  else
    return inputVector[input]; //return input state
}

int readOutput(int output)
{
  if (output < 0 || output > MAX_OUTPUT) //invalid output
    return (ERROR_MSG); //return error
  else
    return outputVector[output]; //return output state
}

int setOutput(int output, boolean state)
{
  if (output < 0 || output > MAX_OUTPUT) //invalid output
    return (ERROR_MSG); //return error
  else
    outputVector[output] = state; //change internal output buffer state
}

void PLCInit()
{
  //setup pins
  pinMode(DE_PIN, OUTPUT); //RS-485 comm
  //status leds
  pinMode(RUN_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  //status switch
  pinMode(RUN_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);
  pinMode(AUTO_PIN, INPUT);
  //enable pullup on inputs
  digitalWrite(RUN_PIN, HIGH);
  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(AUTO_PIN, HIGH);
  //enable sending data through the bus
  digitalWrite(DE_PIN, HIGH);
  //start the rs485 communication at 115200 baud
  Serial1.begin(57600);
  //start serial communication
  Serial.begin(19200);
  //start ethernet and modbus
  ModbusInit();
  //check slots to identify the cards connected
  checkSlots();
  //send a READY signal after initialization
  Serial.print("READY");
  /*
  Serial.print("\rInput Cards Detected\r");
  int i=0;
  for (i=0;i<8;i++)
  {
  	Serial.print("Address ");
  	Serial.print(i+1);
  	Serial.print(":");
  	if(input_card_address[i])
  		Serial.print("OK\r");
  	else
  		Serial.print("None\r");
  }
  Serial.print("Output Cards Detected\r");
  for (i=0;i<8;i++)
  {
  	Serial.print("Address ");
  	Serial.print(i+1);
  	Serial.print(":");
  	if(output_card_address[i])
  		Serial.print("OK\r");
  	else
  		Serial.print("None\r");
  }
  */
}