/*
 * Encoder_Task.c
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: M.Nagah
 */

#include "../ECUAL/Encoder/Encoder.h"
#include "Encoder_Tasks.h"




/*conveyor struct parameter*/
/*g_Timer_Config  g_conveyor;*/
/*Drum struct parameter*/
g_Timer_Config  g_drum;

//conveyor difference Time
/*uint32_t g_conveyor_time;*/

// Drum difference time
uint32_t g_drum_time;
/********************************protoTypeCallBack***********************************/
/*
 * call back function
 * parameters@ difference time between every ISR For Conveyor
 * return@ Nothing
 */
//static void Set_conveyor_time(uint32_t dif_time);
/*
 * call back function
 * parameters@ difference time between every ISR For Drum
 * return@ Nothing
 */
static void Set_drum_time(uint32_t dif_time);

/*
 * set_up the conveyor and Drum config 
 * parameters@ Nothing
 * return@ Nothing
 */

void Encoder_init(void)
{
	//encoder of conveyor on timer 4
// 	g_conveyor.timer_number = 4;
// 	// number of ticks 16 to interrupted
// 	g_conveyor.ticks = 16;
// 	//Call back Function 
// 	g_conveyor.isr_call_back = Set_conveyor_time;
// 	timers_init(&g_conveyor);
	
	//encoder of conveyor on timer 5
	g_drum.timer_number = 5;
	// number of ticks 16 to interrupted
	g_drum.ticks = 16;
	//Call back Function 
	g_drum.isr_call_back = Set_drum_time ; 
    timers_init(&g_drum);
}
/*
 * call back function
 * parameters@ difference time between every ISR For Conveyor
 * return@ Nothing
 */
// static void Set_conveyor_time(uint32_t dif_time)
// { 
// 	g_conveyor_time = dif_time;
// }


/*
 * To calculate the RPM oF conveyor 
 * parameters@ Nothing
 * return@ RPM for Conveyor
 */
// 
// uint16_t Conveyor_speed(void)
// {
// 	float s;
// 	uint16_t val;
// 	s = (float)(g_conveyor_time * 4) / (60000);
// 	if (s != 0 )
// 	{
// 	    s = 1 / s ;
// 	}
// 	val = round(s);
// 	return val;
// 	
// }
/*
 * To calculate the RPM oF Drum
 * parameters@ Nothing
 * return@ RPM for Drum
 */


/*
 * call back function
 * parameters@ difference time between every ISR For Drum
 * return@ Nothing
 */
static void Set_drum_time(uint32_t dif_time)
{
	g_drum_time = dif_time;
}

uint16_t Drum_speed(void)
{
	float s;
	uint16_t val;
	s = (float)(g_drum_time * 4) / (60000);
	if (s != 0 )
	{
		s = 1 / s ;
	}
	val = round(s);
	return val;
	
}