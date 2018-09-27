/*
 * CRC16.h
 *
 *  Created on: Aug 16, 2018
 *      Author: Muhammad
 */

 /*

This header file provides functions for calculating
cyclic redundancy checks (CRC) using common polynomials.
Modified by Doc Walker to be processor-independent (removed inline
assembler to allow it to compile on SAM3X8E processors).
*/


#ifndef ECUAL_MODBUS_UTIL_CRC16_H_
#define ECUAL_MODBUS_UTIL_CRC16_H_

#include "inttypes.h"




uint16_t crc16_update(uint16_t crc, uint8_t a);







#endif /* ECUAL_MODBUS_UTIL_CRC16_H_ */
