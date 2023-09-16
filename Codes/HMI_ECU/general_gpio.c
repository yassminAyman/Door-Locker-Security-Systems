/*
 ============================================================================
 Name        : general_gpio.c
 Author      : Yassmin Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : GPIO
 ============================================================================
 */

#include "avr/io.h"
#include "general_gpio.h"
#include "common_macros.h"

/* Description: setup the pin direction
 * Input: port number, pin num, the required direction
 * Output: void
 * */
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_Pin_Direction direction){
	/*check if the number of ports or pins is exceed our AVR*/
	if((port_num >= NUM_OF_PORTS) || (pin_num >=NUM_OF_PINS))
	{

	}
	else
	{
		/*switch on the number of the port*/
		switch(port_num){
		case PORTA_ID:
			if(direction==Pin_OUTPUT){
				SET_BIT(DDRA,pin_num);
			}
			else{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction==Pin_OUTPUT){
				SET_BIT(DDRB,pin_num);
			}
			else{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction==Pin_OUTPUT){
				SET_BIT(DDRC,pin_num);
			}
			else{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction==Pin_OUTPUT){
				SET_BIT(DDRD,pin_num);
			}
			else{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

/* Description: write on a pin
 * Input: port number, pin number, the required value
 * Output: void
 * */
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value)
{
	/*check if the number of ports or pins is exceed our AVR*/
	if((port_num >= NUM_OF_PORTS) || (pin_num >=NUM_OF_PINS))
	{

	}
	else
	{
		/*switch on the number of the port*/
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH){
				SET_BIT(PORTA,pin_num);
			}
			else{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value== LOGIC_HIGH){
				SET_BIT(PORTB,pin_num);
			}
			else{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value== LOGIC_HIGH){
				SET_BIT(PORTD,pin_num);
			}
			else{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;

		}
	}
}

/* Description: Read data from a pin
 * Input: port number, pin number
 * Output: Read Data (uint8)
 * */
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num)
{
	uint8 pin_value= LOGIC_LOW;
	if((port_num >= NUM_OF_PORTS) || (pin_num >=NUM_OF_PINS))
	{

	}
	else
	{
		switch(port_num){
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value=  LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value=  LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value=  LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value=  LOGIC_LOW;
			}
			break;
		}

	}
	return pin_value;
}

/* Description: setup the whole Port direction
 * Input: port number, the required direction
 * Output: void
 * */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PORT_Direction direction)
{
	if(port_num >= NUM_OF_PORTS)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/* Description: write on the whole Port
 * Input: port number, the required value
 * Output: void
 * */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num >= NUM_OF_PORTS)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/* Description: Read data from The Port
 * Input: port number
 * Output: Read Data (uint8)
 * */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	if(port_num >= NUM_OF_PORTS)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}

	return value;
}
