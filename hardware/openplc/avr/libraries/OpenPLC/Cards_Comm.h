void clearOutputs()
{
  int i;
  byte sendData[1] = {0x00};
  for (i = 1; i <= 8; i++)
  {
    OPLC_send(0x01, SET_OUTPUT, i, sendData); //clear outputs
    delay(OPLC_TIMEOUT); //wait to avoid multiple messages on the bus
  }
}

void updateInput()
{
  byte dataSize, function, cardAddress, dataReceived[1];
  byte inputsReceived[8];
  boolean hadError = false;
  int i, j, vectorIndex;
  for (i = 0; i < 8; i++) //reading each input card
  {
    if (input_card_address[i]) //if there is a card connected with the address 'i+1'
    {
      //ask for the inputs state
      OPLC_send(0x00, READ_INPUT, i + 1, 0x00); //dataSize, function, address, data
      if (OPLC_receive(&dataSize, &function, &cardAddress, dataReceived) && function == READ_INPUT)
      {
        inputsReceived[i] = dataReceived[0]; //save the byte read
      }
      else
      {
        Serial.print("ERROR\r");
        hadError = true;
        errorCount++;
        lastError = millis(); //clear error timeout
      }
    }
    else
    {
      inputsReceived[i] = 0;
    }
  }
  //copying each bit to the input vector
  vectorIndex = 0;
  if (!hadError) //if there were no errors
  {
    for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
      {
        inputVector[vectorIndex] = bitRead(inputsReceived[i], j);
        vectorIndex++;
      }
    }
  }

  //show inputs read
  /*
  Serial.print("\rInputs:\r");
  for (i=0;i<MAX_INPUT;i++)
  {
  	Serial.print(i);
  	Serial.print(": ");
  	Serial.print(inputVector[i], DEC);
  	Serial.print("\r");
  }
  Serial.print("\r\r\r");
  */
}

void updateOutput()
{
  byte dataSize, function, cardAddress, outputData[1];
  byte outputBytes[8];
  int i, j, vectorIndex;
  //copying each bit of the output vector to the outputBytes buffer
  vectorIndex = 0;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      bitWrite(outputBytes[i], j, outputVector[vectorIndex]);
      vectorIndex++;
    }
  }

  for (i = 0; i < 8; i++) //setting each output card connected
  {
    if (output_card_address[i]) //if there is a card connected with the address 'i+1'
    {
      //set the outputs state
      outputData[0] = outputBytes[i];
      OPLC_send(0x01, SET_OUTPUT, i + 1, outputData); //dataSize, function, address, data
      if (OPLC_receive(&dataSize, &function, &cardAddress, outputData) && function == SET_OUTPUT && outputData[0] == outputBytes[i])
      {
        //everything is fine!
      }
      else
      {
        Serial.print("ERROR\r");
        errorCount++;
        lastError = millis(); //clear error timeout
      }
    }
  }
}

void checkSlots()
{
  byte dataSize, function, cardAddress, dataReceived[2];
  int slot = 0;

  //clearing vectors
  for (slot = 0; slot < 8; slot++)
  {
    input_card_address[slot] = false;
    output_card_address[slot] = false;
  }

  //searching for connected cards
  for (slot = 0; slot < 8; slot++)
  {
    OPLC_send(0x00, CARD_TYPE, slot, 0x00);
    if (OPLC_receive(&dataSize, &function, &cardAddress, dataReceived) && function == CARD_TYPE)
    {
      switch (dataReceived[0])
      {
        case DISCRETE_INPUT:
          if (dataReceived[1] > 0 && dataReceived[1] < 9) //validate card address (must be between 1 and 8)
          {
            input_card_address[dataReceived[1] - 1] = true; //found an input card
          }
          break;
        case DISCRETE_OUTPUT:
          if (dataReceived[1] > 0 && dataReceived[1] < 9) //validate card address (must be between 1 and 8)
          {
            output_card_address[dataReceived[1] - 1] = true; //found an output card
          }
          break;
      }
    }
  }
}

void checkCard(int slotNumber)
{
  byte dataSize, function, address, dataReceived[2];

  Serial.print("Slot"); Serial.print(slotNumber); Serial.print(":\r");
  Serial.flush();
  OPLC_send(0x00, CARD_TYPE, slotNumber, 0x00);
  if (OPLC_receive(&dataSize, &function, &address, dataReceived) && function == CARD_TYPE)
  {
    switch (dataReceived[0])
    {
      case DISCRETE_INPUT:
        Serial.print("Discrete Input Card\r");
        break;
      case DISCRETE_OUTPUT:
        Serial.print("Discrete Output Card\r");
        break;
      default:
        Serial.print("Unrecognized Card\r");
        break;
    }
    Serial.print("Address:\r");
    //Serial.print("0x");
    Serial.print(dataReceived[1], HEX);
    Serial.print('\r');
  }
  else if (function == MSG_ERROR)
  {
    Serial.print("Error communicating with the card\r");
    Serial.print("Address:\r");
    Serial.print("none\r");
  }
  else
  {
    Serial.print("No card installed\r");
    Serial.print("Address:\r");
    Serial.print("none\r");
  }
  Serial.flush();
}