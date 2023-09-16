/*
 * timer1.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Yassmin Ayman
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

/*pointer to function which store the address of the required function to be processed
 *to not to take a lot of time at the ISR
 * -static as i don't need anyone to change it
 * -volatile for no optimization as it has null value at the beginning
 * */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*ISR for the OverFlow mode*/
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function*/
		(*g_callBackPtr)();
	}
}


/*ISR for the compare mode*/
ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function*/
		(*g_callBackPtr)();
	}
}


/*void Timer1_init(const Timer1_ConfigType * Config_Ptr):
 * Description: Function to initialize the Timer driver
 * Inputs: pointer to the configuration structure with type Timer1_ConfigType.
 * Return: None
 * */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*Initial value to start count from:*/
	TCNT1=Config_Ptr->initial_value;

	/*TCCR1A:
	 *Bit 7:6 – COM1A1:0:	0
	 *Bit 5:4 – COM1B1:0: 	0
	 *Bit 3 – FOC1A: 		0
	 *Bit 2 – FOC1B:		0
	 *Bit 1:0 – WGM11:0:	determine The mode by the config pointer (Last two bits)
	 * */
	TCCR1A = (TCCR1A & 0xFC) |	((Config_Ptr->mode) & 0x03) ;

	/*TCCR1B:
	 *Bit 7 – ICNC1:		Clear as Don't care about noise canceler
	 *Bit 6 – ICES1:		Clear
	 *Bit 5 – Reserved Bit
	 *Bit 4:3 – WGM13:2:	Determine The mode by the config pointer (First two bits)
	 *Bit 2:0 – CS12:0:		Determine The Prescaler by the config pointer
	 * */

	/*To enter The required mode:*/
	TCCR1B |= (TCCR1B & 0xE7) |	(((Config_Ptr->mode) >> 2)<< WGM12) ;

	/*To enter The required Clock:*/
	TCCR1B |= (TCCR1B & 0xF8) |	(Config_Ptr->prescaler);



	/*TIMSK:
	 * Bit 5 – TICIE1:	Clear to disable Input Capture Interrupt
	 * Bit 4 – OCIE1A:	Set to Enable Output Compare A Match Interrupt if the chosen mode is the Compare mode
	 * Bit 3 – OCIE1B:	Clear to disable Output Compare B Match Interrupt
	 * Bit 2 – TOIE1:	Set to Enable Overflow Interrupt if the chosen mode is the Normal mode
	 * */

	if(Config_Ptr->mode == CTC)
	{
		/*If the mode is compare then we must assign a compare value:*/
		OCR1A=Config_Ptr->compare_value;

		/*Set to Enable Output Compare A Match Interrupt if the chosen mode is the Compare mode*/
		TIMSK = (1<<OCIE1A);
	}
	else
	{
		/*Set to Enable Overflow Interrupt if the chosen mode is the Normal mode*/
		TIMSK = (1<<TOIE1) ;
	}
	SREG |=(1<<7);
}


/*void Timer1_deInit(void):
 * Description: Function to disable the Timer1.
 * Inputs: None
 * Return: None
 * */
void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TIMSK=0;
	TCNT1 = 0;
	OCR1A=0;
	g_callBackPtr = NULL_PTR;
}


/*void Timer1_setCallBack(void(*a_ptr)(void)):
 * Description: Function to set the Call Back function address.
 * Inputs: pointer to Call Back function.
 * Return: None
 * */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
