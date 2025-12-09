#ifndef MAC_TYPES_H_
#define MAC_TYPES_H_

#include "common_macros.h"
#include "std_types.h"

#endif /* MAC_TYPES_H_ */

#ifndef GPIO_H_
#define GPIO_H_

/* Function Prototypes */

void gpio_setup_pin_direction(uint8 port_num , uint8 pin_num , uint8 direction);
void gpio_write_pin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 gpio_read_pin(uint8 port_num, uint8 pin_num);
void gpio_setup_port_direction(uint8 port_num, uint8 direction);
void gpio_write_port(uint8 port_num, uint8 value);
uint8 gpio_read_port(uint8 port_num);

#endif /* GPIO_H_ */