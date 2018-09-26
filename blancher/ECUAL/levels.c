/*
 * tank_level.c
 *
 * Created: 26/09/2018 01:00:35 ã
 *  Author: mahmoud elgendy
 */ 


#include "levels.h"
#include "../MCAL/DIO.h"

 static uint8_t g_tank_sensor = 0 ;
 static uint8_t g_blancher_level =0;
 
 uint8_t Get_tank_level(void)
 {
	g_tank_sensor = Get_tank_level_state(1) | (Get_tank_level_state(2) << 1) | (Get_tank_level_state(3) << 2) ;
	return g_tank_sensor ;
 }
 
uint8_t Get_blabcher_level(void)
{
	g_blancher_level = Get_blancher_level_state();
	return g_blancher_level ;
}


