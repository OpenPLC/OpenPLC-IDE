/* This code was written specifically for the OpenPLC by the OpenPLC Team. */
/* It will work only with the auto-generated code by LDMicro               */


#ifndef LADDER_H
#define LADDER_H

//#include "WProgram.h"
//#include <Arduino.h>
#include <OpenPLC.h>

#define BOOL boolean
#define SWORD int

#define EXTERN_EVERYTHING
#define NO_PROTOTYPES

void PlcCycle(void);


/* Individual pins (this code is used in ladder.cpp) */

//SPECIAL FUNCTIONS
inline extern BOOL Read_U_b_XSF01(void)
{
	return SF_01();
}

inline extern BOOL Read_U_b_XSF02(void)
{
	return SF_02();
}

inline extern BOOL Read_U_b_XSF03(void)
{
	return SF_03();
}

inline extern BOOL Read_U_b_XSF04(void)
{
	return SF_04();
}

inline extern BOOL Read_U_b_XSF05(void)
{
	return SF_05();
}

inline extern BOOL Read_U_b_XSF06(void)
{
	return SF_06();
}

//READING INPUT CARDS
//CARD 1
inline extern BOOL Read_U_b_X1_0(void)
{
    return readInput(X1_0);
}

inline extern BOOL Read_U_b_X1_1(void)
{
    return readInput(X1_1);
}

inline extern BOOL Read_U_b_X1_2(void)
{
    return readInput(X1_2);
}

inline extern BOOL Read_U_b_X1_3(void)
{
    return readInput(X1_3);
}

inline extern BOOL Read_U_b_X1_4(void)
{
    return readInput(X1_4);
}

inline extern BOOL Read_U_b_X1_5(void)
{
    return readInput(X1_5);
}

inline extern BOOL Read_U_b_X1_6(void)
{
    return readInput(X1_6);
}

inline extern BOOL Read_U_b_X1_7(void)
{
    return readInput(X1_7);
}

//CARD 2
inline extern BOOL Read_U_b_X2_0(void)
{
    return readInput(X2_0);
}

inline extern BOOL Read_U_b_X2_1(void)
{
    return readInput(X2_1);
}

inline extern BOOL Read_U_b_X2_2(void)
{
    return readInput(X2_2);
}

inline extern BOOL Read_U_b_X2_3(void)
{
    return readInput(X2_3);
}

inline extern BOOL Read_U_b_X2_4(void)
{
    return readInput(X2_4);
}

inline extern BOOL Read_U_b_X2_5(void)
{
    return readInput(X2_5);
}

inline extern BOOL Read_U_b_X2_6(void)
{
    return readInput(X2_6);
}

inline extern BOOL Read_U_b_X2_7(void)
{
    return readInput(X2_7);
}

//CARD 3
inline extern BOOL Read_U_b_X3_0(void)
{
    return readInput(X3_0);
}

inline extern BOOL Read_U_b_X3_1(void)
{
    return readInput(X3_1);
}

inline extern BOOL Read_U_b_X3_2(void)
{
    return readInput(X3_2);
}

inline extern BOOL Read_U_b_X3_3(void)
{
    return readInput(X3_3);
}

inline extern BOOL Read_U_b_X3_4(void)
{
    return readInput(X3_4);
}

inline extern BOOL Read_U_b_X3_5(void)
{
    return readInput(X3_5);
}

inline extern BOOL Read_U_b_X3_6(void)
{
    return readInput(X3_6);
}

inline extern BOOL Read_U_b_X3_7(void)
{
    return readInput(X3_7);
}

//CARD 4
inline extern BOOL Read_U_b_X4_0(void)
{
    return readInput(X4_0);
}

inline extern BOOL Read_U_b_X4_1(void)
{
    return readInput(X4_1);
}

inline extern BOOL Read_U_b_X4_2(void)
{
    return readInput(X4_2);
}

inline extern BOOL Read_U_b_X4_3(void)
{
    return readInput(X4_3);
}

inline extern BOOL Read_U_b_X4_4(void)
{
    return readInput(X4_4);
}

inline extern BOOL Read_U_b_X4_5(void)
{
    return readInput(X4_5);
}

inline extern BOOL Read_U_b_X4_6(void)
{
    return readInput(X4_6);
}

