/*
 * Drum.c
 *
 * Created: 10/2/2018 4:00:49 AM
 *  Author: Mohab Adel
 */ 
#include "Drum.h"
#include <stdint.h>
#include <math.h>
#include "Encoder/Encoder.h"
/*Drum struct parameter*/


// Drum difference time
uint32_t g_drum_time;

/*
 * call back function
 * parameters@ difference time between every ISR For Drum
 * return@ Nothing
 */
static void Set_drum_time_callback(uint32_t dif_time);


/*
 * call back function
 * parameters@ difference time between every ISR For Drum
 * return@ Nothing
 */
void Drum_speed_init(void){
	Encoder_init(Set_drum_time_callback, 5, 16);
	
}
static void Set_drum_time_callback(uint32_t dif_time)
{
	g_drum_time = dif_time;
}


//application call
uint16_t Drum_speed(void)
{
	float s;
	uint16_t val;
	s = (float)(g_drum_time * 4) / (60000);
	g_drum_time = 0;
	if (s != 0 )
	{
		s = 1 / s ;
	}
	val = round(s);
	return val;
	
}

