/*
 * Inverter.h
 *
 * Created: 9/9/2018 10:56:37 AM
 *  Author: M.nagah
 */ 


#ifndef INVERTER_H_
#define INVERTER_H_
#include "../CONFIG.h"
/**********************Declaration*******************************************/
//Inveter  configration parameters that contain the gear ratio , diameter,distance ,MAXRpm 
typedef struct inv_configration
{
	uint16_t gear_ratio; // 80
	uint16_t distance; // 210 cm
	uint16_t gear_diameter;  // 6 cm
	uint16_t motor_rpm_max;   // 900 rpm
	uint16_t time_user_M ; // time of Inverter to boil by minutes
	uint16_t time_user_S ; // time of Inverter to boil by minutes
}g_Inveter_Config;
 
#define INVERTER_FRE_ADD 0x2001
#define INVERTER_StART_ADD 0x2000

/*
 * set the enbable pin for modbus to start send
 * parameters  Nothing
 * return Nothing
 */
void Inverter_pre_transmition(void);
/*
 * Clear the enbale pin for modbus to start send
 * parameters  Nothing
 * return Nothing
 */
void Inverter_post_transmition(void);
/*
 * set_up the Inverter Parameters
 * parameters  uart_num , baudrate, slave ID.
 * return Nothing
 */
void Inverter_init( UART_Modules uart_n, uint32_t baudrate, uint8_t slave_id);
/*
 * claculate the setting Frequancy From the Motor Parameter 
 * parameters  struct of Motor configration of RPm and distance, diameter gear ratio 
 * return Nothing
 */

void Inverter_set_Freq(g_Inveter_Config *In_cofig );
void Inverter_change_state(uint8_t stat);




#endif /* INVERTER_H_ */