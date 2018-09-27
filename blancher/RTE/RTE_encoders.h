/*
 * RTE_encoder.h
 *
 * Created: 9/20/2018 3:08:46 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_ENCODER_H_
#define RTE_ENCODER_H_
void RTE_encoder_init(void);

// uint16_t RTE_get_Conveyor_speed(void);
// void RTE_set_Conveyor_speed(uint16_t U16rteConvetorSpeed);
#include <stdint.h>
uint16_t RTE_get_Drum_speed(void);
void RTE_set_Drum_speed(uint16_t U16rteDrumSpeed);




#endif /* RTE_ENCODER_H_ */