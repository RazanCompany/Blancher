/*
 * Ignition.h
 *
 * Created: 10/10/2018 1:33:17 PM
 *  Author: M.nagah
 */ 


#ifndef IGNITION_H_
#define IGNITION_H_
/*
 * start the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
uint8_t Start_ignition(void);
/*
 * stop the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
uint8_t Stop_ignition(void);
/*
 * start the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */

uint8_t start_gas__igintion(void) ;

/*
 * start the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
uint8_t Start_electric_igintion(void); 
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */

uint8_t close_gas__igintion (void);
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
uint8_t close_electric__igintion(void);




#endif /* IGNITION_H_ */