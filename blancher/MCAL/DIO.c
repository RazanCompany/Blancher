/*
 * This file provides some functions to deal
 * with input / output devices such as
 * ( 3 level sensors for water tank , 1 level sensor for the blancher ,
 *  light sensor , gas sensor , conveyor_state )
 *  tank_valve_1   : responsible for feeding tank with water .
 *  tank_valve_2  : responsible for allowing the water to go out of tank .
 *  blancher_valve  : responsible for allowing the water to go out of blancher.
 *  gas valve , main gas valve  , powder motor , conveyor motor , pump
 *  spark , blower , electrical_heater .
 *
 *  author : Mahmoud Elgendy
 *  Date : 14/8/2018
 */
#include "../RAL/HW_types.h"
#include "../RAL/RAL.h"
#include "../RAL/UART_RAL.h"
#include "DIO.h"


// initialize input / output devices .
void DIO_init(void)
{
	// 3 tank level sensors as input .
	CLR_BIT(TANK_LEVEL_1_DIRECTION_REG , TANK_LEVEL_1_PIN);
	CLR_BIT(TANK_LEVEL_2_DIRECTION_REG , TANK_LEVEL_2_PIN);
	CLR_BIT(TANK_LEVEL_3_DIRECTION_REG , TANK_LEVEL_3_PIN);

	// blancher level sensor as input
	CLR_BIT(BLANCHER_LEVEL_DIRECTION_REG , BLANCHER_LEVEL_PIN);

	// salt exist >> input
	CLR_BIT(SALT_EXISTANCE_DIRECTION_REG , SALT_EXISTANCE_PIN);
	
	// SALT DROP SENSOR  >>> INPUT 
    CLR_BIT(SALT_DROP_SUCCESS_DIRECTION_REG , SALT_DROP_SUCCESS_PIN);

	// light sensor  ->> input
	CLR_BIT(LIGHT_DIRECTION_REG , LIGHT_PIN);

	// gas sensor ->> input
	CLR_BIT(GAS_DIRECTION_REG , GAS_PIN);

	// tank valve 1 ->> out
	SET_BIT(TANK_VALVE_1_DIRECTION_REG , TANK_VALVE_1_PIN);

	// tank valve 2 ->> out
	SET_BIT(TANK_VALVE_2_DIRECTION_REG , TANK_VALVE_2_PIN);

	// blancher valve  ->> out
	SET_BIT(BLANCHER_VALVE_DIRECTION_REG , BLANCHER_VALVE_PIN);

	// gas valves ->> out
	SET_BIT(GAS_VALVE_DIRECTION_REG , GAS_VALVE_PIN);
	SET_BIT(GAS_VALVE_DIRECTION_REG , GAS_VALVE_PIN);

	// powder motor ->> out
	SET_BIT(POWDER_DIRECTION_REG , POWDER_PIN);

	// initialize the conveyor motor and its sensor.
	SET_BIT(CONVEYOR_DIRECTION_REG , CONVEYOR_PIN);
	CLR_BIT(CONVEYOR_STATE_DIRECTION_REG , CONVEYOR_STATE_PIN);

	// pump ->> out
	SET_BIT(PUMP_DIRECTION_REG , PUMP_PIN);

	// spark - >> out
	SET_BIT(SPARK_DIRECTION_REG , SPARK_PIN);

	// mode bus 1 & 2 enable pins
	SET_BIT(DEVICE_0_MODBUS_DIRECTION_REG , DEVICE_0_MODBUS_PIN);
	SET_BIT(DEVICE_1_MODBUS_DIRECTION_REG , DEVICE_1_MODBUS_PIN);

	// electrical heater ->> out
	SET_BIT(ELECTRICAL_HEATER_DIRECTION_REG , ELECTRICAL_HEATER_PIN);

	// blower ->> out
	SET_BIT(BLOWER_DIRECTION_REG , BLOWER_PIN);
	
	// WATCH GOG PIN ->> out
	SET_BIT(WATCH_DOG_DIRECTION_REG , WATCH_DOG_PIN);
	
	// SAREEN PIN 
	SET_BIT(SAREEN_DIRECTION_REG , SAREEN_PIN);
	
	

	//UART2
	CLR_BIT(UART2_RX_DIRECTION_REG,UART2_RX_PIN_NUM);
	SET_BIT(UART2_TX_DIRECTION_REG,UART2_TX_PIN_NUM);
	SET_BIT(UART2_RX_DATA_REG,UART2_RX_PIN_NUM); //pull up resistor
	//UART1
	CLR_BIT(UART1_RX_DIRECTION_REG,UART1_RX_PIN_NUM);
	SET_BIT(UART1_TX_DIRECTION_REG,UART1_TX_PIN_NUM);
	SET_BIT(UART1_RX_DATA_REG,UART1_RX_PIN_NUM); //pull up resistor

}
//__________TANK LEVEL SENSORS_______________//

