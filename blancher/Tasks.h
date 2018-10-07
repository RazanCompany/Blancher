#ifndef _TASKS_H_
#define  _TASKS_H_
#include "System.h"


void Tank_operation_calibrate_wash_init(void);

gSystemError Wash(uint8_t CycleNumber);
gSystemError Tank_Calibrate(void);


#endif //_TASKS_H_