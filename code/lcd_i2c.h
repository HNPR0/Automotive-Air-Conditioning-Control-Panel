#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"


/* 
definitions 
*/
#define LCD_I2C_ADDR  0x27
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01


/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/* Functions Prototypes */
void LCD_init(void);
void LCD_send_command(uint8 command);
void LCD_display_character(uint8 data);
void LCD_display_string(const char *Str);
void LCD_move_cursor(uint8 row,uint8 col);
void LCD_display_string_row_column(uint8 row,uint8 col,const char *Str);
void LCD_intger_to_string(int data);
void LCD_intger_to_string_row_column(uint8 row,uint8 col,int data);
void LCD_clear_screen(void);

#endif /* LCD_H_ */




PS C:\Users\Arwa> git init
Initialized empty Git repository in C:/Users/Arwa/.git/
PS C:\Users\Arwa> git remote add origin https://github.com/HNPR0/Automotive-Air-Conditioning-Control-Panel.git
PS C:\Users\Arwa> git remote -v
origin  https://github.com/HNPR0/Automotive-Air-Conditioning-Control-Panel.git (fetch)
origin  https://github.com/HNPR0/Automotive-Air-Conditioning-Control-Panel.git (push)
PS C:\Users\Arwa>
