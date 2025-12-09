#include "keypad.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define ROW0 PD0
#define ROW1 PD1
#define ROW2 PD2
#define ROW3 PD3

#define COL0 PD4
#define COL1 PD5
#define COL2 PD6

volatile char last_key = 0;

/* Convert row + col → actual character */
char decode_key(uint8_t row, uint8_t col)
{
    switch(row)
    {
        case 0:
            if(col == 0) return '1';
            if(col == 1) return '2';
            if(col == 2) return '3';
            break;
        case 1:
            if(col == 0) return '4';
            if(col == 1) return '5';
            if(col == 2) return '6';
            break;
        case 2:
            if(col == 0) return '7';
            if(col == 1) return '8';
            if(col == 2) return '9';
            break;
        case 3:
            if(col == 0) return '*';
            if(col == 1) return '0';
            if(col == 2) return '#';
            break;
    }
    return 0;
}

void keypad_init(void)
{
    /* Rows = outputs */
    DDRD |= (1<<ROW0) | (1<<ROW1) | (1<<ROW2) | (1<<ROW3);

    /* Columns = inputs + pullups */
    DDRD &= ~((1<<COL0) | (1<<COL1) | (1<<COL2));
    PORTD |= (1<<COL0) | (1<<COL1) | (1<<COL2);

    /* Enable pin-change interrupts for PD4–PD6 */
    PCICR |= (1 << PCIE2);  // Enable PCINT2 group (PORTD)
    PCMSK2 |= (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22);

    sei();
}

/* Scan keypad and return key, or 0 */
char scan_keypad(void)
{
    for(uint8_t row = 0; row < 4; row++)
    {
        /* all rows high */
        PORTD |= (1<<ROW0) | (1<<ROW1) | (1<<ROW2) | (1<<ROW3);

        /* pull one row low */
        PORTD &= ~(1 << (ROW0 + row));

        _delay_us(5);

        /* now check each column */
        if(!(PIND & (1<<COL0))) return decode_key(row, 0);
        if(!(PIND & (1<<COL1))) return decode_key(row, 1);
        if(!(PIND & (1<<COL2))) return decode_key(row, 2);
    }

    return 0;   
}

ISR(PCINT2_vect)
{
    _delay_ms(20); // debounce
    char k = scan_keypad();
    if(k != 0)
	{
        last_key = k;
	}
}

char keypad_getKey(void)
{
    char k = last_key;
    last_key = 0;
    return k;  // return 0 if nothing new
}
