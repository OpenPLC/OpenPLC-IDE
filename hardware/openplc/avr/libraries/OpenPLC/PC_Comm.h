void showInfo()
{
	/*************************************************
	*                  SHOW INFO                     *
	*                                                *
	* This function sends information about the PLC  *
	* when the "info" message is received over the   *
	* serial port. The information is sent with a    *
	* '\r' character at the end of each message.     *
	**************************************************
	*/
	//Sending basic informations
	Serial.print("OpenPLC Prototype Rev.1\r"); //model
	Serial.print("00000000-0001\r"); //serial number
	Serial.print("AVR ATmega2560 16MHz\r"); //CPU
	Serial.print("8\r"); //expansion slots
	//Sending MAC address
	Serial.print(EEPROM.read(MAC), HEX); Serial.print(":");
	Serial.print(EEPROM.read(MAC+1), HEX); Serial.print(":");
	Serial.print(EEPROM.read(MAC+2), HEX); Serial.print(":");
	Serial.print(EEPROM.read(MAC+3), HEX); Serial.print(":");
	Serial.print(EEPROM.read(MAC+4), HEX); Serial.print(":");
	Serial.print(EEPROM.read(MAC+5), HEX);
	Serial.print('\r');
	//Sending IP address
	Serial.print(EEPROM.read(IP), DEC); Serial.print(".");
	Serial.print(EEPROM.read(IP+1), DEC); Serial.print(".");
	Serial.print(EEPROM.read(IP+2), DEC); Serial.print(".");
	Serial.print(EEPROM.read(IP+3), DEC); 
	Serial.print('\r');
	//Sending Gateway address
	Serial.print(EEPROM.read(GATEWAY), DEC); Serial.print(".");
	Serial.print(EEPROM.read(GATEWAY+1), DEC); Serial.print(".");
	Serial.print(EEPROM.read(GATEWAY+2), DEC); Serial.print(".");
	Serial.print(EEPROM.read(GATEWAY+3), DEC);
	Serial.print('\r');
	//Sending Subnet Mask
	Serial.print(EEPROM.read(SUBNET), DEC); Serial.print(".");
	Serial.print(EEPROM.read(SUBNET+1), DEC); Serial.print(".");
	Serial.print(EEPROM.read(SUBNET+2), DEC); Serial.print(".");
	Serial.print(EEPROM.read(SUBNET+3), DEC);
	Serial.print('\r');
	//Sending Cards Types
	int i;
	for(i=0; i<8; i++)
	{
		checkCard(i);
	}
}

void newValue(int startAddress)
{
	/**************************************************
	*                  NEW VALUE                      *
	*                                                 *
	* This function is called whenever a value stored *
	* in the EEPROM memory needs to be updated. It    *
	* will read each byte of the word received, parse *
	* it and convert the string value received into   *
	* an integer to save it on an EEPROM position.    *
	***************************************************
	*/
	char aux[4]; //to store temporarily the byte received
	int i,j=2,k; //indexers
	for (i=0;i<4;i++)//reading each byte of the word (total = 4 bytes)
	{
		k=0; //aux index starts with zero
		//making sure that aux has no trash on it
		aux[0]='\0';
		aux[1]='\0';
		aux[2]='\0';
		while(message[j]!='.' && message[j]!='E') //search for the end of the byte (the byte ends with '.' or 'E' characters
		{
			aux[k]=message[j]; //aux receives message's character
			k++;
			j++;
		}
		j++; //message index keeps going
		aux[k]='\0'; //end of string
		EEPROM.write(startAddress,atoi(aux)); //write the new value received on the message converting it first into integer
		startAddress++; //go to the next address until message[] ends
	}
}

void newMAC()
{
	char aux[4]; //to store temporarily the byte received
	char* pos = aux; //pointer to the aux, needed by the function that converts an HEXA string into an integer
	int i,j=2,k,startAddress=1; //indexers
	for (i=0;i<6;i++) //reading each byte of the word (total = 6 bytes for the MAC)
	{
		//making sure that aux has no trash on it
		aux[0]='\0';
		aux[1]='\0';
		aux[2]='\0';
		k=0; //aux index starts with zero
		while(message[j]!=':' && message[j]!='E') //search for the end of the byte (the byte ends with ':' or 'E' characters
		{
			aux[k]=message[j]; //aux receives message's character
			k++;
			j++;
		}
		j++; //message index keeps going
		aux[k]='\0'; //end of string
		pos=aux; //pos points to the start of aux
		EEPROM.write(startAddress,strtol(pos, &pos, 16)); //write the new value received on the message converting it first from ASCII HEX to integer
		startAddress++; //go to the next address
	}
}

