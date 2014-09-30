/*
    Mudbus.cpp - an Arduino library for a Modbus TCP slave.
    Copyright (C) 2011  Dee Wykoff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Mudbus.h"

EthernetServer MbServer(MB_PORT);

Mudbus::Mudbus()
{
}

void Mudbus::Run()
{  
  Runs = 1 + Runs * (Runs < 999);

  //****************** Read from socket ****************
  EthernetClient client = MbServer.available();
  if(client.available())
  {
    Reads = 1 + Reads * (Reads < 999);
    int i = 0;
    while(client.available())
    {
      ByteArray[i] = client.read();
      i++;
    }
    SetFC(ByteArray[7]);  //Byte 7 of request is FC
    if(!Active)
    {
      Active = true;
      PreviousActivityTime = millis();
    }
  }
  if(millis() > (PreviousActivityTime + 60000))
  {
    if(Active)
    {
      Active = false;
    }
  }

  int Start, WordDataLength, ByteDataLength, CoilDataLength, InputDataLength, MessageLength;

  //****************** Read Coils **********************
  if(FC == MB_FC_READ_COILS)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    CoilDataLength = word(ByteArray[10],ByteArray[11]);
	//calculating the size of the message in bytes
    ByteDataLength = CoilDataLength / 8;
    if(ByteDataLength * 8 < CoilDataLength) ByteDataLength++;      
    CoilDataLength = ByteDataLength * 8;
    ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
    ByteArray[8] = ByteDataLength;     //Number of bytes after this one (or number of bytes of data).
    for(int i = 0; i < ByteDataLength ; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        bitWrite(ByteArray[9 + i], j, C[Start + i * 8 + j]);
      }
    }
    MessageLength = ByteDataLength + 9;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }
  //*************** Read Discrete Inputs ***************	
  if(FC == MB_FC_READ_INPUTS)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    InputDataLength = word(ByteArray[10],ByteArray[11]);
    ByteDataLength = InputDataLength / 8;
    if(ByteDataLength * 8 < InputDataLength) ByteDataLength++;      
    InputDataLength = ByteDataLength * 8;
    ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
    ByteArray[8] = ByteDataLength;     //Number of bytes after this one (or number of bytes of data).
    for(int i = 0; i < ByteDataLength ; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        bitWrite(ByteArray[9 + i], j, I[Start + i * 8 + j]);
      }
    }
    MessageLength = ByteDataLength + 9;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }
  //****************** Read Registers ******************
  if(FC == MB_FC_READ_REGISTERS)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    WordDataLength = word(ByteArray[10],ByteArray[11]);
    ByteDataLength = WordDataLength * 2;
    ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
    ByteArray[8] = ByteDataLength;     //Number of bytes after this one (or number of bytes of data).
    for(int i = 0; i < WordDataLength; i++)
    {
      ByteArray[ 9 + i * 2] = highByte(R[Start + i]);
      ByteArray[10 + i * 2] =  lowByte(R[Start + i]);
    }
    MessageLength = ByteDataLength + 9;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }

  //****************** Write Coil **********************
  if(FC == MB_FC_WRITE_COIL)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    C[Start] = word(ByteArray[10],ByteArray[11]) > 0;
    ByteArray[5] = 2; //Number of bytes after this one.
    MessageLength = 8;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  } 

  //****************** Write Register ******************
  if(FC == MB_FC_WRITE_REGISTER)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    R[Start] = word(ByteArray[10],ByteArray[11]);
    ByteArray[5] = 6; //Number of bytes after this one.
    MessageLength = 12;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }


  //****************** Write Multiple Coils **********************
  //Function codes 15 & 16 by Martin Pettersson http://siamect.com
  if(FC == MB_FC_WRITE_MULTIPLE_COILS)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    CoilDataLength = word(ByteArray[10],ByteArray[11]);
    ByteDataLength = CoilDataLength / 8;
    if(ByteDataLength * 8 < CoilDataLength) ByteDataLength++;
    CoilDataLength = ByteDataLength * 8;
    ByteArray[5] = ByteDataLength + 5; //Number of bytes after this one.
    for(int i = 0; i < ByteDataLength ; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        C[Start + i * 8 + j] = bitRead( ByteArray[13 + i], j);
      }
    }
    MessageLength = 12;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }


  //****************** Write Multiple Registers ******************
  //Function codes 15 & 16 by Martin Pettersson http://siamect.com
  if(FC == MB_FC_WRITE_MULTIPLE_REGISTERS)
  {
    Start = word(ByteArray[8],ByteArray[9]);
    WordDataLength = word(ByteArray[10],ByteArray[11]);
    ByteDataLength = WordDataLength * 2;
    ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
    for(int i = 0; i < WordDataLength; i++)
    {
      R[Start + i] =  word(ByteArray[ 13 + i * 2],ByteArray[14 + i * 2]);
    }
    MessageLength = 12;
    client.write(ByteArray, MessageLength);
    Writes = 1 + Writes * (Writes < 999);
    FC = MB_FC_NONE;
  }
}


void Mudbus::SetFC(int fc)
{
  if(fc == 1) FC = MB_FC_READ_COILS;
  if(fc == 2) FC = MB_FC_READ_INPUTS;
  if(fc == 3) FC = MB_FC_READ_REGISTERS;
  if(fc == 5) FC = MB_FC_WRITE_COIL;
  if(fc == 6) FC = MB_FC_WRITE_REGISTER;
  if(fc == 15) FC = MB_FC_WRITE_MULTIPLE_COILS;
  if(fc == 16) FC = MB_FC_WRITE_MULTIPLE_REGISTERS;
}
