/*
 * control_functions.h
 *
 *  Created on: Aug 31, 2023
 *      Author: Yassmin ayman
 */

#ifndef CONTROL_FUNCTIONS_H_
#define CONTROL_FUNCTIONS_H_

/*********************************LIBRARIES*********************************/
#include "uart.h"
#include <util/delay.h>
#include "eeprom.h"
#include "i2c.h"
#include "general_gpio.h"
#include "dc_motor.h"
#include "buzzer.h"

/*******************************DEFINITIONS********************************/
#define ERROR	0
#define SUCCESS	1
#define OPEN_DOOR 0x45
#define CHANGE_PASSWORD 0x56
#define BUZZER 0x76

uint8 g_checkFlag;

/*********************************FUNCTIONS*********************************/

/*Description: Check if the two passwords are the same and send the result to the HMI
 * And store the password at the EEPROM
 * Input: Addresses of the two arrays: "password" and "re_password"
 * Output: void
 * */
void checkPassword(unsigned char *password,unsigned char *re_password);

/*Description: Check if the stored password and the logging password are the same and send the result to the HMI
 * Input: Addresses of the two arrays: "password" and "logPassword"
 * Output: void
 * */
void checkLogPassword(unsigned char *password,unsigned char *logpassword);


#endif /* CONTROL_FUNCTIONS_H_ */
