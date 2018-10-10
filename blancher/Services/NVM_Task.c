/*
 * NVM_Task.c
 *
 * Created: 10/1/2018 11:25:04 AM
 *  Author: Muhammad
 */ 

#include <avr/eeprom.h>
#include "NVM_Task.h"

#define	EEPROM_DATA_ELEMENTS_NUMBER		16
#define	EEPROM_FIRST_DATA_ADDRESS		0

#define EEPROM_SYSTEM_ON_ADR				0
#define EEPROM_START_BLANCHER_ADR			2
#define EEPROM_WASH_OPERATION_ADR			4
#define EEPROM_TANK_CALIBRATION_ADR			6
#define EEPROM_SLEEP_TEMP_ADR				8
#define EEPROM_SET_TEMP_ADR					10
#define EEPROM_THRE_SET_TEMP_ADR			12
#define EEPROM_THRE_SLEEP_TEMP_ADR			14
#define EEPROM_POSTIVE_OFS_TEMP_ADR			16
#define EEPROM_NEGATIVE_OFS_TEMP_ADR		18
#define EEPROM_GEAR_RATIO_ADR				20
#define EEPROM_CONVAYER_LENGTH_ADR			22
#define EEPROM_DRIVER_DIAMETER_ADR			24
#define EEPROM_RPM_MAX_ADR					25
#define EEPROM_TIME_MINUTE_ADR				26
#define EEPROM_TIME_SECOND_ADR				27


typedef struct EEPROM_DATA{
	uint16_t System_on;							//system on
	uint16_t Start_blancher_operation;			//blancher start
	uint16_t Wash_operation;					//wash operation
	uint16_t Tank_calibration_operation;		//calibration operation
	uint16_t Sleep_temp;						//sleep temperature
	uint16_t Set_temp;							//set temperature
	uint16_t Threshold_set_temp;				//threshold set temperature
	uint16_t Threshold_sleep_temp;				//threshold sleep temperature
	uint16_t Positive_offset_temp;				//temperature offset +
	uint16_t Negative_offset_temp;				//temperature offset -
	uint16_t Gear_ratio;						//gear ratio
	uint16_t Conveyor_length;					//conveyor length
	uint16_t Driver_diameter;					//gear diameter
	uint16_t RPM_max;							//maximum RPM
	uint16_t Time_minute;						//time minute
	uint16_t Time_second;						//time second
	
	//no padding !!
}s_EEPROM_DATA_t;


static s_EEPROM_DATA_t		s_eeprom_data;

uint16_t *s_eeprom_data_ptr = (uint16_t*)&s_eeprom_data;

void EEPROM_READ_ALL_DATA(void){
	//call LCD_read_mutliple regs (fill the struct) and c
	for(int i=0; i<EEPROM_DATA_ELEMENTS_NUMBER; i++){
		// fill the struct with data
		s_eeprom_data_ptr[i] = eeprom_read_word( (const uint16_t *) (i*2));
	}	
}


void EEPROM_WRITE_ALL_DATA(void){
	//call LCD_read_mutliple regs (fill the struct) and c
	for(int i=0; i<EEPROM_DATA_ELEMENTS_NUMBER; i++){
		// fill the struct with data
		//eeprom_write_word( (const uint16_t *) (i*2) , s_eeprom_data_ptr[i]);
	}
}



