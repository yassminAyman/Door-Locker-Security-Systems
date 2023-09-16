/*
 * uart.h
 *
 *  Created on: Jul 13, 2023
 *      Author: Yassmin Ayman
 */

#ifndef UART_H_
#define UART_H_

/*********************************LIBRARIES*********************************/
#include "std_types.h"


/*******************************DEFINITIONS********************************/

/*It's been used when we need to synchronous the data transfer
 * between two MC if one of them need to prepare*/
#define MC2_ready 0x10

/*enum s for the Dynamic configuration */
typedef enum
{
	bit_5,bit_6,bit_7,bit_8,bit_9
}UART_BitData;

typedef enum
{
	Disabled,Reserved,Even,Odd
}UART_Parity;

typedef enum
{
	bit_1,bit_2
}UART_StopBit;

typedef uint32 UART_BaudRate;

typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;


/*********************************FUNCTIONS*********************************/

/* Description: setup and enable the UART
 * Input: Pointer To structure that contain several enum for configuration
 * Output: void
 * */
void UART_init(const UART_ConfigType *Config_Ptr);

/* Description: Send the data from UDR
 * Input: data to be sent
 * Output: void
 * */
void UART_sendByte(uint8 data);

/* Description: Receive data from UART from the UDR
 * Input: void
 * Output: uint8 (data)
 * */
uint8 UART_receiveByte(void);

/* Description: Send string using UART
 * Input:  location of the string that will be sent
 * Output: void
 * */
void UART_sendString(const uint8 *str);

/* Description: Receive string using UART
 * Input:  Address of the string that will be store the received data
 * Output: void
 * */
void UART_receiveString(uint8 *str);


#endif /* UART_H_ */
