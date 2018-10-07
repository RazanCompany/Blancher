

#include "Timer.h"
/*************************Variable*******************************************/
// Timer 1 configration parameters
g_Timer_Config *g_timer1_config;
// Timer 3 configration parameters
g_Timer_Config *g_timer3_config;
// Timer 4 configration parameters
g_Timer_Config *g_timer4_config;
// Timer 5 configration parameters
g_Timer_Config *g_timer5_config;







/*************************************************************************/


/*
 * set_up the timer and interrupt config and
 * parameters timer_ config struct contain all info about Timer
 * return 1 if the function setup OK -1 if not
 */
uint8_t timers_init(g_Timer_Config *config)
{
	//millis_init(); //start this timer to get the time between ticks

	// choose the timer number depend on the config timer_number
	if(config->timer_number == 1){

		// off all the modes of  first config register on timer
		TIMER1_CONGFIG_A = 0X00;
		// External counter on T1 and set the Top vale is OCRnA
		TIMER1_CONGFIG_B = 0x0E;
		// number of Encoder Tick for Each interrupt
		TIMER1_COMPARE = config->ticks - 1;
		// Enable interrupt Bit on the timer Mask
		SET_BIT(TIMER1_INTERUPT, TIMER1_COMPARE_INT);
		// copy the config parameter to Timer stuct
		g_timer1_config = config;
		// set the time before get ticks ISR time
		//g_Timer1_old_time = Get_millis();
	}// timer_number = 1

	else if(config->timer_number == 3)
	{
		// off all the modes of  first config register on timer
		TIMER3_CONGFIG_A = 0X00;
		//External counter on T1 and set the Top vale is OCRnA
		TIMER3_CONGFIG_B = 0x0E;
		// number of Encoder Tick for Each interrupt
		TIMER3_COMPARE = config->ticks - 1;
		// Enable interrupt Bit on the timer Mask
		SET_BIT(TIMER3_INTERUPT, TIMER3_COMPARE_INT);
		// copy the config parameter to Timer stuct
		g_timer3_config = config;
		// set the time before get ticks ISR time
		//g_Timer3_old_time = Get_millis();
	}//timer_number = 3
	else if(config->timer_number == 4){
		// off all the modes of  first config register on timer
		TIMER4_CONGFIG_A = 0X00;
		// External counter on T1 and set the Top vale is OCRnA
		TIMER4_CONGFIG_B = 0x0E;
		// number of Encoder Tick for Each interrupt
		TIMER4_COMPARE = config->ticks - 1;
		// Enable interrupt Bit on the timer Mask
		SET_BIT(TIMER5_INTERUPT, TIMER5_COMPARE_INT);
		// copy the config parameter to Timer stuct
		g_timer4_config = config;
		// set the time before get ticks ISR time
		//g_Timer4_old_time = Get_millis();
	}//timer_number = 4

	else if(config->timer_number == 5){
		// off all the modes of  first config register on timer
		TIMER5_CONGFIG_A = 0X00;
		//  External counter on T1 and set the Top vale is OCRnA
		TIMER5_CONGFIG_B = 0x0E;
		//number of Encoder Tick for Each interrupt
		TIMER5_COMPARE = config->ticks - 1;
		// Enable interrupt Bit on the timer Mask
		SET_BIT(TIMER5_INTERUPT, TIMER5_COMPARE_INT);
		// copy the config parameter to Timer struct
		g_timer5_config = config;
		// set the time before get ticks ISR time
		//g_Timer5_old_time = Get_millis();
		//Clear the counter number
		TIMER5_COUNT_L = 0;
	}//timer_number = 5

	else
	{
		//Error the timer number not valid
		return -1;
	}// Else

    sei();
    return 1;// Setup done ok
}//timer_init

// interrupted service routine when we have reach the number of  Ticks On Encoder
ISR(TIMER1_COMPA_vect)
{
	volatile uint32_t diff_time;      // to save the different between new time and old time
	volatile static uint32_t s_Timer1_old_time;
	volatile static uint32_t s_Timer1_new_time;
	// get the time now
	s_Timer1_new_time = Get_millis();
	// calculate the diff between now and last interrupt
	diff_time = s_Timer1_new_time - s_Timer1_old_time;
	// save the to the old time to next interrupt
	s_Timer1_old_time = s_Timer1_new_time;
	//call back function on upper layer to get time
	g_timer1_config->isr_call_back(diff_time);
}
// interrupted service routine when we have reach the number of  Ticks On Encoder
ISR(TIMER3_COMPA_vect)
{
	volatile uint32_t diff_time;      // to save the different between new time and old time
	volatile static uint32_t s_Timer3_old_time;
	volatile static uint32_t s_Timer3_new_time;
	// get the time now
	s_Timer3_new_time = Get_millis();
	// calculate the diff between now and last interrupt
	diff_time = s_Timer3_new_time - s_Timer3_old_time;
	// save the to the old time to next interrupt
	s_Timer3_old_time = s_Timer3_new_time;
	//call back function on upper layer to get time
	g_timer3_config->isr_call_back(diff_time);
}
// interrupted service routine when we have reach the number of  Ticks On Encoder
ISR(TIMER4_COMPA_vect)
{
	volatile uint32_t diff_time;      // to save the different between new time and old time
	volatile static uint32_t s_Timer4_old_time;
	volatile static uint32_t s_Timer4_new_time;
	// get the time now
	s_Timer4_new_time = Get_millis();
	// calculate the diff between now and last interrupt
	diff_time = s_Timer4_new_time - s_Timer4_old_time;
	// save the to the old time to next interrupt
	s_Timer4_old_time = s_Timer4_new_time;
	//call back function on upper layer to get time
	g_timer4_config->isr_call_back(diff_time);
}
// interrupted service routine when we have reach the number of  Ticks On Encoder
ISR(TIMER5_COMPA_vect)
{
	volatile uint32_t diff_time;      // to save the different between new time and old time
	volatile static uint32_t s_Timer5_old_time;
	volatile static uint32_t s_Timer5_new_time;
	//TOG_BIT(PORTB,0);
	// get the time now
	s_Timer5_new_time = Get_millis();
	// calculate the difference between now and last interrupt
	diff_time = s_Timer5_new_time - s_Timer5_old_time;
	// save the to the old time to next interrupt
	s_Timer5_old_time = s_Timer5_new_time;
	// clear the counter
	TIMER5_COUNT_L = 0;
	//call back function on upper layer to get time
	g_timer5_config->isr_call_back(diff_time);
	
}



