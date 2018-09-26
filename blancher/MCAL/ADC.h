/*
 * ADC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_
#include <stdint.h>
void ADC_init(uint8_t channel);
void ADC_enable_reading(void);
uint16_t ADC_read(void);




#endif /* ADC_ADC_H_ */
