/*
 * Inverter.c
 *
 * Created: 9/9/2018 10:55:57 AM
 *  Author: M.nagah
 */ 
#include "Modbus/Modbus_master.h"
#include "Inverter.h"
#include "../MCAL/DIO.h"

/*************************************************Varaibles***************************************************************/
g_Inveter_Config *Motor_config; 
float g_rpm_Motor;
static modbus_config s_inv_mod_confg; //mod bus parameters
/*************************************************************************************************************************/
/*
 * set the enable pin for modbus to start send
 * parameters  Nothing
 * return Nothing
 */
void Inverter_pre_transmition(void) {
	Modbus_change_state(INVERTER, HIGH);

}// End Function
/*
 * Clear the enable pin for modbus to start send
 * parameters  Nothing
 * return Nothing
 */
void Inverter_post_transmition(void) {
	Modbus_change_state(INVERTER, LOW);
	
}// End Function
/*
 * set_up the Inverter Parameters
 * parameters  uart_num , baudrate, slave ID.  
 * return Nothing
 */
void Inverter_init( UART_Modules uart_n, uint32_t baudrate, uint8_t slave_id )
{
	
	// Modbus Parameters
	s_inv_mod_confg.uart_num = uart_n;
	s_inv_mod_confg.baud_rate =  baudrate;
	s_inv_mod_confg.slave_address = slave_id;
	s_inv_mod_confg.post_transmission = Inverter_post_transmition;
	s_inv_mod_confg.pre_transmission = Inverter_pre_transmition;
// 	UART0_puts("Inverter init \n");
// 	UART0_puts("UART num = ");
// 	UART0_OutUDec(uart_n);
// 	UART0_puts("  baud rate = ");
// 	UART0_OutUDec(baudrate);
// 	UART0_puts("slave id ");
// 	UART0_OutUDec(slave_id);

	// init the mod bus on Mod Bus
	
	Modbus_init(INVERTER, &s_inv_mod_confg);
}// End Init

/*
 * Calculate the setting Frequency From the Motor Parameter 
 * parameters  struct of Motor configration of RPm and distance, diameter gear ratio 
 * return Nothing
 */



void Inverter_DEBUG_set_Freq(uint16_t sitting_freq){
	Modbus_Write_single_register(INVERTER,INVERTER_FRE_ADD,sitting_freq);
}

void Inverter_set_Freq(g_Inveter_Config *In_cofig )
{
	
	
	//Modbus_Write_single_register(INVERTER,0x2001,5000);// Motor speed on address 0x2001 
	Motor_config = In_cofig; // transform our data to global struct
	// calculated the whole timer
	float time_user =(float)(Motor_config->time_user_S/60) + (Motor_config->time_user_M);
	 // calculated the Rpm required For motor
	float rpm_required = (float)(Motor_config->distance *  Motor_config->gear_ratio) / (float)(time_user * (Motor_config->gear_diameter) * 22 / 7) ;
	  
	// made the range of the Rpm between 0 and RPM_MAX    
	uint16_t maxRPM =Motor_config->motor_rpm_max;
	uint16_t minRPM = maxRPM / 2;    
	if(rpm_required > maxRPM){
		    rpm_required = maxRPM;
	   }//End IF
	else if(rpm_required < minRPM){
		    rpm_required = minRPM;
	    }// END IF
	// Put the value of RPM To Global Value
    g_rpm_Motor = (float)(rpm_required)/(Motor_config->gear_ratio);
	// calculate the settings Frequency
    uint16_t sitting_freq = rpm_required * 5000  / (Motor_config->motor_rpm_max);
	    // Manual limitation for motor speed
	if(sitting_freq > 5000){
		    sitting_freq = 5000;
	}// End IF
	else if(sitting_freq < 2500){
		    sitting_freq = 2500;
	}// End IF
    //set new value 
	
	//sitting_freq-=10;
    Modbus_Write_single_register(INVERTER,INVERTER_FRE_ADD,sitting_freq);// Motor speed on address 0x2001 
		  	
}// End Function
void Inverter_change_state(uint8_t stat)
{
	if(stat == 0){
		 Modbus_Write_single_register(INVERTER,INVERTER_StART_ADD,5);  // Motor off
	}
	else if(stat == 1){
		 Modbus_Write_single_register(INVERTER,INVERTER_StART_ADD,1);    // Motor On
	 }
	
}




