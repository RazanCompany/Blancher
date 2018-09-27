/*
 * this file contain some macros to deal with
 * bits and registers .
 * author : Mahmoud El-gendy
 * data : 14/8/2018
 */

#ifndef hardware_types_h_
#define hardware_types_h_
#include <stdint.h>
//_________________ to set a specific bit________________//
#define SET_BIT(reg , index)   ((reg) |= (1<<(index)))

//________________to clear a specific bit _______________//
#define CLR_BIT(reg , index)   ((reg) &= ~(1<<(index)))

//_______________to toggle a specific bit________________//
#define TOG_BIT(reg , index)   ((reg) ^= (1<<(index)))

//______________to get the value of a specific bit_______//
#define GET_BIT(reg , index)   (((reg) >> (index)) & 0x01)

//______________to set the high four bites ______________//
#define SET_HIGH_NIBBLE(reg)   ((reg) |= 0xf0)

//______________to set the low four bites _______________//
#define SET_LOW_NIBBLE(reg)   ((reg) |= 0x0f)

//______________to clear the high four bites_____________//
#define CLR_HIGH_NIBBLE(reg)   ((reg) &= 0x0f)

//______________to clear the low four bites______________//
#define CLR_LOW_NIBBLE(reg)   ((reg) &= 0xf0)

//______________to put a value in the high nibble________//
#define PUT_VAL_HIGH_NIBBLE(reg , val)   (reg=(((reg) &= 0x0f ) | ((val) << 4)))

//______________to put a value in the low nibble_________//
#define PUT_VAL_LOW_NIBBLE(reg , val)   (reg=(((reg) &= 0xf0 ) | ((val) & 0x0f)))

//______________to get the high four bites_______________//
#define GET_HIGH_NIBBLE(reg)   ((reg) >> 4)

//______________to get the low four bites________________//
#define GET_LOW_NIBBLE(reg)   ((reg) &= 0x0f)

//______________set the register_________________________//
#define SET_REG(reg)          ((reg) |= 0xff)

//______________clear the register_______________________//
#define CLR_REG(reg)          ((reg) &= 0x00)

//_____________write 8 bit register _____________________//
#define PUT_VAL_reg(reg,val) ((reg) = (val) )

// ____________read  8 register
#define GET_REG(reg) (reg)


//____________ GET 8 BIT REGISTER MASKED ________________//
#define HW_WRITE_REG8_MASKED(reg , value , mask) \
                          PUT_VAL_reg(reg,(GET_REG(reg) & ~(mask))|((value) & (mask)))
// get high byte of 16 bit word
#define GET_HIGH_BYTE(val)  ((val) >> 8)

// get low byte of 16 bit word
#define GET_LOW_BYTE(val)    ((val) & 0x00ff)

// make 16 bit word out of two bytes .
#define MAKE_WORD(high,low)   (((high) << 8  ) | (low) )

// get first 16 bit from 32 bit word
#define GET_HIGH_WORD(val)   ((uint16_t )((val) >> 16))

#define GET_LOW_WORD(val)    ((uint16_t)((val) & 0xffff))


#endif /* hardware_types.h */
