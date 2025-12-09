#ifndef led_H_
#define led_H_

#include "common_macros.h"
#include "std_types.h"

/* 0=PORTA,1=PORTB,2=PORTC,3=PORTD */


#define led_port  3   /* PORTD */
#define led_pin   7   /* PD7   */

/* Functions Prototypes */
void led_init(void);
void led_on(void);
void led_off(void);

#endif /* led_H_ */