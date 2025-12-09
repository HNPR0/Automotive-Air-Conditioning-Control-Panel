#ifndef INTERNAL_EEPROM_H
#define INTERNAL_EEPROM_H

#include <avr/io.h>
#include <stdint.h>
#include "std_types.h"

/* Function Prototypes */
void eeprom_write_byte(uint16 addr, uint8 data);
void eeprom_read_byte(uint16 addr, uint8 *data);

#endif
