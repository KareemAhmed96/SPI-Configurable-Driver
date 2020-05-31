# SPI-Configurable-Driver
AVR ATmega32 Serial Peripheral Interface Software Driver that is highly configurable.

Example to use this driver:
---------------------------

```
int main()
{
	/* 
	 * Declaring a structure called "SPI_Config" of type "SPI_ConfigType"
	 * Then giving it's members the following parameters:
	 * Most Significant Bit First: MSB_FIRST
	 * Clock Frequency = 4MHZ: F_CLOCK_4
	 * Master or Slave Selection: MASTER
	 */
	
	SPI_ConfigType SPI_Config = {MSB_FIRST,F_CLOCK_4,MASTER};


	// Passing the structure by address to the initialization function as input parameters
	
	SPI_init(&SPI_ConfigType);
}
```
