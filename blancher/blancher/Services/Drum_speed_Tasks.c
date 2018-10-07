


#include "Drum_speed_Tasks.h"
#include "../ECUAL/Drum.h"
#include "../RTE/RTE_drum.h"



void Drum_speed_Tasks_init(void){
	Drum_speed_init();
}



void Drum_speed_periodic_task(void){
	RTE_set_Drum_speed(Drum_speed());
	
}