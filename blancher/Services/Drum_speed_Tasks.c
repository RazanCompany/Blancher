


#include "Drum_speed_Tasks.h"
#include "../ECUAL/Drum.h"
#include "../RTE/RTE_drum.h"
#include "../RTOS_Includes.h"


void Drum_speed_Tasks_init(void){
	Drum_speed_init();
}



void Drum_speed_periodic_task(void){
	while (1)
	{
		RTE_set_Drum_speed(Drum_speed());
		vTaskDelay(3000/portTICK_PERIOD_MS);
	}
}