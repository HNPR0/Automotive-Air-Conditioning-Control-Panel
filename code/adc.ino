#include "adc.h"
#include <avr/io.h>

void adc_init(void)
{
    /* AVCC as reference, ADC0 by default */
    ADMUX = (1 << REFS0);

    /* Enable ADC, prescaler = 128 (for 16MHz -> 125kHz ADC clock) */
    ADCSRA = (1 << ADEN)  |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
}

uint16_t adc_read_channel(uint8_t Ch_Num)
{
    /* Select ADC channel (0–7) */
    ADMUX &= 0xF8;                 /* Clear MUX2:0 */
    ADMUX |= (Ch_Num & 0x07);      /* Set channel    */

    /* Start conversion */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion to finish */
    while (!(ADCSRA & (1 << ADIF)))
    {
        /* busy-wait */
    }

    /* Clear ADIF by writing 1 */
    ADCSRA |= (1 << ADIF);

    /* Return 10-bit ADC result */
    return ADC;
}