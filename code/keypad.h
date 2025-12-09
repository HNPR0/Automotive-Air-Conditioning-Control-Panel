#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>

void keypad_init(void);
char keypad_getKey(void);  // non-blocking

#endif
