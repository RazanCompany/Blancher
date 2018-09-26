#ifndef DIO_h_
#define DIO_h_
#include <inttypes.h>
#include "../CONFIG.h"

// _______ init function _____//
void DIO_init(void);

//___________ input devices _________//
uint8_t Get_tank_level_state (uint8_t sensor_num);
uint8_t Get_blancher_level_state (void);
uint8_t Get_light_state (void);
uint8_t Get_gas_state (void);
uint8_t Salt_exist(void);



#define HIGH  1
#define LOW   0
//____________ output devices _______//
void Pump_change_state(uint8_t state);

void Powder_motor_change_state(uint8_t state);
void Conveyor_motor_change_state(uint8_t state);
uint8_t Get_conveyor_state(void);

void Tank_valve_1_change_state(uint8_t state);
void Tank_valve_2_change_state(uint8_t state);

void Blancher_valve_change_state(uint8_t state);

void Gas_valve_change_state(uint8_t state);
uint8_t Get_gas_valve_state(void);

void Main_gas_valve_change_state(uint8_t state);

void Spark_change_state(uint8_t state);
void Heater_change_state(uint8_t state);

void Modbus_change_state(uint8_t device ,uint8_t state);

void Electrical_heater_change_state(uint8_t state);
void Pre_heater_change_state(uint8_t state);








#endif /* DIO.h */
