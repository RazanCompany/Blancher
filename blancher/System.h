/*
 * System.h
 *
 * Created: 9/26/2018 7:00:16 AM
 *  Author: Mohab Adel
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_


typedef enum{
	E_OK=0,
	E_Fail,
	E_SALT_fail,
	E_INLET_FLOW_fail , 
	E_OUTLET_FLOW_fail,
	E_DRUM_ENCODER_fail,
	E_CONVOYER_ENCODER_fail,
	E_SALT_MOTER_ENCODER_fail,
	E_FLAME_Fail,
	E_IGNITION_Fail,
	E_NO_SALT_IN_TANK_Fail,
	E_SALT_DROP_Fail
	
	

}gSystemError;

gSystemError System_init(void);

#endif /* SYSTEM_H_ */