//global variables
boolean newMessage = false; //new message flag
char message[100]; //serial message buffer
int messageIndex = 0; //serial message buffer index

//system variables
boolean input_card_address[8] = {false, false, false, false, false, false, false, false}; //address of each input card connected. false means no card connected
boolean output_card_address[8] = {false, false, false, false, false, false, false, false}; //address of each output card connected. false means no card connected
//special function variables
boolean first_cycle = true;
boolean toggle_30s = false;
boolean toggle_500ms = false;
boolean toggle_50ms = false;
int system_timer = 0;
char PLCstatus; //status of the actual state of the OpenPLC
int errorCount = 0;
long lastError = 0;

Mudbus modbus; //create the modbus object

/*************************************************
*          LOCAL INPUT/OUTPUT BUFFERS            *
*                                                *
* These buffers store the value of the input and *
* output read from the cards. During the PLC     *
* cycle, all input cards' values are read and    *
* stored inside inputVector. After that, the     *
* Ladder programm is processed and then the      *
* result is stored inside the outputVector. At   *
* the end of the PLC cycle, the values stored in *
* the outputVector are sent to the output cards. *
**************************************************
*/
boolean inputVector[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};
boolean outputVector[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};