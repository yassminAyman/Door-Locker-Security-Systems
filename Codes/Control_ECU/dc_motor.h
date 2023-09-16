/*
 * dc_motor.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Yassmin Ayman
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "general_gpio.h"
#include "std_types.h"

/***************************************DEFINATIONS***************************************/
#define MOTOR_PORT_ID					PORTB_ID
#define MOTOR_FIRST_INPUT_PIN_ID		PIN0_ID
#define MOTOR_SECOND_INPUT_PIN_ID		PIN1_ID

/***************************************DATA TYPES***************************************/
typedef enum {
	CW,A_CW,stop
}DcMotor_State ;

/**********************************FUNCTIONS PROTOTYPES**********************************/

/*void DcMotor_Init(void):
 * Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 * Inputs: None
 * Return: None
 * */
void DcMotor_Init(void);

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
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
