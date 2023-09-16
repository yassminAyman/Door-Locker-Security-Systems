/*
 * hmi_main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Yassmin Ayman
 */

#include "general_gpio.h"
#include "hmi_functions.h"

/*global variable to store the number of ticks of the timer */
unsigned char g_tick=0;

/*function to be done when ISR is called*/
void TIMER1_ticks()
{
	g_tick++;
}

int main(void)
{
	/*Definitions:*/
	unsigned char password[5],re_password[5],logPassword[5];
	UART_ConfigType uartConfig = {bit_8,Disabled,bit_1,9600};
	Timer1_ConfigType timerconfig ={0,999,CLK_1024,CTC};

	/*initialize the LCD , UART and Timer1:*/
	LCD_init();
	UART_init(&uartConfig);
	Timer1_init(&timerconfig);
	Timer1_setCallBack(TIMER1_ticks);

	/*Create Password:*/
	createPassword(password,re_password);

	//If the passwords unmatched create password again, if not continue to the main menu to open the door:
	while(g_checkFlag == ERROR)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Unmatched pass");
		LCD_displayStringRowColumn(1, 3, "Try again");
		g_tick=0;
		while(g_tick <=2){};
		createPassword(password, re_password);
	}

	while(1)
	{
		unsigned char key;
		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("- : Change Pass");

		key=KEYPAD_getPressedKey();
		LCD_clearScreen();
		switch(key){
		case '+':
			openDoor(logPassword,&g_tick);
			break;
		case '-':
			changePassword(logPassword,password,re_password,&g_tick);
			break;
		}

	}
}
