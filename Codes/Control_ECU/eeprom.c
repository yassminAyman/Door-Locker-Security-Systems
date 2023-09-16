/*
 * eeprom.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Yassmin Ayman
 */

#include "eeprom.h"
#include "i2c.h"

/* Description: Save a byte at the external EEPROM
 * Input: the address in the EEPROM , and data to be stored
 * Return: The status of the process
 * */
uint8 EEPROM_writeByte(uint16 address, uint8 data)
{
	/* Send the Start Bit */
	TWI_start();
	/*Check if it's Sent*/
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*Send the device address:
	 * 0b1010 + [ A10 A9 A8 (from the EEPROM address) ] by masking + Write bit identifier (0)
	 * */
	TWI_writeByte((uint8)(0xA0 | ((address & 0x0700)>>7)));
	/*Check if the master transmit the address of the slave and the slave response by ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}


	/*Send the cont. of the device address which is the memory location:*/
	TWI_writeByte((uint8)address);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}


	/* write data to eeprom */
	TWI_writeByte(data);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}


	/* Send the Stop Bit */
	TWI_stop();


	return SUCCESS;
}

/* Description: Read a byte that is stored at the external EEPROM
 * Input: the address in the EEPROM , pointer to a var to store the readed data
 * Return: The status of the process
 * */
uint8 EEPROM_readByte(uint16 address, uint8 *data)
{
	/* Send the Start Bit */
	TWI_start();
	/*Check if it's Sent*/
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*Send the device address:
	 * 0b1010 + [ A10 A9 A8 (from the EEPROM address) ] by masking + Write bit identifier (0)
	 * */
	TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7)));
	/*Check if the master transmit the address of the slave and the slave response by ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}


	/*Send the cont. of the device address which is the memory location:*/
	TWI_writeByte((uint8)address);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}


	/* Send the Start Bit to Change the flow of the data*/
	TWI_start();
	/*Check if it's Sent*/
	if(TWI_getStatus() != TWI_REPEATED_START
	)
	{
		return ERROR;
	}


	/*Send the device address:
	 * 0b1010 + [ A10 A9 A8 (from the EEPROM address) ] by masking + Read bit identifier (1)
	 * */
	TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7) | 1));
	/*Check if the master transmit the address of the slave and the slave response by ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
	{
		return ERROR;
	}



	/* Read Byte from Memory without send ACK */
	*data = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;



	/* Send the Stop Bit */
	TWI_stop();



	return SUCCESS;


}
