
#include <avr/io.h>
#include "uart.h"

void uart_set_baudrate(unsigned short baud_rate)
{
    unsigned short UBBR = (F_CPU / (8UL * baud_rate)) - 1;
    UBRR0L = (UBBR & 0xFF);
    UBRR0H = (( UBBR >> 8 ) & 0xFF);
    
    return;
}

void uart_init(void)
{
    /* Enable double-speed mode */
    UCSR0A |= (1 << U2X0);
    
    /* Set baud rate */
    uart_set_baudrate(9600);
    
    /* Enable USART transmitter/receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    /* 8 data bits, 1 stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	return;
}


void uart_send_char(unsigned char data_byte)
{
    // Wait until Write buffer is empty
    while ( ! (UCSR0A & ( 1 << UDRE0)) );
    UDR0 = data_byte;
	return;
}

unsigned char uart_read_data(void)
{
    // Wait until data is received
    while ( ! (UCSR0A & ( 1 << RXC0)) );
    return UDR0;
}

void uart_send_string(char DataString[])
{
    int i;
    for (i=0; DataString[i]; i++)
    {
        uart_send_char(DataString[i]);
    }
	return;
}

void uart_receive_string(uint8 *Str)
{
    uint8 i = 0U;
    char data;

    /* Wait for the first actual character (skip preceding newlines) */
    do {
        data = uart_read_data();
    } while (data == '\n' || data == '\r');
    
    /* Now, start receiving the command until a newline */
    while ( (data != '\n') && (data != '\r') )
    {
        Str[i] = data;
        i++;

        // Echo back the character so user sees what they typed
        uart_send_char(data);

        data = uart_read_data();
    }
    
    /* Add the null terminator */
    Str[i] = '\0';
    
    // Move to a new line after Enter
    uart_send_string("\r\n");
}



uint8 uart_data_avaiable(void)
{
    if (UCSR0A & (1 << RXC0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}