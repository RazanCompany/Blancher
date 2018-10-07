/*
 * tank_level.h
 *
 * Created: 26/09/2018 01:00:35 ã
 *  Author: ENG
 */ 


#ifndef TANK_LEVEL_H_
#define TANK_LEVEL_H_
#include <stdint.h>


#define LEVEL_OK 1
#define LEVEL_ERROR 0x55

uint8_t Get_tank_level(void);
uint8_t Get_blancher_level(void);


#endif /* LEVEL_TASK_H_ */