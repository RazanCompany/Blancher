#include"Frying.h"
#include "../../MCAL/DIO.h"
#include "../../GLOBAL.h"
uint16_t sensor_read(uint16_t *current_temp,uint16_t *setTemp, uint16_t *Threshold )
{
    // add value to temperature sensor
   
    float Temp = *current_temp ;
    uint16_t T = 0 , res = 0 , Light =0 ;
    uint8_t v;
    float error_temp = ((*setTemp) * 50) / 100;

    uint16_t MaxTemp , LowerTemp;
    LowerTemp = (*setTemp) - (*Threshold);
    MaxTemp   = (*setTemp) + (*Threshold);
    error_temp  += MaxTemp ;


	if(Temp < LowerTemp)
	   T = 0x00; 
	else if(Temp > MaxTemp )
	   T = 0x03;
	else if(Temp <= MaxTemp  &&Temp >= LowerTemp )
	 	T = 0x01; 

	Light = Get_light_state ();
	v = Get_gas_valve_state(); 
	res = T;
    res |= (Light<<2);
    res |= (v<<3);
    if (Temp > error_temp ) 
    {
        res = 0x02;
    }

    return res;
}

uint16_t choose_state(uint16_t reads, uint16_t *Motor_state)
{
    uint16_t val = 0 ;

    if(reads == 0x00){
        val = start_frying();
    }
    else if(reads == 0x04){
        val = Error2( );
    }
    else if(reads == 0x08){
        val = Error3( );
    }
    else if(reads == 0x0c || reads == 0x0d){
	    val = StayOn();
    }
    else if(reads == 0x01 || reads == 0x03){
	    val = StayOff();
    }
    else if(reads == 0x05){
        val = Error4( );
    }
    else if(reads == 0x09){
        val = Error5();
    }
    else if(reads == 0x07){
        val = Error6();
    }
    else if(reads == 0x0B){
        val = Error7();
    }
    else if(reads == 0x02){
        val = Error8(Motor_state);
    }
    else if(reads == 0x0f){
        val = close(Motor_state);
    }

    return val;
}

//open spark 
//open vlve
//check light 
// try twice if it false 
// retrun ok or Not
uint16_t start_frying() //0x00
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

/*_______________________________________________________________________________*/
uint16_t Error2() //0x04 Light sensor have a problem or Vlve
{//gas sesor
    Gas_valve_change_state(LOW);
   // delay(4000);
    return 2;
}

/*_______________________________________________________________________________*/
uint16_t  Error3() //0x08 logic error vlve is on and light is off
{//light failer//
    Gas_valve_change_state(LOW);
   // delay(4000);
    return 3;
}

/*_______________________________________________________________________________*/
uint16_t StayOn() //0x0c
{
 
    return OK;
}

/*_______________________________________________________________________________*/
uint16_t StayOff() //0x01
{
  
    return OK;
}

/*_______________________________________________________________________________*/
uint16_t  Error4() //0x05  error vlve is off and light is oN
{
    Gas_valve_change_state(LOW);
    return 4;
}

/*_______________________________________________________________________________*/
uint16_t Error5()//0x09  error vlve is oN and light is oFF
{
    Gas_valve_change_state(LOW);
    
    return 5;
}

/*_______________________________________________________________________________*/
uint16_t  Error6()//0x07  error vlve is oFF and light is oN
{
    Gas_valve_change_state(LOW);
    return 6;
}



uint16_t  Error7()//0x0B  error vlve is oFF and light is oN
{
   Gas_valve_change_state(LOW);
    return 7;
}
/// Error 8 
uint16_t  Error8(uint16_t * Motor_state)//0x02 Temp is over Max 
{
    * Motor_state = 0;
    //delay(4000);
    return 8;
}



uint16_t close(uint16_t * Motor_state) //0x0f
{
    * Motor_state =1;
     Gas_valve_change_state(LOW);
	 _delay_ms(1000);
	 return 1;
}





/*uint16_t check_Frying(uint16_t * Vlve)
{
    int light_val;
    light_val = Get_light_state();
    if (light_val == 1)
    {
        return 0;
    }
    set_main_Vlve();
    Set_spark ();
    Set_vlve (Vlve);
    delay (4000);
    Clear_spark();
    delay (2000);
    light_val = Get_light_state();
    if(light_val == 1)
    {
         // check is done scuessfullly
        Clear_vlve ( Vlve);
        clear_main_Vlve();
        delay (2000);
        return 1;
    }
    else
    {
        Clear_vlve (Vlve); // check Fault as the light is On 
        clear_main_Vlve();
        delay (2000);
        return 0;
    }
}
*/




