/*
 * SPI.h
 *
 *  Created on: Apr 27, 2019
 *      Author: Kareem
 */

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

typedef enum
{
	MSB_FIRST,LSB_FIRST
}SPI_DataOrder;

typedef enum
{
	F_CLOCK_4,F_CLOCK_16,F_CLOCK_64,F_CLOCK_128,F_CLOCK_2,F_CLOCK_8,F_CLOCK_32
}SPI_ClockRate;

typedef enum
{
	SLAVE,MASTER
}SPI_Master_Slave_Select;

typedef struct
{
	SPI_DataOrder order;
	SPI_ClockRate clock;
	SPI_Master_Slave_Select master_slave;
}SPI_ConfigType;

/*
 * Function Prototypes
 */
void SPI_init(const SPI_ConfigType * Config_Ptr);

void slavePinsEnable(void);
void masterPinsEnable(void);

void SPI_sendByte(uint8 byte);
void SPI_sendString(const uint8 *string);

uint8 SPI_receiveByte(void);
void SPI_receiveString(uint8 *string);

/*
 * Function to set the data order
void SPI_setDataOrder(const SPI_DataOrder a_dataOrder){

	SPCR = (SPCR & 0b11011111) | (a_dataOrder<<5); // (SPCR & 0xDF)
}
*/


#endif /* SPI_H_ */
