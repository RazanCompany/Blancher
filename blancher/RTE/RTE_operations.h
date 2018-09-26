/*
 * RTE_operations.h
 *
 * Created: 9/20/2018 3:12:56 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_OPERATIONS_H_
#define RTE_OPERATIONS_H_

void RTE_operations_init(void);
void RTE_set_System_on(uint16_t u16System_on);
uint16_t RTE_get_System_on(void);
void RTE_set_Start_blancher_Operation(uint16_t u16Start_blancher_Operation);
uint16_t RTE_get_Start_blancher_Operation(void);
void RTE_set_Wash_Operation(uint16_t u16Wash_Operation);
uint16_t RTE_get_Wash_Operation(void);
void RTE_set_Tank_Calibration_Operation(uint16_t u16Tank_Calibration_Operation);
uint16_t RTE_get_Tank_Calibration_Operation(void);

  
  
  
   


#endif /* RTE_OPERATIONS_H_ */