#ifndef _electric_heater_H_
#define _electric_heater_H_

uint8_t Error(uint16_t * Motor_state);



uint16_t Elc_sensor_read(uint16_t *current_temp,uint16_t *setTemp, uint16_t *Threshold );
uint8_t Elc_choose_state(uint16_t reads, uint16_t *Motor_state);
void start_electric(uint16_t *Motor_state);
void close_electric(uint16_t * Motor_state);
void StayOff_electric(uint16_t * Motor_state) ;
void StayON_electric(uint16_t * Motor_state);

#endif