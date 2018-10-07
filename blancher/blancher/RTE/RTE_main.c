/*
 * RTE_main.c
 *
 * Created: 9/26/2018 6:50:41 AM
 *  Author: Mohab Adel
 */ 

#include "RTE_error_types.h"
#include "RTE_drum.h"
#include "RTE_invertersetting.h"
#include "RTE_operations.h"
#include "RTE_levels.h"
#include "RTE_temperature.h"
#include "RTE_main.h"

void RTE_init(void){
	RTE_drum_init();
	RTE_invertersetting_init();
	RTE_operations_init();
	RTE_levels_init();
	RTE_temperature_init();
	
}