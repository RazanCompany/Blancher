/*
 * RTE_temperature.h
 *
 * Created: 9/20/2018 3:09:23 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_TEMPERATURE_H_
#define RTE_TEMPERATURE_H_


void RTE_temperature_init(void);

void RTE_set_Sleep_temperature(uint16_t u16sleepTemp);
uint16_t RTE_get_Sleep_temperature(void);
void RTE_set_set_temperature(uint16_t u16setTemp);
uint16_t RTE_get_set_temperature(void);
void RTE_set_threshold_set_temperature(uint16_t u16thresholdsetTemp);
uint16_t RTE_get_threshold_set_temperature(void);
void RTE_set_threshold_sleep_temperature(uint16_t u16thresholdsleepTemp);
uint16_t RTE_get_threshold_sleep_temperature(void);
void RTE_set_positive_offset_temperature(uint16_t u16positiveOffsetTemp);
uint16_t RTE_get_positive_offset_temperature(void);
void RTE_set_negative_offset_temperature(uint16_t u16negativeOffsetTemp);
uint16_t RTE_get_negative_offset_temperature(void);
void RTE_set_Current_temperature(uint16_t u16Currenttemp);
uint16_t RTE_get_Current_temperature(void);




#endif /* RTE_TEMPERATURE_H_ */