/*
 * control_main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Yassmin Ayman
 */

#include "control_functions.h"
#include "timer.h"

/*global variable to store the number of ticks of the timer */
unsigned char g_tick=0;

/*function to be done when ISR is called*/
void TIMER1_ticks()
{
	g_tick++;
}

int main(void)
{
	/*Definitions:*/
	uint8 i=0;
	unsigned char password[6],re_password[6],logPassword[6];
	UART_ConfigType uartConfig = {bit_8,Disabled,bit_1,9600};
	TWI_ConfigType Congi={0x02,0x02};
	Timer1_ConfigType timerconfig ={0,999,CLK_1024,CTC};

	/*UART, TWI, DC-motor, buzzer and timer initialization:*/
	UART_init(&uartConfig);
	TWI_init(&Congi);
	DcMotor_Init();
	Buzzer_init();
	Timer1_init(&timerconfig);
	Timer1_setCallBack(TIMER1_ticks);

	/*Receive the two strings from HMI_ECU and check if they are the same and the check send flag*/
	UART_receiveString(password);
	UART_receiveString(re_password);
	checkPassword(password,re_password);

	/*if the password and re password not matched try again*/
	while(g_checkFlag == ERROR)
	{
		UART_receiveString(password);
		UART_receiveString(re_password);
		checkPassword(password,re_password);
	}


	while(1)
	{
		/*recieve log password and check it with our saved password*/
		UART_receiveString(logPassword);
		checkLogPassword(password,logPassword);

		/*if the logging password is not true try again
		 * within the allowed number of errors */
		while((g_checkFlag == ERROR) && (i<2))
		{
			UART_receiveString(logPassword);
			checkLogPassword(password,logPassword);
			i++;
		}
		i=0;

		/*Receive the flag from HMI that specify the required process*/
		uint8 option;
		option= UART_receiveByte();

		switch(option){
		case OPEN_DOOR:
			g_tick = 0;
			DcMotor_Rotate(CW);
			while(g_tick <= 15){};
			DcMotor_Rotate(stop);
			while(g_tick <= 18){};
			DcMotor_Rotate(A_CW);
			while(g_tick <= 33){};
			DcMotor_Rotate(stop);
			break;

		case CHANGE_PASSWORD:
			UART_receiveString(password);
			UART_receiveString(re_password);
			checkPassword(password,re_password);
			/*if the password and re password not matched try again*/
			while(g_checkFlag == ERROR)
			{
				UART_receiveString(password);
				UART_receiveString(re_password);
				checkPassword(password,re_password);
			}
			break;

		case BUZZER:
			Buzzer_on();
			g_tick=0;
			while(g_tick <= 1){};
			Buzzer_off();
			break;
		}
	}
}
