/*
 * RTE_drum.h
 *
 * Created: 9/20/2018 3:08:46 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_DRUM_H_
#define RTE_DRUM_H_
#include <stdint.h>

void RTE_drum_init(void);

// uint16_t RTE_get_Conveyor_speed(void);
// void RTE_set_Conveyor_speed(uint16_t U16rteConvetorSpeed);

uint16_t RTE_get_Drum_speed(void);
void RTE_set_Drum_speed(uint16_t U16rteDrumSpeed);
void RTE_set_app_Drum_speed(uint16_t U16rteDrumSpeed);
uint16_t RTE_get_app_Drum_speed(void);




#endif /* RTE_DRUM_H_ */