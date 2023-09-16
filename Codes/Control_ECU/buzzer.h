/*
 * buzzer.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Yassmin Ayman
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"


/*******************************DEFINITIONS********************************/
#define BUZZER_PORT_ID		PORTD_ID
#define BUZZER_PIN_ID		PIN7_ID



/*void Buzzer_init():
 * Description: Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO.
 * Inputs: None
 * Return: None
 * */
void Buzzer_init();
/*void Buzzer_on(void):
 * Description: Function to enable the Buzzer through the GPIO.
 * Inputs: None
 * Return: None
 * */
void Buzzer_on(void);

/*void Buzzer_off(void):
 * Description: Function to disable the Buzzer through the GPIO.
 * Inputs: None
 * Return: No
 * */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
