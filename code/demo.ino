#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "std_types.h"
#include "lm35.h"
#include "lcd_i2c.h"
#include "keypad.h"
#include "button.h"
#include "led.h"
#include "motor.h"
#include "rtc.h"
#include "uart.h"
#include "eeprom.h"

/* Global variables */
uint8 editing        = 0;
uint8 RTtemperature  = 0;
uint8 REQtemperature = 25;
uint8 eeprom_req;
uint8 temp_diff;
uint8 speed;
uint8 mode_select;
uint8 button_value;

char C[]    = "C";
char rtt[]  = "CUR:";
char reqt[] = "REQ:";
char ac[]   = "AC:";
char mot_state[4];

rtc_time time = {10, 15};          /* hours, minutes */
rtc_date date = {3, 9, 12, 2025};  /* day, date, month, year */
uint16 start_address = 0x000A;

/* motorState global (declared extern in motor.h) */
DcMotor_State motorState = STOP;

/* ------------------ Helper Functions ------------------ */

void temp_control(void)
{
    char key = keypad_getKey(); // non-blocking

    /* toggle modes when button pressed */
    if (button_status() == 1)
    {
        mode_select ^= 1;
        _delay_ms(20); /* debounce */
        return;
    }

    if (mode_select == 0)
    {
        if (key == '#')      REQtemperature++;
        else if (key == '*') REQtemperature--;
    }
    else if (mode_select == 1)
    {
        static uint8 digits[2];
        static uint8 index = 0;

        if (!editing && key == '*')
        {
            editing = 1;
            index = 0;
            LCD_display_string_row_column(0, 4, "  ");
            return;
        }

        if (editing)
        {
            if (key >= '0' && key <= '9')
            {
                digits[index] = (uint8)(key - '0');
                LCD_intger_to_string_row_column(0, 4 + index, digits[index]);
                index++;
                if (index >= 2) index = 0;
            }

            if (key == '#')
            {
                REQtemperature = (uint8)(digits[0] * 10 + digits[1]);
                editing = 0;
            }
        }
    }
}

void eeprom_store_data(uint16 start_addr, rtc_time time, DcMotor_State motorState, uint8 req_t)
{
    uint16 address = start_addr;
    eeprom_write_byte(address++, time.hours);
    eeprom_write_byte(address++, time.minutes);
    eeprom_write_byte(address++, (uint8)motorState);
    eeprom_write_byte(address++, req_t);
}

void ac_control(void)
{
    temp_diff = (uint8)(RTtemperature - REQtemperature);

    if (temp_diff > 5)
    {
        motorState = CW;
        strcpy(mot_state, "CW ");
        led_on();

        if      (temp_diff > 25) speed = 100;
        else if (temp_diff > 15) speed = 75;
        else                     speed = 50;

        dc_motor_rotate(motorState, speed);
    }
    else if ((int8_t)temp_diff < -5)
    {
        /* temp_diff is uint8, so cast for comparison to negative */
        motorState = A_CW;
        strcpy(mot_state, "ACW");
        led_on();

        if      ((int8_t)temp_diff < -25) speed = 100;
        else if ((int8_t)temp_diff < -15) speed = 75;
        else                              speed = 50;

        dc_motor_rotate(motorState, speed);
    }
    else
    {
        motorState = STOP;
        strcpy(mot_state, "OFF");
        speed = 0;
        dc_motor_rotate(motorState, speed);
        led_off();
    }

    LCD_display_string_row_column(1, 0, ac);
    LCD_display_string_row_column(1, 3, mot_state);
}

void time_update(void)
{
    rtc_get_time(&time);
}

/* ------------------ Arduino setup/loop ------------------ */

void setup(void)
{
    /* Initialize peripherals */
    adc_int();          /* for LM35 */
    LCD_init();
    keypad_init();
    button_init();
    led_init();
    motor_init();
    uart_init();
    i2c_init();
    rtc_set_time(&time);
    rtc_set_date(&date);
    _delay_ms(100);

    /* Store initial EEPROM values */
    eeprom_store_data(start_address, time, motorState, REQtemperature);
}

void loop(void)
{
    /* EEPROM update only if needed */
    eeprom_read_byte(start_address + 3, &eeprom_req);
    if (eeprom_req != REQtemperature)
    {
        eeprom_store_data(start_address, time, motorState, REQtemperature);
    }

    /* Sensor reading */
    RTtemperature = lm35_get_temperature();

    /* Control loops */
    temp_control();
    ac_control();
    time_update();

    /* LCD display */
    LCD_display_string_row_column(0, 0, reqt);
    if (!editing)
        LCD_intger_to_string_row_column(0, 4, REQtemperature);
    LCD_display_string_row_column(0, 6, C);

    LCD_display_string_row_column(0, 8, rtt);
    LCD_intger_to_string_row_column(0, 12, RTtemperature);
    LCD_display_string_row_column(0, 14, C);

    /* display time as HH:MM on row 1, cols 9–12 */
    LCD_intger_to_string_row_column(1, 9,  time.hours);
    LCD_intger_to_string_row_column(1, 12, time.minutes);
}