#include "gpio.h"
#include <avr/io.h>
#include "led.h"


/*
 * Description :
 * LED Initialization.
 */
void led_init(void)
 {
   gpio_setup_pin_direction(led_port, led_pin, PIN_OUTPUT);         /* Set the LED pin as output */
   led_off();                                 /* Turn OFF the LED at the beginning */
 }

/*
 * Description :
 * Function responsible for turning on the LED by putting 1 on the pin  .
 */
void led_on(void)
 {
    gpio_write_pin(led_port, led_pin, LOGIC_HIGH);
 }

/*
 * Description :
 * Function responsible for turning off the LED by putting 0 on the pin  .
 */
void led_off(void)
 {
     gpio_write_pin(led_port, led_pin, LOGIC_LOW);
 }