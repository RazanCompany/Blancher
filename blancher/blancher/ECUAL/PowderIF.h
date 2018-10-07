/*
 * Pouder.h
 *
 *  Created on: Aug 25, 2018
 *      Author: M.nagah
 */

#ifndef POWDER_H_
#define POWDER_H_


/*
 * init the powder gm for each ticks
 * and the timer for powder encoder
 * @parameters gram of the salt of each tick and timer number
 * @return Nothing
 */
void Powder_init(float Gram_for_one_ticks ,int Timer_number );
/*
 * using to Drop salt into the tank u
 * polling Function using Interrupt to Exit polling
 * @parameter the amount of salt by Gram
 * @Return Nothing
 */
void Powder_drop(float Gram);

// /*
//  * ISR call Back function
//  * @parameter different time between each ticks
//  */
// void Powder_ISR(); //not used


#endif /* POUDER_H_ */
