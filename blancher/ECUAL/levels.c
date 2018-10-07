/*
 * tank_level.c
 *
 * Created: 26/09/2018 01:00:35 ã
 *  Author: Mahmoud elgendy
 */ 


#include "levels.h"
#include "../MCAL/DIO.h"

 
 uint8_t Get_tank_level(void)
 {
	uint8_t Tank_sensor = 0 ;
	Tank_sensor = Get_tank_level_state(1) | (Get_tank_level_state(2) << 1) | (Get_tank_level_state(3) << 2) ;
	if (Tank_sensor == 2 || Tank_sensor == 4 || Tank_sensor == 5 || Tank_sensor == 6  )
	{
		return LEVEL_ERROR ;
	}
	if(Tank_sensor == 3) Tank_sensor =2;
	if(Tank_sensor == 7) Tank_sensor =3;
	return Tank_sensor ;
 }
 
uint8_t Get_blancher_level(void)
{
	uint8_t Blancher_level =0;
	Blancher_level = Get_blancher_level_state();
	return Blancher_level ;
}


