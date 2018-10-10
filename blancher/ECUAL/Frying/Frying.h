#ifndef Frying_h
#define Frying_h
#include <stdint.h>
#include <util/delay.h>


uint16_t sensor_read(uint16_t *current_temp , uint16_t *setTemp, uint16_t *Threshold );

uint16_t choose_state(uint16_t reads,  uint16_t * Motor_state);

uint16_t  start_frying(void);
uint16_t  Error2(void);
uint16_t  Error3(void);
uint16_t  StayOn(void);
uint16_t  StayOff(void);
uint16_t  Error4(void);
uint16_t  Error5(void);
uint16_t  Error6(void);
uint16_t  Error7(void);
uint16_t  Error8(uint16_t * Motor_state);
uint16_t  close(uint16_t * Motor_state);

//uint16_t check_Frying(uint16_t * Vlve);

#endif