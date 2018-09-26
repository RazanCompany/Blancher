/*
 * RTE_encoder.c
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: Mohab Adel
 */ 
//conveyor speed w
//drum speed    w
#include "../RTOS_Includes.h"
#include "RTE_encoders.h"


static uint16_t Conveyor_speed;
static uint16_t Drum_speed;

// void RTE_encoder_init(void){
// 	Sema_Conveyor_speed_handle = xSemaphoreCreateBinaryStatic(&Sema_Conveyor_speed_Buffer);
// 	Sema_Drum_speed_handle = xSemaphoreCreateBinaryStatic(&Sema_Drum_speed_Buffer);
// }

uint16_t RTE_get_Conveyor_speed(void){ //LCD_main call //no blocking
	return Conveyor_speed;
}

void RTE_set_Conveyor_speed(uint16_t U16rteConvetorSpeed){ //Application call
	Conveyor_speed =U16rteConvetorSpeed;
}



uint16_t RTE_get_Drum_speed(void){
	return Drum_speed;
}

void RTE_set_Drum_speed(uint16_t U16rteDrumSpeed){
	Drum_speed = U16rteDrumSpeed;
}
