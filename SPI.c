/*
 * SPI.c
 *
 *  Created on: Apr 27, 2019
 *      Author: Kareem
 */
#include "SPI.h"

void SPI_init(const SPI_ConfigType *Config_Ptr){

	// Master/Slave Select
	SPCR = (SPCR & 0xEF) | ((Config_Ptr -> master_slave) << 4);

	// Data Order
	SPCR = (SPCR & 0xDF) | ((Config_Ptr -> order) << 5);

	// Clock Rate
	SPCR = (SPCR & 0xFC) | ((Config_Ptr -> clock) & (0x03));
	SPSR = (SPSR & 0xFE) | ((Config_Ptr -> clock) & (0x04));

}

void masterPinsEnable(void){
	/*
	 * Data Direction for:
	 *
	 * SS: Slave Select
	 * MOSI: Master Output Slave Input
	 * SCK: Clock Generator
	 */
	DDRB = (1 << PB4) | (1 << PB5) | (1 << PB7); // Outputs

	/*
	 * Data direction for MISO: Master Input Slave Output
	 */
	DDRB &= (~(1 << PB6)); // Input

	// Important to enable SPI in Master Mode after setting the SS (Slave Select) as output pin
	// Enabling the SPI while the SS is configured as input pin would cause the SPI to switch to Slave Mode
	SPCR |= (1<<SPE);
}

void slavePinsEnable(void){

	DDRB = (1 << PB6); // Output

	/*
	 * Data Direction for:
	 *
	 * SS: Slave Select
	 * MOSI: Master Output Slave Input
	 * SCK: Clock Generator
	 */
	DDRB &= (~(1 << PB4)) & (~(1 << PB5)) & (~(1 << PB7)); // Inputs

	SPCR |= (1<<SPE);
}
void SPI_sendByte(uint8 byte){
	/*
	 * Receive the desired byte you want to send and store in the data register (SPDR)
	 * The master will automatically start sending with clock
	 */
	SPDR = byte;

	/*
	 * Polling until transmission is complete (waiting until SPI Interrupt flag is set)
	 * Flag is set when the whole 8-bits are transfered
	 */
	while(BIT_IS_CLEAR(SPSR, SPIF));

}
void SPI_sendString(const uint8 *string){

	while(*string != '\0')
		{
			SPI_sendByte(*string);
			string++;
		}

}
uint8 SPI_receiveByte(void){

	/*
	 * Waiting for the received byte
	 */
	while(BIT_IS_CLEAR(SPSR, SPIF));

	/*
	 * Received byte is stored in SPDR
	 */
	return SPDR;
}
void SPI_receiveString(uint8 *string){

	uint8 i = 0;
	/*
	 * Receive each character and store in the array defined in the main function
	 * The array is filled by using a pointer to character
	 */
	string[i] = SPI_receiveByte();
	while (string[i] != '#') {
		i++;
		string[i] = SPI_receiveByte();
	}
	string[i] = '\0';

	/*********************** Using Pointers ***********************/
	/*

	 *string = SPI_receiveByte();
	 while(*string != '#'){

	 string++;
	 *string = SPI_receiveByte();

	 }
	 *string = '\0';
	 */
	 /*************************************************************/
}

