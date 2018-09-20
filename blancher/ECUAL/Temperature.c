/*
 * temp.c
 * This file is responsible for reading and calibrating temperature reading
 * using ADC file .
 *      Author: Mahmoud elgendy
 */
#include "Temperature.h"
#include "../MCAL/ADC.h"
#include <math.h>


void temp_init(uint8_t channal)
{
	// initialize the ADC module in order to be able
	// to get reading from the sensor.
	ADC_init(channal);
}

uint16_t temp_read ()
{
	// this function returns the temperature sensor reading
	double Temp ,  vout, rt, a = 0.0039083 , r0 =100, y, b = -0.000000577,x ;
	// sum of samples taken
	double sum = 0.0;
	// current sample number
	unsigned char sample_count = 0;

    // read 30 values of ADC and take their average.
	while (sample_count < 30)
	{
	       double x  = ADC_read();
	       sum += x;
	       sample_count++;
	}

    // the average of ADC readings
	 vout = (double)sum / (double)30;

	 vout *= 3.29;
	 vout /= 1024.0;

	 rt = vout * 1000 / 10  ;


	 // some math equations to Get The temperature value from ADC reading.
	 Temp = (-1 * a) ;
	 x =  pow(a,2);
	 y = 4  * b * (1 - (rt/r0));
	 x = x - y;
	 x = pow(x,0.5);
	 Temp = Temp + x ;
	 Temp /= (2 * b);

	 return round(Temp);
}
