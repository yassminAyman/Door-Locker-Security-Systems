/*
 * dcmotor.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Yassmin Ayman
 */

#include "dc_motor.h"
#include "pwm.h"

/*void DcMotor_Init(void):
 * Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 * Inputs: None
 * Return: None
 * */
void DcMotor_Init(void)
{
	/*Directions:*/
	GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_FIRST_INPUT_PIN_ID, Pin_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_SECOND_INPUT_PIN_ID, Pin_OUTPUT);

	/*init_state:*/
	GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_INPUT_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECOND_INPUT_PIN_ID, LOGIC_LOW);
}

/*void DcMotor_Rotate(DcMotor_State state,uint8 speed):
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 * Inputs:
 * state: The required DC Motor state, it should be CW or A-CW or stop.
 * DcMotor_State data type should be declared as enum or uint8.
 * For example, if the input is 50, The motor should rotate with 50% of its maximum speed.
 * Return: None
 * */
void DcMotor_Rotate(DcMotor_State state)
{
	PWM_Timer0_Start();

	if(state==CW)
	{
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_INPUT_PIN_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECOND_INPUT_PIN_ID,LOGIC_HIGH);
	}
	else if(state==A_CW)
	{
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_INPUT_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECOND_INPUT_PIN_ID,LOGIC_LOW);
	}
	else if(state==stop)
	{
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_FIRST_INPUT_PIN_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_SECOND_INPUT_PIN_ID,LOGIC_LOW);
	}
}
