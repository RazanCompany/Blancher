
#include "../../MCAL/DIO.h"
#include "electric_heater.h"
uint8_t frying_flag = 0;

uint16_t Elc_sensor_read(uint16_t *current_temp,uint16_t *setTemp, uint16_t *Threshold )
{
    
    float Temp =  *current_temp ;
    uint8_t T_state = 0 ;
    uint16_t MaxTemp , LowerTemp;
	float error_temp = ((*setTemp) * 50) / 100;
    LowerTemp = *setTemp - *Threshold;
    MaxTemp   = *setTemp + *Threshold;
	error_temp  += MaxTemp ;
	if(Temp < LowerTemp)
	   T_state = 0x00; 
	else if(Temp > MaxTemp )
	   T_state = 0x03;
	else if(Temp <= MaxTemp  &&Temp >= LowerTemp )
	   T_state = 0x01; 
	if (Temp > error_temp ) 
    {
       T_state = 0x02;
    }
    return T_state;
}
uint8_t Elc_choose_state(uint16_t reads, uint16_t *Motor_state)
{

    if(reads == 0x00){
       start_electric(Motor_state);
    }
    else if(reads == 0x03){
	    close_electric( Motor_state);
    }
    else if(reads == 0x01 && frying_flag == 0)
    {
        StayOff_electric( Motor_state);
    }
    else if(reads == 0x01 && frying_flag == 1)
    {
        StayON_electric( Motor_state);
    }
	else
	{
		return Error(Motor_state);
	}
    return 1;

}





void start_electric(uint16_t *Motor_state)
{
	*Motor_state = 0;
    frying_flag = 1;
    Electrical_heater_change_state(HIGH);
}
void close_electric(uint16_t * Motor_state)
{  
    frying_flag = 0;
	*Motor_state = 1;
   Electrical_heater_change_state(LOW);
}
uint8_t Error(uint16_t * Motor_state)
{
	frying_flag = 0;
	*Motor_state = 0;
    Electrical_heater_change_state(LOW);
	return 2;
	
}

/*_______________________________________________________________________________*/
void StayOff_electric(uint16_t * Motor_state) 
{
   // *Motor_state = 1;
}
void StayON_electric(uint16_t * Motor_state)
{
    //*Motor_state = 1;
}
