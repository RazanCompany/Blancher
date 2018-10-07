/*
 * RTE_Tankslevels.h
 *
 * Created: 9/20/2018 3:10:36 AM
 *  Author: Mohab Adel
 */ 


#ifndef RTE_TANKSLEVELS_H_
#define RTE_TANKSLEVELS_H_

void RTE_levels_init(void);

void RTE_set_tank_level(uint16_t u16tank_level);
uint16_t RTE_get_tank_level(void);

void RTE_set_blancher_level(uint16_t u16blancher_level);
uint16_t RTE_get_blancher_level(void);



#endif /* RTE_TANKSLEVELS_H_ */