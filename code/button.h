#ifndef button_H_
#define button_H_

#include "common_macros.h"
#include "std_types.h"

/* 0=PORTA,1=PORTB,2=PORTC,3=PORTD */
#define PORTNUM  1   /* PORTB */
#define PINNUM   0   /* PB0 (D8) */

/* Function prototypes */
void button_init(void);
uint8 button_status(void);   /* returns 1 if pressed, 0 if not */

#endif /* button_H_ */