inline extern BOOL Read_U_b_X4_7(void)
{
    return readInput(X4_7);
}

//CARD 5
inline extern BOOL Read_U_b_X5_0(void)
{
    return readInput(X5_0);
}

inline extern BOOL Read_U_b_X5_1(void)
{
    return readInput(X5_1);
}

inline extern BOOL Read_U_b_X5_2(void)
{
    return readInput(X5_2);
}

inline extern BOOL Read_U_b_X5_3(void)
{
    return readInput(X5_3);
}

inline extern BOOL Read_U_b_X5_4(void)
{
    return readInput(X5_4);
}

inline extern BOOL Read_U_b_X5_5(void)
{
    return readInput(X5_5);
}

inline extern BOOL Read_U_b_X5_6(void)
{
    return readInput(X5_6);
}

inline extern BOOL Read_U_b_X5_7(void)
{
    return readInput(X5_7);
}

//CARD 6
inline extern BOOL Read_U_b_X6_0(void)
{
    return readInput(X6_0);
}

inline extern BOOL Read_U_b_X6_1(void)
{
    return readInput(X6_1);
}

inline extern BOOL Read_U_b_X6_2(void)
{
    return readInput(X6_2);
}

inline extern BOOL Read_U_b_X6_3(void)
{
    return readInput(X6_3);
}

inline extern BOOL Read_U_b_X6_4(void)
{
    return readInput(X6_4);
}

inline extern BOOL Read_U_b_X6_5(void)
{
    return readInput(X6_5);
}

inline extern BOOL Read_U_b_X6_6(void)
{
    return readInput(X6_6);
}

inline extern BOOL Read_U_b_X6_7(void)
{
    return readInput(X6_7);
}

//CARD 7
inline extern BOOL Read_U_b_X7_0(void)
{
    return readInput(X7_0);
}

inline extern BOOL Read_U_b_X7_1(void)
{
    return readInput(X7_1);
}

inline extern BOOL Read_U_b_X7_2(void)
{
    return readInput(X7_2);
}

inline extern BOOL Read_U_b_X7_3(void)
{
    return readInput(X7_3);
}

inline extern BOOL Read_U_b_X7_4(void)
{
    return readInput(X7_4);
}

inline extern BOOL Read_U_b_X7_5(void)
{
    return readInput(X7_5);
}

inline extern BOOL Read_U_b_X7_6(void)
{
    return readInput(X7_6);
}

inline extern BOOL Read_U_b_X7_7(void)
{
    return readInput(X7_7);
}

//CARD 8
inline extern BOOL Read_U_b_X8_0(void)
{
    return readInput(X8_0);
}

inline extern BOOL Read_U_b_X8_1(void)
{
    return readInput(X8_1);
}

inline extern BOOL Read_U_b_X8_2(void)
{
    return readInput(X8_2);
}

inline extern BOOL Read_U_b_X8_3(void)
{
    return readInput(X8_3);
}

inline extern BOOL Read_U_b_X8_4(void)
{
    return readInput(X8_4);
}

inline extern BOOL Read_U_b_X8_5(void)
{
    return readInput(X8_5);
}

inline extern BOOL Read_U_b_X8_6(void)
{
    return readInput(X8_6);
}

inline extern BOOL Read_U_b_X8_7(void)
{
    return readInput(X8_7);
}

//WRITING ON OUTPUT CARDS
//CARD 1
inline void Write_U_b_Y1_0(BOOL v)
{
    setOutput(Y1_0, v);
}

inline void Write_U_b_Y1_1(BOOL v)
{
    setOutput(Y1_1, v);
}

inline void Write_U_b_Y1_2(BOOL v)
{
    setOutput(Y1_2, v);
}

inline void Write_U_b_Y1_3(BOOL v)
{
    setOutput(Y1_3, v);
}
inline void Write_U_b_Y1_4(BOOL v)
{
    setOutput(Y1_4, v);
}

inline void Write_U_b_Y1_5(BOOL v)
{
    setOutput(Y1_5, v);
}

inline void Write_U_b_Y1_6(BOOL v)
{
    setOutput(Y1_6, v);
}

inline void Write_U_b_Y1_7(BOOL v)
{
    setOutput(Y1_7, v);
}

