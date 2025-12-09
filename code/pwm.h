#ifndef std_types
#define std_types
#include "std_types.h"
#endif

#ifndef macros
#define macros
#include "common_macros.h" /* To use the macros like SET_BIT */
#endif

#ifndef avr
#define avr
#include "avr/io.h" /* To use the IO Ports Registers */
#endif //avr

#ifndef PWM_H_
#define PWM_H_

/*
*function prototype
*/
void PWM_Timer0_Init(unsigned char set_duty_cycle);

#endif /* PWM_H_ */
