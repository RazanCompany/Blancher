/*
 * Encoder_Task.H
 *
 * Created: 9/20/2018 3:08:33 AM
 *  Author: M.Nagah
 */ 
#ifndef ENCODER_TASK_H_
#define ENCODER_TASK_H_
/*
 * set_up the conveyor and Drum config 
 * parameters@ Nothing
 * return@ Nothing
 */
void Encoder_init();
/*
 * To calculate the RPM oF conveyor 
 * parameters@ Nothing
 * return@ RPM for Conveyor
 */

uint16_t Conveyor_speed();
/*
 * To calculate the RPM oF Drum
 * parameters@ Nothing
 * return@ RPM for Drum
 */
uint16_t Drum_speed();


#endif /* ENCODER_TASK_H_ */