/*
 * Ignition.c
 *
 * Created: 10/10/2018 1:33:02 PM
 *  Author: M.nagah
 */ 
#include <util/delay.h>
#include <stdint.h>
#include "Ignition.h"
#include "../MCAL/DIO.h"
#include "../GLOBAL.h"
/*
 * start the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
uint8_t Start_ignition()
{
	if (ignitiontype == GAS_IGNITION)
	{
		return start_gas__igintion();
	}
	else if (ignitiontype == ELECTRIC_IGNITION)
	{
		return Start_electric_igintion();
	}
	return 4;// not define type
	
}
/*
 * stop the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
uint8_t Stop_ignition()
{
	if (ignitiontype == GAS_IGNITION)
	{
		return close_gas__igintion();
	}
	else if (ignitiontype == ELECTRIC_IGNITION)
	{
		return  close_electric__igintion();
	}
	return 4;// not define type	
}




/*
 * start the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */


uint8_t start_gas__igintion() 
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
			return OK; // ok
		}
		else
		{
			Spark_change_state(LOW);
			Gas_valve_change_state(LOW);
			_delay_ms(4000);
			count ++;
		}
	}
	return Not_ok;
}
/*
 * start the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
uint8_t Start_electric_igintion()
{
	Electrical_heater_change_state(HIGH);
	return OK;
}
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
uint8_t close_gas__igintion() //0x0f
{
	Gas_valve_change_state(LOW);
	_delay_ms(1000);
	return OK;
}
/*
 * stop the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
uint8_t close_electric__igintion()
{
	Electrical_heater_change_state(LOW);
	return OK;
}