uint8_t Get_tank_level_state (uint8_t sensor_num)
{
	/* this function will return the state of the tank level sensors
	 * by passing the number of the sensor
	 * 1 ->> low   ,  2 ->> med   3 ->> high
	 */
	if(1 == sensor_num )
		return  !GET_BIT( TANK_LEVEL_1_STATUS_REG , TANK_LEVEL_1_PIN ) ;
	else if (2 == sensor_num)
		return  !GET_BIT( TANK_LEVEL_2_STATUS_REG , TANK_LEVEL_2_PIN ) ;
	else if (3 == sensor_num)
		return  !GET_BIT( TANK_LEVEL_3_STATUS_REG , TANK_LEVEL_3_PIN ) ;
	return -1;
}

// ________________ BLANCHER LEVEL SENSOR _________//

uint8_t Get_blancher_level_state (void)
{
	/* check the blancher level weather it is high or low */
	return   GET_BIT( BLANCHER_LEVEL_STATUS_REG , BLANCHER_LEVEL_PIN ) ;
}

//_________________ SALT EXIST _____________________//
uint8_t Salt_exist (void)
{
	/* check if there is salt in the tank or not  */
	return   GET_BIT( SALT_EXISTANCE_STATUS_REG , SALT_EXISTANCE_PIN ) ;
}

//_________________ SALT DROP SENSOR _____________________//
uint8_t Salt_dropped_successfully (void)
{
	/* check if the salt goes out successfully   */
	return   ! GET_BIT( SALT_DROP_SUCCESS_STATUS_REG , SALT_DROP_SUCCESS_PIN ) ;
}



// ________________ LIGHT SENSOR ___________________//

uint8_t Get_light_state (void)
{
	return  GET_BIT( LIGHT_STATUS_REG , LIGHT_PIN ) ;
}

//___________ GAS SENSOR __________________________//
uint8_t Get_gas_state (void)
{
	return  GET_BIT( GAS_STATUS_REG , GAS_PIN ) ;
}

//_____________ TANK VALVE ______________________//


void Tank_valve_1_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(TANK_VALVE_1_DATA_REG , TANK_VALVE_1_PIN);
	else if(LOW == state)
		CLR_BIT(TANK_VALVE_1_DATA_REG , TANK_VALVE_1_PIN);
}

// ______________ BLANCHER VALVE ____________________//

void Blancher_valve_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(BLANCHER_VALVE_DATA_REG , BLANCHER_VALVE_PIN);
	else if(LOW == state)
		CLR_BIT(BLANCHER_VALVE_DATA_REG , BLANCHER_VALVE_PIN);
}

//______________GAS VALVES _____________________//

void Gas_valve_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(GAS_VALVE_DATA_REG , GAS_VALVE_PIN);
	else if(LOW == state)
		CLR_BIT(GAS_VALVE_DATA_REG , GAS_VALVE_PIN);
}

uint8_t Get_gas_valve_state(void)
{
	return  GET_BIT( GAS_VALVE_STATUS_REG , GAS_VALVE_PIN ) ;
}

