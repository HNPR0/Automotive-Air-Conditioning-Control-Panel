#include "std_types.h"


/*function prototypes*/
void uart_init(void);
void uart_set_baudrate(unsigned short baud_rate);
void uart_send_char(unsigned char data_byte);
unsigned char uart_read_data();
uint8 uart_data_avaiable(void);
void uart_send_string(char DataString[]);
