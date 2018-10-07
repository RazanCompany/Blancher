#ifndef _TASKS_H_
#define  _TASKS_H_
#include "System.h"




void Tank_operation_calibrate_wash_init(void);

gSystemError Wash(uint8_t CycleNumber);
gSystemError Tank_Calibrate(void);

#define Tank_empty()		Wash(1)

#endif //_TASKS_H_