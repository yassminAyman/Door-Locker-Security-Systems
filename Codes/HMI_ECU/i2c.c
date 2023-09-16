/*
 * i2c.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Yassmin Ayman
 */

#include <avr/io.h>
#include "i2c.h"
#include "common_macros.h"
/* Description: setup and enable the TWI
 * Input: void
 * Output: void
 * */
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	/*Bit rate : speed of 400kbps , Prescalar TWPS=00, Frequency= 8 MHZ */
	TWBR = Config_Ptr->bit_rate;

	/*Prescalar:*/
	TWSR =0x00;

	/*TWCR:
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR =  (1<<TWEN);

	/*Assign my address is 0x0F*/
	TWAR = Config_Ptr->address;
}

/* Description: Start the communication by sending start bit
 * Input:  void
 * Output: void
 * */
void TWI_start(void)
{
	/*TWCR:
	 * Bit-7 TWINT: Set by 1 to clear the flag but after setup all other registers to start the TWI operation
	 * Bit-5 TWSTA: Set to become a master by sending the start condition
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR = (1<<TWINT) | (1<< TWSTA) | (1 << TWEN);

	/*Wait until the Start bit is sent and the TWINT flag is set*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/* Description: Stop the communication by sending the stop condition
 * Input: void
 * Output: void
 * */
void TWI_stop(void)
{
	/*TWCR:
	 * Bit-7 TWINT: Set by 1 to clear the flag but after setup all other registers to start the TWI operation
	 * Bit-4 TWSTO: Set to become a master
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/* Description: Write a byte
 * Input: Data (uint8)
 * Output: void
 * */
void TWI_writeByte(uint8 data)
{
	/*store the data in the data register*/
	TWDR =data;

	/*TWCR:
	 * Bit-7 TWINT: Set by 1 to clear the flag but after setup all other registers to start the TWI operation
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR = (1<<TWINT)| (1<<TWEN);

	/*Wait until the Start bit is sent and the TWINT flag is set*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

}

/* Description: read Byte and send ACK bit
 * Input: void
 * Output: data (uint8)
 * */
uint8 TWI_readByteWithACK()
{
	/*TWCR:
	 * Bit-7 TWINT: Set by 1 to clear the flag but after setup all other registers to start the TWI operation
	 * Bit-6 TWEA: Set to enable ACK bit
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

	/*Wait until the Start bit is sent and the TWINT flag is set*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	 return TWDR;
}

/* Description: read Byte and don't send ACK bit
 * Input: void
 * Output: data (uint8)
 * */
uint8 TWI_readByteWithNACK()
{
	/*TWCR:
	 * Bit-7 TWINT: Set by 1 to clear the flag but after setup all other registers to start the TWI operation
	 * Bit-6 TWEA: Clear to disable ACK bit
	 * Bit-2 TWEN:	Set for enable the TWI
	 * */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/*Wait until the Start bit is sent and the TWINT flag is set*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Read Data */
	 return TWDR;
}

/* Description: Get the status of the TWI
 * Input: void
 * Output: status (uint8)
 * */
uint8 TWI_getStatus(void)
{
    uint8 status;

    /*extract the 5 bits from 7 to 3 only and eliminate the first 3 bits*/
    status = TWSR & 0xF8;

    return status;
}
