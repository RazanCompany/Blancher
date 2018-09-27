/*
 * this file define the used registers
 * in the system
 * author : Mahmoud Elgendy
 * date : 14/8/2018
 */


#ifndef RAL_H_
#define RAL_H_

#include <avr/io.h>


//___________TANK LOW LEVEL SENSOR _________//
#define TANK_LEVEL_1_DIRECTION_REG  DDRL
#define TANK_LEVEL_1_DATA_REG       PORTL
#define TANK_LEVEL_1_STATUS_REG     PINL
#define TANK_LEVEL_1_PIN            5

//___________TANK MEDILLE LEVEL SENSOR______//
#define TANK_LEVEL_2_DIRECTION_REG  DDRL
#define TANK_LEVEL_2_DATA_REG       PORTL
#define TANK_LEVEL_2_STATUS_REG     PINL
#define TANK_LEVEL_2_PIN            6

//___________TANK HIGH LEVEL SENSOR _______//
#define TANK_LEVEL_3_DIRECTION_REG  DDRL
#define TANK_LEVEL_3_DATA_REG       PORTL
#define TANK_LEVEL_3_STATUS_REG     PINL
#define TANK_LEVEL_3_PIN            4

//__________ BLANCHER LEVEL SENSOR_________//
#define BLANCHER_LEVEL_DIRECTION_REG  DDRD
#define BLANCHER_LEVEL_DATA_REG       PORTD
#define BLANCHER_LEVEL_STATUS_REG     PIND
#define BLANCHER_LEVEL_PIN            3

//_________ SALT EXISTANCE ________________//
#define SALT_EXISTANCE_DIRECTION_REG  DDRB
#define SALT_EXISTANCE_DATA_REG       PORTB
#define SALT_EXISTANCE_STATUS_REG     PINB
#define SALT_EXISTANCE_PIN            0


// ________ GAS LECKAGE SENSOR ___________//
#define GAS_DIRECTION_REG  DDRD
#define GAS_DATA_REG       PORTD
#define GAS_STATUS_REG     PIND
#define GAS_PIN            4

//_________ LIGHT SENSOR ________________//
#define LIGHT_DIRECTION_REG  DDRD
#define LIGHT_DATA_REG       PORTD
#define LIGHT_STATUS_REG     PIND
#define LIGHT_PIN            5

//_________PUMP _________________________//
#define PUMP_DIRECTION_REG  DDRD
#define PUMP_DATA_REG       PORTD
#define PUMP_STATUS_REG     PIND
#define PUMP_PIN            6

//_________POWDER MOTOR ________________//
#define POWDER_DIRECTION_REG  DDRD
#define POWDER_DATA_REG       PORTD
#define POWDER_STATUS_REG     PIND
#define POWDER_PIN            7

// ________CONVOYER MOTOR _____________//
#define CONVEYOR_DIRECTION_REG  DDRC
#define CONVEYOR_DATA_REG             PORTC
#define CONVEYOR_STATUS_REG           PINC
#define CONVEYOR_PIN                  0

// _______CONVEROR STATE SENSOR ________//
#define CONVEYOR_STATE_DIRECTION_REG        DDRC
#define CONVEYOR_STATE_DATA_REG             PORTC
#define CONVEYOR_STATE_STATUS_REG           PINC
#define CONVEYOR_STATE_PIN                  0

//________gas valve __________________//
#define GAS_VALVE_DIRECTION_REG        DDRC
#define GAS_VALVE_DATA_REG             PORTC
#define GAS_VALVE_STATUS_REG           PINC
#define GAS_VALVE_PIN                  1

//_______main gas ____________________//
#define MAIN_GAS_VALVE_DIRECTION_REG  DDRC
#define MAIN_GAS_VALVE_DATA_REG             PORTC
#define MAIN_GAS_VALVE_STATUS_REG           PINC
#define MAIN_GAS_VALVE_PIN                  2

//_______ SPARK _______________________//
#define SPARK_DIRECTION_REG        DDRC
#define SPARK_DATA_REG             PORTC
#define SPARK_STATUS_REG           PINC
#define SPARK_PIN                  3

//______ TANK VALVE 1 ___________________//
#define TANK_VALVE_1_DIRECTION_REG        DDRC
#define TANK_VALVE_1_DATA_REG             PORTC
#define TANK_VALVE_1_STATUS_REG           PINC
#define TANK_VALVE_1_PIN                  4

//_______ BLANCHER VALVE ______________//
#define BLANCHER_VALVE_DIRECTION_REG        DDRC
#define BLANCHER_VALVE_DATA_REG             PORTC
#define BLANCHER_VALVE_STATUS_REG           PINC
#define BLANCHER_VALVE_PIN                  5

//_______  MODE BUS 1 ____________________//
#define DEVICE_0_MODBUS_DIRECTION_REG        DDRJ
#define DEVICE_0_MODBUS_DATA_REG             PORTJ
#define DEVICE_0_MODBUS_STATUS_REG           PINJ
#define DEVICE_0_MODBUS_PIN                  2

//_______  MODE BUS 2 ____________________//
#define DEVICE_1_MODBUS_DIRECTION_REG        DDRC
#define DEVICE_1_MODBUS_DATA_REG             PORTC
#define DEVICE_1_MODBUS_STATUS_REG           PINC
#define DEVICE_1_MODBUS_PIN                  7

//_______  electrical_heater ____________________//
#define ELECTRICAL_HEATER_DIRECTION_REG        DDRC
#define ELECTRICAL_HEATER_DATA_REG             PORTC
#define ELECTRICAL_HEATER_STATUS_REG           PINC
#define ELECTRICAL_HEATER_PIN                  7

//_______  blower  ____________________//
#define BLOWER_DIRECTION_REG        DDRC
#define BLOWER_DATA_REG             PORTC
#define BLOWER_STATUS_REG           PINC
#define BLOWER_PIN                  7

//_______  TANK_VALVE_2 ____________________//
#define TANK_VALVE_2_DIRECTION_REG        DDRC
#define TANK_VALVE_2_DATA_REG             PORTC
#define TANK_VALVE_2_STATUS_REG           PINC
#define TANK_VALVE_2_PIN                  7


/*
 * ADC Registers !!!!
 */
#define ADC_DIRECTION_REG                    DDRF
#define ADC_CHANEL                           0
#define ADC_MULTIPLEXER_SELECTION_REG        ADMUX
#define ADC_CONTROL_STATUS_B_REG             ADCSRB
#define ADC_CONTROL_STATUS_A_REG             ADCSRA
#define ADC_START_CONVERSION_bit             6
#define ADC_DATA_REG_HIGH                    ADCH
#define ADC_DATA_REG_LOW                     ADCL


//______Spi registers ________________________//
#define SPI_DIRECTION_REG        DDRB
#define SPI_PORT_REG             PORTB
#define MOSI_PIN                 2
#define MISO_PIN                 3
#define SCK_PIN                  1
#define SS_PIN                   0
#define SPI_CONTROL_REG          SPCR
#define SPI_STATUS_REG           SPSR
#define SPI_DATA_REG             SPDR
#define CHIP_SELECT_DIRECTION_REG   DDRB
#define CHIP_SELECT_PORT_REG        PORTB
#define CHIP_SELECT_PIN             0





#endif  /* RAL.h */
