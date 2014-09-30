/*
A wrapper library for OpenPLC.
This includes OpenPLCWrapper.h and Arduino-core.h

OpenPLCWrapper takes care of all OpenPLC side of things,
making it smooth to transition from the main board to
mini/micro OpenPLC boards without changing the included files.
The variant system of Arduino IDE takes care of that.

The Arduino-core.h is renamed from the original Arduino.h file
and takes care of all the arduino stuff that needs to be there 
from the beginning. 

*/

#ifndef OpenPLCWrapper_h
#define OpenPLCWrapper_h

#include <Arduino-core.h>
//#include <openplc/OpenPLC.h>

#endif