//CARD 2
inline void Write_U_b_Y2_0(BOOL v)
{
    setOutput(Y2_0, v);
}

inline void Write_U_b_Y2_1(BOOL v)
{
    setOutput(Y2_1, v);
}

inline void Write_U_b_Y2_2(BOOL v)
{
    setOutput(Y2_2, v);
}

inline void Write_U_b_Y2_3(BOOL v)
{
    setOutput(Y2_3, v);
}
inline void Write_U_b_Y2_4(BOOL v)
{
    setOutput(Y2_4, v);
}

inline void Write_U_b_Y2_5(BOOL v)
{
    setOutput(Y2_5, v);
}

inline void Write_U_b_Y2_6(BOOL v)
{
    setOutput(Y2_6, v);
}

inline void Write_U_b_Y2_7(BOOL v)
{
    setOutput(Y2_7, v);
}

//CARD 3
inline void Write_U_b_Y3_0(BOOL v)
{
    setOutput(Y3_0, v);
}

inline void Write_U_b_Y3_1(BOOL v)
{
    setOutput(Y3_1, v);
}

inline void Write_U_b_Y3_2(BOOL v)
{
    setOutput(Y3_2, v);
}

inline void Write_U_b_Y3_3(BOOL v)
{
    setOutput(Y3_3, v);
}
inline void Write_U_b_Y3_4(BOOL v)
{
    setOutput(Y3_4, v);
}

inline void Write_U_b_Y3_5(BOOL v)
{
    setOutput(Y3_5, v);
}

inline void Write_U_b_Y3_6(BOOL v)
{
    setOutput(Y3_6, v);
}

inline void Write_U_b_Y3_7(BOOL v)
{
    setOutput(Y3_7, v);
}

//CARD 4
inline void Write_U_b_Y4_0(BOOL v)
{
    setOutput(Y4_0, v);
}

inline void Write_U_b_Y4_1(BOOL v)
{
    setOutput(Y4_1, v);
}

inline void Write_U_b_Y4_2(BOOL v)
{
    setOutput(Y4_2, v);
}

inline void Write_U_b_Y4_3(BOOL v)
{
    setOutput(Y4_3, v);
}
inline void Write_U_b_Y4_4(BOOL v)
{
    setOutput(Y4_4, v);
}

inline void Write_U_b_Y4_5(BOOL v)
{
    setOutput(Y4_5, v);
}

inline void Write_U_b_Y4_6(BOOL v)
{
    setOutput(Y4_6, v);
}

inline void Write_U_b_Y4_7(BOOL v)
{
    setOutput(Y4_7, v);
}

//CARD 5
inline void Write_U_b_Y5_0(BOOL v)
{
    setOutput(Y5_0, v);
}

inline void Write_U_b_Y5_1(BOOL v)
{
    setOutput(Y5_1, v);
}

inline void Write_U_b_Y5_2(BOOL v)
{
    setOutput(Y5_2, v);
}

inline void Write_U_b_Y5_3(BOOL v)
{
    setOutput(Y5_3, v);
}
inline void Write_U_b_Y5_4(BOOL v)
{
    setOutput(Y5_4, v);
}

inline void Write_U_b_Y5_5(BOOL v)
{
    setOutput(Y5_5, v);
}

inline void Write_U_b_Y5_6(BOOL v)
{
    setOutput(Y5_6, v);
}

inline void Write_U_b_Y5_7(BOOL v)
{
    setOutput(Y5_7, v);
}

//CARD 6
inline void Write_U_b_Y6_0(BOOL v)
{
    setOutput(Y6_0, v);
}

inline void Write_U_b_Y6_1(BOOL v)
{
    setOutput(Y6_1, v);
}

inline void Write_U_b_Y6_2(BOOL v)
{
    setOutput(Y6_2, v);
}

inline void Write_U_b_Y6_3(BOOL v)
{
    setOutput(Y6_3, v);
}
inline void Write_U_b_Y6_4(BOOL v)
{
    setOutput(Y6_4, v);
}

inline void Write_U_b_Y6_5(BOOL v)
{
    setOutput(Y6_5, v);
}

inline void Write_U_b_Y6_6(BOOL v)
{
    setOutput(Y6_6, v);
}

