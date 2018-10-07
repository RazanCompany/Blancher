/*
 * RTE_invertersetting.h
 *
 * Created: 9/20/2018 3:14:48 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_INVERTERSETTING_H_
#define RTE_INVERTERSETTING_H_

void RTE_invertersetting_init(void);


void RTE_set_Gear_ratio(uint16_t u16GearRatio);
uint16_t RTE_get_Gear_ratio(void);
void RTE_set_RPM_max(uint16_t u16RPMmax);
uint16_t RTE_get_RPM_max(void);
void RTE_set_Conveyor_length(uint16_t u16ConveyorLength);
uint16_t RTE_get_Conveyor_length(void);
void RTE_set_Driver_diameter(uint16_t u16Driverdiameter);
uint16_t RTE_get_Driver_diameter(void);
void RTE_set_Time_minute(uint16_t u16Timeminute);
uint16_t RTE_get_Time_minute(void);
void RTE_set_Time_second(uint16_t u16Timesecond);
uint16_t RTE_get_Time_second(void);

#endif /* RTE_INVERTERSETTING_H_ */