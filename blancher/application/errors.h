/*
 * errors.h
 *
 * Created: 07/10/2018 01:17:53 م
 *  Author: ENG
 */ 


#ifndef ERRORS_H_
#define ERRORS_H_
#include "../ECUAL/LCD.h"

extern uint8_t g_error_number;

#define NO_ERRORS          0
#define DRUM_ERROR         DRUM_ERROR_PIC
#define OVER_TEMP_ERROR    OVER_TEMP_ERROR_PIC
#define CONVEYOR_ERROR     CONVEYOR_ERROR_PIC
#define iGNITION_TYPE      iGNITION_TYPE_PIC
#define GAS_ERROR          GAS_ERROR_PIC

 /*
 * Task run for ever stop the scheduler Report Errors To LCD and Close the Systems 
 *parameters@ Void Pointer
 * Return@ Nothing
 */
void Error_monitor_main(void* pvParameters);

#endif /* ERRORS_H_ */