void newAddress()
{
	byte slotNumber, newAddress;
	byte dataSize, function, address, dataReceived[2];
	char temp[3];
	
	//getting the slot id
	temp[0]=message[4];
	temp[1]=message[5];
	temp[2]='\0';
	slotNumber=atoi(temp);
	
	//getting the new address
	temp[0]=message[9];
	temp[1]=message[10];
	temp[2]='\0';
	newAddress=atoi(temp);
	
	//sending message
	OPLC_send(0x01, CHANGE_ADDRESS, slotNumber, &newAddress);
	if (OPLC_receive(&dataSize, &function, &address, dataReceived) && function == CHANGE_ADDRESS)
	{
		Serial.print("OK\r");
		checkSlots(); //recreate vector of connected cards
	}
	else
	{
		Serial.print("ERROR\r");
	}
}

void restoreOriginal()
{
	Serial.println("Network information will be reset after reboot");
	EEPROM.write(0,127);
}

void CheckSerial()
{
	/**************************************************
	*                CHECK SERIAL                     *
	*                                                 *
	* Check Serial is called once at every OpenPLC    *
	* cycle to see if there are any messages received *
	* over the serial port. The message received must *
	* end with the 'E' character. Once it is fully    *
	* received, an "OK" is sent back.                 *
	***************************************************
	*/
	//check to see if there are any messages in the Serial buffer
	if (Serial.available())
	{
	while(Serial.available()&&!newMessage) //keep reading each byte of the message received until it reaches the end ('E' character)
	{
	  message[messageIndex] = Serial.read(); //message buffer gets a byte from the Serial port buffer
	  if (message[messageIndex] == 'E')  //if the byte received is an 'E'
	  {
		Serial.print("OK\r"); //send the "message received" confirmation
		newMessage = true; //set the new message flag
		message[messageIndex+1]='\0'; //end of string
		messageIndex=0; //start-over the message index
	  }
	  else {messageIndex++;}
	}
	}
}

void ProcessMessage()
{
	/**************************************************
	*               PROCESS MESSAGE                   *
	*                                                 *
	* Every time a new message is received, it must   *
	* be processed. The new message must be one of    *
	* the following:                                  *
	* 1) info:                                        *
	*     This message calls the showInfo function    *
	*     to send back information about the PLC.     *
	* 2) ip:                                          *
	*     Any message starting with "ip" must have    *
	*     an ip number right after the 'p' character. *
	*     For example: ip192.168.0.55 is a valid      *
	*     message.                                    *
	* 3) gt:                                          *
	*     Similarly to the ip message, a gt message   *
	*     must have a valid gateway address after the *
	*     't' character.                              *
	* 4) sb:                                          *
	*     Again, a valid subnet mask address must     *
	*     come after the 'b' character                *
	* 5) mc:                                          *
	*     mc messages are needed to configure a new   *
	*     MAC address. It must be written in pure     *
	*     ASCII HEXA. Here is an example of an "mc"   *
	*     message: mc6A:7E:22:13:45:FF                *
	* 6) ca:										  *
	*     ca stands for Change Address. This message  *
	*     will tell the OpenPLC to change the address *
	*     of one of the connected cards. The message  *
	*     must contain the slot id and the new addres *
	*     to be sent to the card separated by a '.'	  *
	*     Ex: ca0x01.0x07 (slot 0x01 | address 0x07)  *
	* 7) reset:                                       *
	*     The reset message will call the             *
	*     restoreOriginal() function to restore the   *
	*     OpenPLC's factory defaults.                 *
	***************************************************
	*/
	if(newMessage==true)
	{
		if(message[0]=='i' && message[1]=='n' && message[2]=='f' && message[3]=='o')
		{
			showInfo();
		}
		else if(message[0]=='i' && message[1]=='p')
		{
			newValue(IP);
		}
		else if(message[0]=='g' && message[1]=='t')
		{
			newValue(GATEWAY);
		}
		else if(message[0]=='s' && message[1]=='b')
		{
			newValue(SUBNET);
		}
		else if(message[0]=='m' && message[1]=='c')
		{
			newMAC();
		}
		else if(message[0]=='c' && message[1]=='a')
		{
			newAddress();
		}
		else if(message[0]=='r' && message[1]=='e' && message[2]=='s' && message[3]=='e' && message[4]=='t')
		{
			restoreOriginal();
		}	
		newMessage=false;
	}
}