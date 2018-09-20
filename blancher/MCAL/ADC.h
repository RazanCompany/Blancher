/*
 * ADC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG
 */
#include <inttypes.h>
#ifndef ADC_ADC_H_
#define ADC_ADC_H_

void ADC_init(uint8_t channel);
 void ADC_enable_reading ();
uint16_t ADC_read();




#endif /* ADC_ADC_H_ */
