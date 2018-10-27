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
static uint16_t app_Drum_speed = 0;

void RTE_drum_init(void){
// 	Sema_Drum_speed_handle = xSemaphoreCreateBinaryStatic(&Sema_Drum_speed_Buffer);
}


uint16_t RTE_get_Drum_speed(void){
	return Drum_speed;
}

void RTE_set_Drum_speed(uint16_t U16rteDrumSpeed){
	Drum_speed = U16rteDrumSpeed;
}



void RTE_set_app_Drum_speed(uint16_t U16rteDrumSpeed){
	app_Drum_speed = U16rteDrumSpeed;
}

uint16_t RTE_get_app_Drum_speed(void){
	uint16_t drum_speed_temp = app_Drum_speed;
	app_Drum_speed = 0;
	return drum_speed_temp;
}
