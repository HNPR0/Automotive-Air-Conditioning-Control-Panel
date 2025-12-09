#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd_i2c.h"
#include "gpio.h"
#include "i2c.h"


static void LCD_send_two_4bit_chunks(uint8 nibble)
{
    uint8 data;

    /* Backlight always ON */
    data = nibble | LCD_BACKLIGHT;

    /* Send data */
    i2c_start();
    i2c_write_byte((LCD_I2C_ADDR << 1) | 0);   // Write mode
    i2c_write_byte(data);

    /* Enable HIGH */
    i2c_write_byte(data | LCD_ENABLE);

    /* Enable LOW */
    i2c_write_byte(data & ~LCD_ENABLE);

    i2c_stop();
}

static void LCD_send_byte(uint8 value, uint8 mode)
{
    uint8 high = (value & 0xF0) | mode;
    uint8 low  = ((value << 4) & 0xF0) | mode;

    LCD_send_two_4bit_chunks(high);
    LCD_send_two_4bit_chunks(low);
}

void LCD_init(void)
{
	
    _delay_ms(50);  // LCD power-up delay

    /* Initialize to 4-bit mode */
    LCD_send_two_4bit_chunks(0x30);
    _delay_ms(5);
    LCD_send_two_4bit_chunks(0x30);
    _delay_ms(1);
    LCD_send_two_4bit_chunks(0x30);
    LCD_send_two_4bit_chunks(0x20);  // Go to 4-bit mode

    /* Function set: 4 bit, 2 lines, 5x8 font */
    LCD_send_command(0x28);

    /* Display ON, Cursor OFF */
    LCD_send_command(0x0C);

    /* Clear display */
    LCD_send_command(0x01);
    _delay_ms(2);

    /* Entry mode: Move cursor right */
    LCD_send_command(0x06);
}

void LCD_send_command(uint8 command)
{
    LCD_send_byte(command, 0x00);  // RS = 0 (command)
    _delay_ms(2);
}

void LCD_display_character(uint8 data)
{
    LCD_send_byte(data, LCD_RS);  // RS = 1 (data)
}

void LCD_display_string(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_display_character(Str[i]);
		i++;
	}
	
}

void LCD_move_cursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_send_command(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}



void LCD_display_string_row_column(uint8 row,uint8 col,const char *Str)
{
	LCD_move_cursor(row,col); /* go to to the required LCD position */
	LCD_display_string(Str); /* display the string */
}


void LCD_intger_to_string(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_display_string(buff); /* Display the string */
}

void LCD_intger_to_string_row_column(uint8 row,uint8 col,int data){
    LCD_move_cursor(row,col); /* go to to the required LCD position */
    LCD_intger_to_string(data); /* display the data */
}
void LCD_clear_screen(void)
{
	LCD_send_command(LCD_CLEAR_COMMAND); /* Send clear display command */
}