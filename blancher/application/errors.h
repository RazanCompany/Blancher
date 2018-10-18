/*
 * errors.h
 *
 * Created: 07/10/2018 01:17:53 م
 *  Author: ENG
 */ 


#ifndef ERRORS_H_
#define ERRORS_H_
#include "../ECUAL/LCD.h"

//extern uint16_t g_error_number;

#define NO_ERRORS          0
#define DRUM_ERROR         DRUM_ERROR_PIC
#define OVER_TEMP_ERROR    OVER_TEMP_ERROR_PIC
#define CONVEYOR_ERROR     CONVEYOR_ERROR_PIC
#define iGNITION_TYPE      iGNITION_TYPE_PIC
#define GAS_ERROR          GAS_ERROR_PIC
#define	TANK_FEED_OPERATION_FAIL   TANK_FEED_OPERATION_FAIL_PIC
#define LEVEL_SENSORS_FAIL	LEVEL_SENSORS_FAIL_PIC
#define POWDER_TANK_FAIL	POWDER_TANK_FAIL_PIC
#define TANK_SHOULD_BE_EMPTY	TANK_SHOULD_BE_EMPTY_PIC
#define TANK_OUT_FAIL			TANK_OUT_FAIL_PIC
#define BLANCHER_EMPTY_AND_TANK_ERROR_WITH_WATER_INLET		BLANCHER_EMPTY_AND_TANK_ERROR_WITH_WATER_INLET_PIC
#define BLANCHER_LEVEL_EMPTY_AND_TANK_POWDER_DROP_ERROR		BLANCHER_LEVEL_EMPTY_AND_TANK_POWDER_DROP_ERROR_PIC


 void Set_System_error_main(uint16_t error_PIC);
 void Get_System_error_main(void);

 /*
 * Task run for ever stop the scheduler Report Errors To LCD and Close the Systems 
 *parameters@ Void Pointer
 * Return@ Nothing
 */
void Error_monitor_main(void* pvParameters);

#endif /* ERRORS_H_ */