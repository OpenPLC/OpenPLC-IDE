/*****************************************************
 *	     		PROTOTYPE DEFINITIONS                *
 *                                                   *
 * This file defines the function prototypes used    *
 * on the OpenPLC library                            *
 *                                                   *
 *****************************************************
 */

//Cards_Comm.h
void clearOutputs(void); //certify that all outputs are turned off
void updateInput(void); //read inputs of each input card connected and update the local input buffer
void updateOutput(void); //set outputs of each output card connected according to the local output buffer
void checkSlots(void); //search for cards connected on each slot
void checkCard(void); //check to see how many boards are connected to the system

//OpenPLC.cpp
void ModbusInit(void); //initialize the modbus functions
void ModbusCycle(void); //check to see if new modbus messages are received and process them
void OpenPLCcycle(void); //read inputs, process them according to the ladder software and set outputs
void readPLCSwitch(void); //read the switch to determine the PLC status
void setStatusLeds(void); //set the leds according to PLC status
int readInput(int input); //return the value of the specified input according to the local input buffer
int readOutput(int output); //return the value of the specified output according to the local output buffer
int setOutput(int output, boolean state); //set or clear the value of the specified output in the local output buffer
void PLCInit(void); //initialize plc functions

//OPLC_Protocol.h
void OPLC_send(byte dataSize, byte function, byte address, byte * data); //send a message over the OPLC Protocol
boolean OPLC_receive(byte * dataSize, byte * function, byte * data); //receive a message over the OPLC Protocol

//PC_Comm.h 
void showInfo(void); //show information about the PLC over Serial Port when requested
void newValue(int startAddress); //change the value of the IP Addres, Subnet Mask or Gateway
void newMAC(void); //change the MAC address
void newAddress(void); //change one of the cards address
void restoreOriginal(void); //restore all information to factory-default
void CheckSerial(void); //check to see if any message was received over Serial Port
void ProcessMessage(void); //process any received message

//Special_functions.h
boolean SF_01(void);
boolean SF_02(void);
boolean SF_03(void);
boolean SF_04(void);
boolean SF_05(void);
boolean SF_06(void);
void countTimers(void);