inline void Write_U_b_Y6_7(BOOL v)
{
    setOutput(Y6_7, v);
}

//CARD 7
inline void Write_U_b_Y7_0(BOOL v)
{
    setOutput(Y7_0, v);
}

inline void Write_U_b_Y7_1(BOOL v)
{
    setOutput(Y7_1, v);
}

inline void Write_U_b_Y7_2(BOOL v)
{
    setOutput(Y7_2, v);
}

inline void Write_U_b_Y7_3(BOOL v)
{
    setOutput(Y7_3, v);
}
inline void Write_U_b_Y7_4(BOOL v)
{
    setOutput(Y7_4, v);
}

inline void Write_U_b_Y7_5(BOOL v)
{
    setOutput(Y7_5, v);
}

inline void Write_U_b_Y7_6(BOOL v)
{
    setOutput(Y7_6, v);
}

inline void Write_U_b_Y7_7(BOOL v)
{
    setOutput(Y7_7, v);
}

//CARD 8
inline void Write_U_b_Y8_0(BOOL v)
{
    setOutput(Y8_0, v);
}

inline void Write_U_b_Y8_1(BOOL v)
{
    setOutput(Y8_1, v);
}

inline void Write_U_b_Y8_2(BOOL v)
{
    setOutput(Y8_2, v);
}

inline void Write_U_b_Y8_3(BOOL v)
{
    setOutput(Y8_3, v);
}
inline void Write_U_b_Y8_4(BOOL v)
{
    setOutput(Y8_4, v);
}

inline void Write_U_b_Y8_5(BOOL v)
{
    setOutput(Y8_5, v);
}

inline void Write_U_b_Y8_6(BOOL v)
{
    setOutput(Y8_6, v);
}

inline void Write_U_b_Y8_7(BOOL v)
{
    setOutput(Y8_7, v);
}

//READING OUTPUTS
//CARD 1
inline BOOL Read_U_b_Y1_0(void)
{
    return readOutput(Y1_0);
}

inline BOOL Read_U_b_Y1_1(void)
{
    return readOutput(Y1_1);
}

inline BOOL Read_U_b_Y1_2(void)
{
    return readOutput(Y1_2);
}

inline BOOL Read_U_b_Y1_3(void)
{
    return readOutput(Y1_3);
}
inline BOOL Read_U_b_Y1_4(void)
{
    return readOutput(Y1_4);
}

inline BOOL Read_U_b_Y1_5(void)
{
    return readOutput(Y1_5);
}

inline BOOL Read_U_b_Y1_6(void)
{
    return readOutput(Y1_6);
}

inline BOOL Read_U_b_Y1_7(void)
{
    return readOutput(Y1_7);
}

//CARD 2
inline BOOL Read_U_b_Y2_0(void)
{
    return readOutput(Y2_0);
}

inline BOOL Read_U_b_Y2_1(void)
{
    return readOutput(Y2_1);
}

inline BOOL Read_U_b_Y2_2(void)
{
    return readOutput(Y2_2);
}

inline BOOL Read_U_b_Y2_3(void)
{
    return readOutput(Y2_3);
}
inline BOOL Read_U_b_Y2_4(void)
{
    return readOutput(Y2_4);
}

inline BOOL Read_U_b_Y2_5(void)
{
    return readOutput(Y2_5);
}

inline BOOL Read_U_b_Y2_6(void)
{
    return readOutput(Y2_6);
}

inline BOOL Read_U_b_Y2_7(void)
{
    return readOutput(Y2_7);
}

//CARD 3
inline BOOL Read_U_b_Y3_0(void)
{
    return readOutput(Y3_0);
}

inline BOOL Read_U_b_Y3_1(void)
{
    return readOutput(Y3_1);
}

inline BOOL Read_U_b_Y3_2(void)
{
    return readOutput(Y3_2);
}

inline BOOL Read_U_b_Y3_3(void)
{
    return readOutput(Y3_3);
}
inline BOOL Read_U_b_Y3_4(void)
{
    return readOutput(Y3_4);
}

inline BOOL Read_U_b_Y3_5(void)
{
    return readOutput(Y3_5);
}

inline BOOL Read_U_b_Y3_6(void)
{
    return readOutput(Y3_6);
}

