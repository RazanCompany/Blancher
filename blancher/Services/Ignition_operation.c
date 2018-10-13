/*
 * Ignition_operation.c
 *
 * Created: 10/10/2018 1:33:02 PM
 *  Author: M.nagah
 */ 
#define  F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>
#include "Ignition_operation.h"
#include "../MCAL/DIO.h"
/*
 * start the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ OK or Error
 */
gSystemError Start_ignition(void)
{
	if (ignitiontype == GAS_IGNITION)
	{
		return start_gas__igintion();
	}
	else if (ignitiontype == ELECTRIC_IGNITION)
	{
		return Start_electric_igintion();
	}
	return E_Fail;// not define type
	
}
/*
 * stop the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
gSystemError Stop_ignition(void)
{
	if (ignitiontype == GAS_IGNITION)
	{
		return close_gas__igintion();
	}
	else if (ignitiontype == ELECTRIC_IGNITION)
	{
		return  close_electric__igintion();
	}
	return E_Fail;// not define type	
}




/*
 * start the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */


gSystemError start_gas__igintion(void)
{
	uint16_t count = 0 ;  //to count the number of trying turn on
	while (count < 2)
	{
		Spark_change_state(HIGH);
		Gas_valve_change_state(HIGH);
		_delay_ms(4000);
		if ( Get_light_state ())
		{
			Spark_change_state(LOW);
			return E_OK; // ok 
		}
		else
		{
			Spark_change_state(LOW);
			Gas_valve_change_state(LOW);
			_delay_ms(4000);
			count ++;
		}
	}
	return E_Fail;
}
/*
 * start the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
gSystemError Start_electric_igintion(void)
{
	Electrical_heater_change_state(HIGH);
	return E_OK;
}
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
gSystemError close_gas__igintion(void) //0x0f
{
	Gas_valve_change_state(LOW);
	_delay_ms(1000);
	if(Get_light_state ())    return E_Fail ;
	
	return E_OK;
}
/*
 * stop the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
gSystemError close_electric__igintion(void)
{
	Electrical_heater_change_state(LOW);
	return E_OK;
}