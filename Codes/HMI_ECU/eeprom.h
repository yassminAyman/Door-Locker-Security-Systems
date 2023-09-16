/*
 * eeprom.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Yassmin Ayman
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#define ERROR 0
#define SUCCESS 1

/* Description: Save a byte at the external EEPROM
 * Input: the address in the EEPROM , and data to be stored
 * Return: The status of the process
 * */
uint8 EEPROM_writeByte(uint16 address, uint8 data);

/* Description: Read a byte that is stored at the external EEPROM
 * Input: the address in the EEPROM , pointer to a var to store the readed data
 * Return: The status of the process
 * */
uint8 EEPROM_readByte(uint16 address, uint8 *data);


#endif /* EEPROM_H_ */
