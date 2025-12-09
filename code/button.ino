#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>
#include "button.h"

/*
 * Description :
 * Button Initialization.
 */
void button_init(void)
{
  gpio_setup_pin_direction(PORTNUM, PINNUM, PIN_INPUT);
}

/*
 * Description :
 * Read and return the value of the Button.
 */

 
uint8_t button_status(void)
{
  static uint8_t last_state = 0;
  uint8_t current_state =  gpio_read_pin(PORTNUM, PINNUM);

  if (current_state != last_state)
  {
    _delay_ms(15);
    current_state =  gpio_read_pin(PORTNUM, PINNUM); 
  }
  last_state = current_state;
  return current_state;
}
