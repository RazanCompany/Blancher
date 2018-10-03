/*
 * RTE_drum.c
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: Mohab Adel
 */ 
//
//drum speed    w
#include "../RTOS_Includes.h"
#include "RTE_drum.h"


/*static uint16_t Conveyor_speed;*/
static uint16_t Drum_speed = 0;

void RTE_drum_init(void){
// 	Sema_Drum_speed_handle = xSemaphoreCreateBinaryStatic(&Sema_Drum_speed_Buffer);
}


uint16_t RTE_get_Drum_speed(void){
	return Drum_speed;
}

void RTE_set_Drum_speed(uint16_t U16rteDrumSpeed){
	Drum_speed = U16rteDrumSpeed;
}
