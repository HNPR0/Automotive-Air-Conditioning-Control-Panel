#include "pwm.h"

#include "common_macros.h"

/*
 * Description :
 * Function to initialize the PWM mode of Timer0.
 */
void PWM_Timer0_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0A  = set_duty_cycle; // Set Compare Value

	DDRB  |= (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
   // Fast PWM, non-inverting mode
    TCCR0A = (1<<WGM00) | (1<<WGM01) | (1<<COM0A1);

    // Prescaler 1024
    TCCR0B = (1<<CS02) | (1<<CS00);
}