void Main_gas_valve_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(MAIN_GAS_VALVE_DATA_REG , MAIN_GAS_VALVE_PIN);
	else if(LOW == state)
		CLR_BIT(MAIN_GAS_VALVE_DATA_REG , MAIN_GAS_VALVE_PIN);
}

//_____________ POWDER mOTOR ____________________//
void Powder_motor_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(POWDER_DATA_REG , POWDER_PIN);
	else if(LOW == state)
		CLR_BIT(POWDER_DATA_REG , POWDER_PIN);
}

//____________CONVEYOR MOTOR ___________________//
void Conveyor_motor_change_state(uint8_t state)
{
	// change the conveyor motor state
	if (HIGH == state)
		SET_BIT(CONVEYOR_DATA_REG , CONVEYOR_PIN);
	else if(LOW == state)
		CLR_BIT(CONVEYOR_DATA_REG , CONVEYOR_PIN);
}

uint8_t Get_conveyor_state(void)
{
	// check whether if the conveyor motor work or not .
	return  GET_BIT( CONVEYOR_STATE_STATUS_REG , CONVEYOR_STATE_PIN ) ;
}


//__________PUMP ___________________________//


void Pump_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(PUMP_DATA_REG , PUMP_PIN);
	else if(LOW == state)
		CLR_BIT(PUMP_DATA_REG , PUMP_PIN);
}

//___________SPARK ________________________//


void Spark_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(SPARK_DATA_REG , SPARK_PIN);
	else if(LOW == state)
		CLR_BIT(SPARK_DATA_REG , SPARK_PIN);
}

//_________ MODE BUS initialize and enable______________________//

void Modbus_change_state(uint8_t device ,uint8_t state){
	
	switch (device){
		case DEVICE_0:
		 	if (HIGH == state)
		 		SET_BIT(DEVICE_0_MODBUS_DATA_REG , DEVICE_0_MODBUS_PIN);
		 	else if(LOW == state)
		 		CLR_BIT(DEVICE_0_MODBUS_DATA_REG , DEVICE_0_MODBUS_PIN);
			
			break;
		case DEVICE_1:
		     if (HIGH == state)
		         SET_BIT(DEVICE_1_MODBUS_DATA_REG , DEVICE_1_MODBUS_PIN);
		     else if(LOW == state)
		         CLR_BIT(DEVICE_1_MODBUS_DATA_REG , DEVICE_1_MODBUS_PIN);
		
			break;
		//default:
	}
	
}

// ___________ electrical heater && preheater __________//
void Electrical_heater_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(ELECTRICAL_HEATER_DATA_REG , ELECTRICAL_HEATER_PIN);
	else if(LOW == state)
		CLR_BIT(ELECTRICAL_HEATER_DATA_REG , ELECTRICAL_HEATER_PIN);
}
void Pre_heater_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(ELECTRICAL_HEATER_DATA_REG , ELECTRICAL_HEATER_PIN);
	else if(LOW == state)
		CLR_BIT(ELECTRICAL_HEATER_DATA_REG , ELECTRICAL_HEATER_PIN);
}

void Tank_valve_2_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(BLOWER_DATA_REG , BLOWER_PIN);
	else if(LOW == state)
		CLR_BIT(BLOWER_DATA_REG , BLOWER_PIN);
}

void Blower_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(TANK_VALVE_2_DATA_REG , TANK_VALVE_2_PIN);
	else if(LOW == state)
		CLR_BIT(TANK_VALVE_2_DATA_REG , TANK_VALVE_2_PIN);
}


void Watch_dog_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(WATCH_DOG_DATA_REG , WATCH_DOG_PIN);
	else if(LOW == state)
		CLR_BIT(WATCH_DOG_DATA_REG , WATCH_DOG_PIN);
}


void Sareen_change_state(uint8_t state)
{
	if (HIGH == state)
		SET_BIT(SAREEN_DATA_REG , SAREEN_PIN);
	else if(LOW == state)
		CLR_BIT(SAREEN_DATA_REG , SAREEN_PIN);
}

