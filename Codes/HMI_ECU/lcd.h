/*
 * lcd.h
 *
 *  Created on: Jun 17, 2023
 *      Author: Yassmin Ayman
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/***********************DEFINITIONS************************/

#define LCD_RS_PORT_ID			PORTB_ID
#define LCD_RS_PIN_ID			PIN1_ID

#define LCD_E_PORT_ID			PORTB_ID
#define LCD_E_PIN_ID			PIN2_ID

#define LCD_DATA_PORT_ID		PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/***********************LCD Commands***********************/

#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

/***********************FUNCTIONS PROTOTYPES************************/
/* Description: Initialize the LCD
 * Input: void
 * Output: void
 * */
void LCD_init();

/* Description: send command to LCD for specific purpose according
 * to the available commands
 * Input: the command code (uint8)
 * Output: void
 * */
void LCD_sendCommand(uint8 command);

/* Description: Display only a char on the LCD
 * Input: the char (uint8)
 * Output: void
 * */
void LCD_displayCharacter(uint8 data);

/* Description: Display string on the LCD
 * Input: the address of the string to be displayed
 * Output: void
 * */
void LCD_displayString(const char *Str);

/* Description: Control the position of the cursor
 * Input: the position in which row and column
 * Output: void
 * */
void LCD_moveCursor(uint8 row,uint8 col);

/* Description: Display the required string in a specified row and
 * column on the LCD
 * Input: the position in which row and column and the address of the string to be displayed
 * Output: void
 * */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/* Description: Convert the data from Integer To string
 * Input: the integer data
 * Output: void
 * */
void LCD_intgerToString(int data);

/* Description: Clear the LCD
 * Input: void
 * Output: void
 * */
void LCD_clearScreen(void);


#endif /* LCD_H_ */
