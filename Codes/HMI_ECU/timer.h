/*
 * timer.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Yassmin Ayman
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************DEFINITIONS********************************/

typedef enum
{
	NO_CLOCK,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024
}Timer1_Prescaler;

typedef enum
{
	NORMAL,CTC=4
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*********************************FUNCTIONS*********************************/

/*void Timer1_init(const Timer1_ConfigType * Config_Ptr):
 * Description: Function to initialize the Timer driver
 * Inputs: pointer to the configuration structure with type Timer1_ConfigType.
 * Return: None
 * */
void Timer1_init(const Timer1_ConfigType *Config_Ptr);

/*void Timer1_deInit(void):
 * Description: Function to disable the Timer1.
 * Inputs: None
 * Return: None
 * */
void Timer1_deInit(void);

/*void Timer1_setCallBack(void(*a_ptr)(void)):
 * Description: Function to set the Call Back function address.
 * Inputs: pointer to Call Back function.
 * Return: None
 * */
void Timer1_setCallBack(void(*a_ptr)(void));




#endif /* TIMER_H_ */
