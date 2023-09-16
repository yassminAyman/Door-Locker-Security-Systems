/*
 * control_functions.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Yassmin Ayman
 */

#include "control_functions.h"

/*Description: Check if the two passwords are the same and send the result to the HMI
 * And store the password at the EEPROM
 * Input: Addresses of the two arrays: "password" and "re_password"
 * Output: void
 * */
void checkPassword(unsigned char *password,unsigned char *re_password){
	/*Definitions:*/
	uint8 i=0;

	/*Check if the two passwords are the same:*/
	for(i=0; i<5 ;i++)
	{
		if(password[i] != re_password[i]){
			UART_sendByte(ERROR);
			g_checkFlag = ERROR;
			return ;
		}
	}

	/*if they are the same then store the password at the EEPROM*/
	for (i = 0; i < 5; i++) {
		EEPROM_writeByte(0x01F4 + i, password[i]);
		_delay_ms(10);
	}

	/*Send the status of the process of checking */
	g_checkFlag = SUCCESS;
	UART_sendByte(SUCCESS);
}

/*Description: Check if the stored password and the logging password are the same and send the result to the HMI
 * Input: Addresses of the two arrays: "password" and "logPassword"
 * Output: void
 * */
void checkLogPassword(unsigned char *password,unsigned char *logpassword){
	/*Definitions:*/
	uint8 i=0;


	/*Check if the two passwords are the same:*/
	for(i=0; i<5 ;i++)
	{
		EEPROM_readByte(0x01F4 + i, &password[i]);
		if(password[i] != logpassword[i]){
			g_checkFlag = ERROR;
			UART_sendByte(ERROR);

			return ;
		}
	}
	/*Send the status of the process of checking */
	g_checkFlag = SUCCESS;
	UART_sendByte(SUCCESS);
}
