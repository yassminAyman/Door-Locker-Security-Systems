/*
 * keypad.h
 *
 *  Created on: Jun 16, 2023
 *      Author: Yassmin Ayman
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************Definations*******************************/
#define KEYPAD_NUM_ROWS			4
#define KEYPAD_NUM_COLS			4
//#define STANDARD_KEYPAD

#define KEYPAD_ROW_PORT_ID                PORTC_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTC_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED 			 LOGIC_HIGH

/*******************************FUNCTIONS PROTOTYPES *******************************/
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
