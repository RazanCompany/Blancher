



#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdint.h>

#define GAS_IGNITION      1
#define ELECTRIC_IGNITION      2
#define OK 1
#define Not_ok 0

extern uint16_t Tank_level_1_in_letters;
extern uint16_t Tank_level_2_in_letters;
extern uint16_t Tank_level_3_in_letters;
 
extern uint16_t  gear_ratio ; // 80
extern uint16_t  distance  ; // 210 cm
extern uint16_t  gear_diameter ;  // 6 cm
extern uint16_t  motor_rpm_max ;   // 900 rpm
extern uint16_t  time_user_M ; // time of Inverter to boil by minutes
extern uint16_t  time_user_S ;
extern uint8_t ignitiontype;
#endif