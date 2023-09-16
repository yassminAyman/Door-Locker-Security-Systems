/*
 * pwm.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Yassmin Ayman
 */

#include <avr/io.h>
#include "std_types.h"

/* void PWM_Timer0_Start(uint8 duty_cycle)
 * Description:
 * The function responsible for trigger the Timer0 with the PWM Mode.
 *  Setup the PWM mode with Non-Inverting.
 *  Setup the prescaler with F_CPU/8.
 *  Setup the compare value based on the required input duty cycle
 *  Setup the direction for OC0 as output pin through the GPIO driver.
 *  The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 *  Inputs:
 *  duty_cycle: The required duty cycle percentage of the generated PWM signal. Its value should be from 0 → 100
 *  Return: None
 *  */
void PWM_Timer0_Start()
{
	DDRB|=(1<<PB3);
	/*bit 7: 		clear FOC0 as we work on PWM mode
	 *bits 6,3: 	set both WGM01 and WGM00 for PWM mode
	 *bits 5,4: 	set COM01 and clear COM00 for non_inverting PWM mode
	 *bits 0->2:	set CS01 but clear CS00 and CS02 for N=8
	 * */
	 TCCR0= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01) ;

	 /*start counting from 0*/
	 TCNT0=0;

	 /*generate signal according to the required speed:*/
	 OCR0=(uint8)(((uint32)(100*255))/100);
}
