
#ifndef ENCODER_H_
#define ENCODER_H

#include <stdint.h>

void Encoder_init(void (*pISR_callback)(uint32_t),uint8_t timer_number,uint16_t ticks_number );
#endif /* ENCODER_H_ */