inline BOOL Read_U_b_Y3_7(void)
{
    return readOutput(Y3_7);
}

//CARD 4
inline BOOL Read_U_b_Y4_0(void)
{
    return readOutput(Y4_0);
}

inline BOOL Read_U_b_Y4_1(void)
{
    return readOutput(Y4_1);
}

inline BOOL Read_U_b_Y4_2(void)
{
    return readOutput(Y4_2);
}

inline BOOL Read_U_b_Y4_3(void)
{
    return readOutput(Y4_3);
}
inline BOOL Read_U_b_Y4_4(void)
{
    return readOutput(Y4_4);
}

inline BOOL Read_U_b_Y4_5(void)
{
    return readOutput(Y4_5);
}

inline BOOL Read_U_b_Y4_6(void)
{
    return readOutput(Y4_6);
}

inline BOOL Read_U_b_Y4_7(void)
{
    return readOutput(Y4_7);
}

//CARD 5
inline BOOL Read_U_b_Y5_0(void)
{
    return readOutput(Y5_0);
}

inline BOOL Read_U_b_Y5_1(void)
{
    return readOutput(Y5_1);
}

inline BOOL Read_U_b_Y5_2(void)
{
    return readOutput(Y5_2);
}

inline BOOL Read_U_b_Y5_3(void)
{
    return readOutput(Y5_3);
}
inline BOOL Read_U_b_Y5_4(void)
{
    return readOutput(Y5_4);
}

inline BOOL Read_U_b_Y5_5(void)
{
    return readOutput(Y5_5);
}

inline BOOL Read_U_b_Y5_6(void)
{
    return readOutput(Y5_6);
}

inline BOOL Read_U_b_Y5_7(void)
{
    return readOutput(Y5_7);
}

//CARD 6
inline BOOL Read_U_b_Y6_0(void)
{
    return readOutput(Y6_0);
}

inline BOOL Read_U_b_Y6_1(void)
{
    return readOutput(Y6_1);
}

inline BOOL Read_U_b_Y6_2(void)
{
    return readOutput(Y6_2);
}

inline BOOL Read_U_b_Y6_3(void)
{
    return readOutput(Y6_3);
}
inline BOOL Read_U_b_Y6_4(void)
{
    return readOutput(Y6_4);
}

inline BOOL Read_U_b_Y6_5(void)
{
    return readOutput(Y6_5);
}

inline BOOL Read_U_b_Y6_6(void)
{
    return readOutput(Y6_6);
}

inline BOOL Read_U_b_Y6_7(void)
{
    return readOutput(Y6_7);
}

//CARD 7
inline BOOL Read_U_b_Y7_0(void)
{
    return readOutput(Y7_0);
}

inline BOOL Read_U_b_Y7_1(void)
{
    return readOutput(Y7_1);
}

inline BOOL Read_U_b_Y7_2(void)
{
    return readOutput(Y7_2);
}

inline BOOL Read_U_b_Y7_3(void)
{
    return readOutput(Y7_3);
}
inline BOOL Read_U_b_Y7_4(void)
{
    return readOutput(Y7_4);
}

inline BOOL Read_U_b_Y7_5(void)
{
    return readOutput(Y7_5);
}

inline BOOL Read_U_b_Y7_6(void)
{
    return readOutput(Y7_6);
}

inline BOOL Read_U_b_Y7_7(void)
{
    return readOutput(Y7_7);
}

//CARD 8
inline BOOL Read_U_b_Y8_0(void)
{
    return readOutput(Y8_0);
}

inline BOOL Read_U_b_Y8_1(void)
{
    return readOutput(Y8_1);
}

inline BOOL Read_U_b_Y8_2(void)
{
    return readOutput(Y8_2);
}

inline BOOL Read_U_b_Y8_3(void)
{
    return readOutput(Y8_3);
}
inline BOOL Read_U_b_Y8_4(void)
{
    return readOutput(Y8_4);
}

inline BOOL Read_U_b_Y8_5(void)
{
    return readOutput(Y8_5);
}

inline BOOL Read_U_b_Y8_6(void)
{
    return readOutput(Y8_6);
}

inline BOOL Read_U_b_Y8_7(void)
{
    return readOutput(Y8_7);
}

#endif
