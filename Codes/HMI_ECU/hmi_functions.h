/*
 * hmi_functions.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Yassmin Ayman
 */

#ifndef HMI_FUNCTIONS_H_
#define HMI_FUNCTIONS_H_

/*********************************LIBRARIES*********************************/
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
#include "avr/interrupt.h"

/*******************************DEFINITIONS********************************/
#define ERROR	0
#define SUCCESS	1
#define OPEN_DOOR 0x45
#define CHANGE_PASSWORD 0x56
#define BUZZER 0x76
#define AGAIN	2

uint8 g_checkFlag;

/*********************************FUNCTIONS*********************************/

/*Description: Take the char from keypad and store it in any string
 * Input: meant string
 * Output: void
 * */
void enterPassword(unsigned char *str);

/*Description: A function to Create Password
 * It take the key input from the keypad and store it in the array of char  "password"
 * then the user type the password again to check it and it is store in the array  "re_password"
 * Input: Addresses of the two arrays: "password" and "re_password"
 * Output: Void
 * */
void createPassword(unsigned char *password,unsigned char *re_password);

/*Description: prepare opening door by take the logging password from keypad
 * send the pass to the control ecu to check if it match the stored pass in the EEPROM
 * and it display status of the door
 * Input: an array of sting to store the logging password ,
 * and the location of a global variable which count the timer ticks
 * Output: void
 * */
void openDoor(unsigned char *password,unsigned char *g_tick);

/*Description: prepare changing pass by take the logging password from keypad
 * send the pass to the control ecu to check if it match the stored pass in the EEPROM
 * and if it match it return to the create password function
 * Input: an array of sting to store the logging password ,
 * the location of a global variable which count the timer ticks ,
 * an array of sting to store the New password,
 * and an array of sting to store the re-enter password
 * Output: void
 * */
void changePassword(unsigned char *a_logPassword,unsigned char *password,unsigned char *re_password,unsigned char *g_tick);

#endif /* HMI_FUNCTIONS_H_ */
