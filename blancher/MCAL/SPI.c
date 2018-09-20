/*
 * SPI.c
 *  this file deals with SPI module and provide plenty of functions
 *  to deal with SPI .
 *      Author: Mahmoud Elgendy
 */
#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../RAL/HW_types.h"
#include "../RAL/RAL.h"




//initialize the SPI bus
uint8_t g_recieved_data ;
void spi_init(){
    //set outputs
	SET_BIT(SPI_DIRECTION_REG , MOSI_PIN);
	SET_BIT(SPI_DIRECTION_REG , SCK_PIN);
	SET_BIT(CHIP_SELECT_DIRECTION_REG , CHIP_SELECT_PIN);
    //set inputs
	CLR_BIT(SPI_DIRECTION_REG , MISO_PIN);


	//set SPI control register
	//  enable spi , master mode , MSB , FOS/16
	PUT_VAL_reg(SPI_CONTROL_REG , 0b01010001); // 0b 0111 0110

	}

//shifts out 8 bits of data
//  uint8_t data - the data to be shifted out

uint8_t SPI_send(uint8_t value){

  //shift the first byte of the value
  SPI_DATA_REG = value;
  while(!(SPSR & (1<<SPIF)));

  return SPI_DATA_REG;
}



void SPI_read_write (uint8_t *datatosend , uint8_t *recieved)
{
	// chip enable
	SET_BIT(CHIP_SELECT_PORT_REG , CHIP_SELECT_PIN);

	// send data to spi
	*recieved = SPI_send(*datatosend);

	// disable chip
	CLR_BIT(CHIP_SELECT_PORT_REG , CHIP_SELECT_PIN );

}




