/*
 * i2c.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Yassmin Ayman
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/* According to the I2C Status Bits codes:*/
#define TWI_START         0x08 /* start has been sent */
#define TWI_REPEATED_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_W_NACK  0x20 /* Master transmit ( slave address + Write request ) to slave + NACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MT_DATA_NACK   0x30 /* Master transmit data and NACK has been received from Slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_NACK  0x48 /* Master transmit ( slave address + Read request ) to slave + NACK received from slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


typedef uint8 TWI_Address ;
typedef uint8 TWI_BaudRate  ;

typedef struct{
 TWI_Address address;
 TWI_BaudRate bit_rate;
}TWI_ConfigType;

/* Description: setup and enable the TWI
 * Input: void
 * Output: void
 * */
void TWI_init(const TWI_ConfigType * Config_Ptr);


/* Description: Start the communication by sending start bit
 * Input:  void
 * Output: void
 * */
void TWI_start(void);

/* Description: Stop the communication by sending the stop condition
 * Input: void
 * Output: void
 * */
void TWI_stop(void);

/* Description: Write a byte
 * Input: Data (uint8)
 * Output: void
 * */
void TWI_writeByte(uint8 data);

/* Description: read Byte and send ACK bit
 * Input: void
 * Output: data (uint8)
 * */
uint8 TWI_readByteWithACK();

/* Description: read Byte and don't send ACK bit
 * Input: void
 * Output: data (uint8)
 * */
uint8 TWI_readByteWithNACK();

/* Description: Get the status of the TWI
 * Input: void
 * Output: status (uint8)
 * */
uint8 TWI_getStatus(void);



#endif /* I2C_H_ */
