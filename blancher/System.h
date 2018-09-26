/*
 * System.h
 *
 * Created: 9/26/2018 7:00:16 AM
 *  Author: Mohab Adel
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_


typedef enum{
	E_OK=0,
	E_Fail

}gSystemError;

gSystemError System_init(void);

#endif /* SYSTEM_H_ */