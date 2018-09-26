/*
 * SPI.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_
#include <inttypes.h>

//initialize the SPI bus

void spi_init(void);

//shifts out 8 bits of data
//  uint8_t data - the data to be shifted out
uint8_t SPI_send(uint8_t value);

//  returns uint8_t - the data received during sending

void SPI_read_write (uint8_t *datatosend , uint8_t *recieved);




#endif /* SPI_SPI_H_ */
