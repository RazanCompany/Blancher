/*
 * Ignition.h
 *
 * Created: 10/10/2018 1:33:17 PM
 *  Author: M.nagah
 */ 


#ifndef IGNITION_OPERATION_H_
#define IGNITION_OPERATION_H_
#include "../GLOBAL.h"
/*
 * start the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
gSystemError Start_ignition(void);
/*
 * stop the ignition process  
 * parameters@ ignition type (GAS - Electric)
 * return@ ok or Error
 */
gSystemError Stop_ignition(void);
/*
 * start the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */

gSystemError start_gas__igintion(void);

/*
 * start the ignition process  For Electric Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
gSystemError Start_electric_igintion(void);
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */

gSystemError close_gas__igintion(void);
 //0x0f
/*
 * stop the ignition process  For GAS Frying
 * parameters@ Nothing
 * return@ ok or Error
 */
gSystemError close_electric__igintion(void);




#endif /* IGNITION_OPERATION_H_ */