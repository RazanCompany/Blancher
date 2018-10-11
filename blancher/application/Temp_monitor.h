/*
 * Temp_monitor.h
 *
 * Created: 07/10/2018 01:16:19 م
 *  Author: ENG
 */ 


#ifndef TEMP_MONITOR_H_
#define TEMP_MONITOR_H_
#include <stdint.h>
#include "../GLOBAL.h"
void Temp_monitor_main(void* pvParameters);
gSystemError Heat ( uint16_t high_temp , uint16_t low_temp );




#endif /* TEMP_MONITOR_H_ */