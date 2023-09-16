/*
 * buzzer.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Yassmin Ayman
 */

#include "buzzer.h"
#include "general_gpio.h"

/*void Buzzer_init():
 * Description: Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO.
 * Inputs: None
 * Return: None
 * */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,Pin_OUTPUT);

	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW );
}

/*void Buzzer_on(void):
 * Description: Function to enable the Buzzer through the GPIO.
 * Inputs: None
 * Return: None
 * */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_HIGH);
}

/*void Buzzer_off(void):
 * Description: Function to disable the Buzzer through the GPIO.
 * Inputs: None
 * Return: No
 * */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
