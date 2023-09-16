/*
 * uart.c
 *
 *  Created on: Jul 13, 2023
 *      Author: Yassmin Ayman
 */

#include "uart.h"

#include  <avr/io.h>
#include "common_macros.h"

/* Description: setup and enable the UART
 * Input: Pointer To structure that contain several enum for configuration
 * Output: void
 * */
void UART_init(const UART_ConfigType *Config_Ptr){

	uint16 UBRR =0;

	/*UCSRA:
	 * bit 1: set U2X for double speed
	 * */
	UCSRA = 1<<U2X;

	/*UCSRB:
	 *BIT 7: clear RXCIE for disable Rx interrupt
	 *BIT 6: clear TXCIE for disable Tx interrupt
	 *BIT 5: clear UDRIE for disable empty reg. interrupt
	 *bit 4: set RXEN to enable receiver
	 *bit 3: set TXEN to enable transmitter
	 *bit 2: INSERT by config pointer char size
	 * */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*Insert bit 2 according to the data bit number which is chosen using config pointer*/
	UCSRB |= (UCSRB & 0xFB) | ((Config_Ptr->bit_data &(0x04))<<UCSZ2) ;

	/*UCSRC:
	 * bit 7: 	set for write in the register
	 * bit 6: 	clear for Asynchronous mode
	 * bit 5,4: INSERT by config pointer mode of parity
	 * bit 3: 	 INSERT by config pointer number of stop bits
	 * bit 2,1: INSERT by config pointer char size
	 * */
	UCSRC = (1<<URSEL) ;

	/*Insert bits 5,4 according to the Parity mode which is chosen using config pointer*/
	UCSRC |= (UCSRC & 0xCF) | ((Config_Ptr->parity)<<UPM0);

	/*Insert bit 3 according to the STOP bit number which is chosen using config pointer*/
	UCSRC |= (UCSRC & 0xF7) | ((Config_Ptr->stop_bit)<<USBS);

	/*Insert bits 2,1 according to the data bit number which is chosen using config pointer*/
	UCSRC |= (UCSRC & 0xF9) | ((Config_Ptr->bit_data)<<UCSZ0);


	/*Equation for calculate UBRR value:*/
	UBRR =(uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);

	/*enter the last 8 bits in UBRRL:*/
	UBRRL = UBRR;
	/*Enter the first 4 bits in UBRRH:*/
	UBRRH = (UBRR>>8);
}


/* Description: Send the data from UDR
 * Input: data to be sent
 * Output: void
 * */
void UART_sendByte(uint8 data){
	/*check if the UDR register is empty*/
	while(BIT_IS_CLEAR(UCSRA,5)){}

	/*Write the data to be sent*/
	UDR = data;
}


/* Description: Receive data from UART from the UDR
 * Input: void
 * Output: uint8 (data)
 * */
uint8 UART_receiveByte(){
	/*check if the UDR register received all the data*/
	while(BIT_IS_CLEAR(UCSRA,7)){}

	/*Read the received data*/
	return UDR;
}


/* Description: Send string using UART
 * Input:  location of the string that will be sent
 * Output: void
 * */
void UART_sendString(const uint8 *str){
	uint8 i=0;
	/*extract each char(byte) and send it byte by byte*/
	while(str[i] != '\0'){
		UART_sendByte(str[i]);
		i++;
	}
}

/* Description: Receive string using UART
 * Input:  Address of the string that will be store the received data
 * Output: void
 * */
void UART_receiveString(uint8 *str){
	uint8 i=0;

	/*Receive first byte*/
	str[i] = UART_receiveByte();

	/*check if it's the last byte*/
	while(str[i] != '#'){
		i++;
		/*receive byte by byte until the # and store in the address of the str*/
		str[i]=UART_receiveByte();
	}

	/*Add the null sign to form the popular form of a string to use it later*/
	str[i] = '\0';
}
