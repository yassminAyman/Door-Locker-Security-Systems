/*
 * hmi_functions.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Yassmin Ayman
 */

#include "hmi_functions.h"

/*Description: Take the char from keypad and store it in any string
 * Input: meant string
 * Output: void
 * */
void enterPassword(unsigned char *str)
{
	uint8 i=0;
	unsigned char key;

	LCD_moveCursor(1,0);

	key = KEYPAD_getPressedKey();
	_delay_ms(500);
	/*Store the pass in the pass string until the user press '=' which is the Enter button:*/
	while(key != '=')
	{
		i=0;
		str[i] = key;
		i++;
		LCD_displayCharacter('*');
		key = KEYPAD_getPressedKey();
		_delay_ms(500);
	}
	/*Add '#' at the end of the string for the UART transmission */
	str[i]= '#';

}

/*Description: A function to Create Password
 * It take the key input from the keypad and store it in the array of char  "password"
 * then the user type the password again to check it and it is store in the array  "re_password"
 * Input: Addresses of the two arrays: "password" and "re_password"
 * Output: Void
 * */
void createPassword(unsigned char *password,unsigned char *re_password)
{
	/*Take Password using Keypad:*/
	LCD_clearScreen();
	LCD_displayString("Enter New Pass:");
	enterPassword(password);


	/*Re-enter the password:*/
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Re-enter Pass:");
	enterPassword(re_password);

	/*Send the password and the re-password to the control ECU to check if they are equel:*/
	UART_sendString(password);
	_delay_ms(500);
	UART_sendString(re_password);

	/*receive the status of the check process*/
	g_checkFlag = UART_receiveByte();
}

/*Description: prepare opening door by take the logging password from keypad
 * send the pass to the control ecu to check if it match the stored pass in the EEPROM
 * and it display status of the door
 * Input: an array of sting to store the logging password ,
 * and the location of a global variable which count the timer ticks
 * Output: void
 * */
void openDoor(unsigned char *a_logPassword,unsigned char *g_tick)
{
	/*variable to count the number of error trying*/
	static uint8 errorCount=0;
	LCD_clearScreen();

	/*Enter Password:*/
	LCD_displayString("Plz Enter Pass:");
	enterPassword(a_logPassword);

	/*Send Password to check if it is true:*/
	UART_sendString(a_logPassword);

	/*receive the status of the check process*/
	g_checkFlag= UART_receiveByte();

	/*Decide what to do according to the check errorCount:*/
	/*If the password is true, display the door opening status*/
	if(g_checkFlag == SUCCESS)
	{
		errorCount =0;
		UART_sendByte(OPEN_DOOR);

		LCD_clearScreen();
		LCD_displayString("Door is Unlocking");
		*g_tick = 0;
		while(*g_tick <= 15){};

		/*hold the door for 3 seconds*/
		LCD_clearScreen();
		LCD_displayString("Door is Open");
		while(*g_tick <= 18){};

		LCD_clearScreen();
		LCD_displayString("Door is Locking");
		while(*g_tick <= 33){};
	}
	/*If the password is false, increment the error count
	 *and check if it's the third time error or still within range to try again*/
	else
	{
		errorCount++;
		/*if we still within the range of errors try again*/
		if(errorCount <3)
		{
			LCD_clearScreen();
			LCD_displayString("Try again");
			*g_tick=0;
			while(*g_tick <= 1){};
			openDoor(a_logPassword,g_tick);
		}
		/*if we are not within the range of errors active the buzzer
		 * and stop the device then restart*/
		else {
			LCD_clearScreen();
			LCD_displayString("ERROR");
			UART_sendByte(BUZZER);
			*g_tick=0;
			while(*g_tick <= 1){};
		}

	}
	errorCount =0;
}

/*Description: prepare changing pass by take the logging password from keypad
 * send the pass to the control ecu to check if it match the stored pass in the EEPROM
 * and if it match it return to the create password function
 * Input: an array of sting to store the logging password ,
 * the location of a global variable which count the timer ticks ,
 * an array of sting to store the New password,
 * and an array of sting to store the re-enter password
 * Output: void
 * */
void changePassword(unsigned char *a_logPassword,unsigned char *password,unsigned char *re_password,unsigned char *g_tick)
{
	/*variable to count the number of error trying*/
	static uint8 errorCount=0;
	LCD_clearScreen();

	/*Enter Password:*/
	LCD_displayString("Plz Enter Pass:");
	enterPassword(a_logPassword);

	/*Send Password to check if it is true:*/
	UART_sendString(a_logPassword);

	/*receive the status of the check process*/
	g_checkFlag= UART_receiveByte();

	UART_sendByte(CHANGE_PASSWORD);

	/*Decide what to do according to the check errorCount:*/
	/*If the password is true, start taking a new password */
	if(g_checkFlag == SUCCESS)
	{
		errorCount=0;
		createPassword(password,re_password);
	}
	/*If the password is false, increment the error count
	 *and check if it's the third time error or still within range to try again*/
	else
	{
		errorCount++;
		if(errorCount <3)
		{
			LCD_clearScreen();
			LCD_displayString("Try again");
			*g_tick=0;
			while(*g_tick <= 1){};
			changePassword(a_logPassword, password, re_password,g_tick);
		}
		else {
			LCD_clearScreen();
			LCD_displayString("ERROR");
			UART_sendByte(BUZZER);
			*g_tick=0;
			while(*g_tick <= 1){};
		}

	}
	errorCount =0;
}
