//#include "WProgram.h" //Arduino library
#include <Arduino.h>
#include <Mudbus.h> //modbus library for the modbus ethernet implementation
#include <EEPROM.h> //library to control write/erase functions at EEPROM
#include <Ladder.h> //auto-generated ladder library
#include "Prototypes.h"



//Basic OpenPLC Definitions
#define ON				1
#define OFF				0
#define ERROR_MSG			-1
#define MAX_ERROR			10
#define ERROR_TIMEOUT			10000

//RS485 BUS Definitions
#define DE_PIN				20
#define LISTEN_PIN			21

//Possible PLC Status
#define RUN				1
#define STOP				2
#define HALTED				3

//PLC Status Switch Pins
#define RUN_PIN				6
#define STOP_PIN			7
#define AUTO_PIN			8

//Status Leds Pins
#define RUN_LED				5
#define ERROR_LED			3

//Boards
#define NONE				0x00
#define DISCRETE_INPUT			0x01
#define DISCRETE_OUTPUT			0x02

//OpenPLC EEPROM address
#define PROGRAMMED			0
#define PROGRAMMED_VALUE		128
#define MAC				1
#define IP				7
#define GATEWAY				11
#define SUBNET				15

/*****************************************************
 *				  INPUT DEFINITIONS  *
 *                                                   *
 * Here we are associating each OpenPLC input name   *
 * with a number, so that when  we call 'X1_3' in a  *
 * program, we are actualy calling the number '3'    *
 * that is interpreted as the 3rd input of the first *
 * input card.                                       *
 *****************************************************
*/
//1st input card
#define X1_0		0
#define X1_1		1
#define X1_2		2
#define X1_3		3
#define X1_4		4
#define X1_5		5
#define X1_6		6
#define X1_7		7
//2nd input card
#define X2_0		8
#define X2_1		9
#define X2_2		10
#define X2_3		11
#define X2_4		12
#define X2_5		13
#define X2_6		14
#define X2_7		15
//3rd input card
#define X3_0		16
#define X3_1		17
#define X3_2		18
#define X3_3		19
#define X3_4		20
#define X3_5		21
#define X3_6		22
#define X3_7		23
//4th input card
#define X4_0		24
#define X4_1		25
#define X4_2		26
#define X4_3		27
#define X4_4		28
#define X4_5		29
#define X4_6		30
#define X4_7		31
//5th input card
#define X5_0		32
#define X5_1		33
#define X5_2		34
#define X5_3		35
#define X5_4		36
#define X5_5		37
#define X5_6		38
#define X5_7		39
//6th input card
#define X6_0		40
#define X6_1		41
#define X6_2		42
#define X6_3		43
#define X6_4		44
#define X6_5		45
#define X6_6		46
#define X6_7		47
//7th input card
#define X7_0		48
#define X7_1		49
#define X7_2		50
#define X7_3		51
#define X7_4		52
#define X7_5		53
#define X7_6		54
#define X7_7		55
//8th input card
#define X8_0		56
#define X8_1		57
#define X8_2		58
#define X8_3		59
#define X8_4		60
#define X8_5		61
#define X8_6		62
#define X8_7		63

/*****************************************************
 *				 OUTPUT DEFINITIONS  *
 *                                                   *
 * Here we are associating each OpenPLC output name  *
 * with a number, so that when  we call 'Y1_3' in a  *
 * program, we are actualy calling the number '3'    *
 * that is interpreted as the 3rd output of the      *
 * first output card.                                *
 *****************************************************
*/
//1st output card
#define Y1_0		0
#define Y1_1		1
#define Y1_2		2
#define Y1_3		3
#define Y1_4		4
#define Y1_5		5
#define Y1_6		6
#define Y1_7		7
//2nd output card
#define Y2_0		8
#define Y2_1		9
#define Y2_2		10
#define Y2_3		11
#define Y2_4		12
#define Y2_5		13
#define Y2_6		14
#define Y2_7		15
//3rd output card
#define Y3_0		16
#define Y3_1		17
#define Y3_2		18
#define Y3_3		19
#define Y3_4		20
#define Y3_5		21
#define Y3_6		22
#define Y3_7		23
//4th output card
#define Y4_0		24
#define Y4_1		25
#define Y4_2		26
#define Y4_3		27
#define Y4_4		28
#define Y4_5		29
#define Y4_6		30
#define Y4_7		31
//5th output card
#define Y5_0		32
#define Y5_1		33
#define Y5_2		34
#define Y5_3		35
#define Y5_4		36
#define Y5_5		37
#define Y5_6		38
#define Y5_7		39
//6th output card
#define Y6_0		40
#define Y6_1		41
#define Y6_2		42
#define Y6_3		43
#define Y6_4		44
#define Y6_5		45
#define Y6_6		46
#define Y6_7		47
//7th output card
#define Y7_0		48
#define Y7_1		49
#define Y7_2		50
#define Y7_3		51
#define Y7_4		52
#define Y7_5		53
#define Y7_6		54
#define Y7_7		55
//8th output card
#define Y8_0		56
#define Y8_1		57
#define Y8_2		58
#define Y8_3		59
#define Y8_4		60
#define Y8_5		61
#define Y8_6		62
#define Y8_7		63

#define MAX_INPUT 64
#define MAX_OUTPUT 64
