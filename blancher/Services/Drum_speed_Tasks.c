


#include "Drum_speed_Tasks.h"
#include "../ECUAL/Drum.h"
#include "../RTE/RTE_drum.h"
#include "../RTOS_Includes.h"


uint16_t drum_speed = 0;

void Drum_speed_Tasks_init(void){
	Drum_speed_init();
}



void Drum_speed_periodic_task(void){
	while (1)
	{
		drum_speed = Drum_speed();
		RTE_set_Drum_speed(drum_speed);
		RTE_set_app_Drum_speed(drum_speed);
		vTaskDelay(3000/portTICK_PERIOD_MS);
	}
}