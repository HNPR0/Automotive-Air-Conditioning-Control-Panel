#include "rtc.h"

/* Convert decimal to BCD */
uint8 dec_to_bcd(uint8 val)
{
    return ((val / 10) << 4) | (val % 10);
}

/* Convert BCD to decimal */
uint8 bcd_to_dec(uint8 val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

/* Set RTC time (24-hour mode enforced) */
void rtc_set_time(rtc_time *time)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x01);  // start at MINUTES register

    i2c_write_byte(dec_to_bcd(time->minutes));
    i2c_write_byte(dec_to_bcd(time->hours) & 0x3F); // enforce 24h

    i2c_stop();
}

/* Get RTC time */
void rtc_get_time(rtc_time *time)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x01);   // start at MINUTES register

    i2c_start();
    i2c_write_byte(RTC_ADDRESS_READ);

    time->minutes = bcd_to_dec(i2c_read_byte_with_ack());
    time->hours   = bcd_to_dec(i2c_read_byte_with_nack()) & 0x3F;

    i2c_stop();
}


/* Set RTC date */
void rtc_set_date(rtc_date *date)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x03);  // day-of-week register

    i2c_write_byte(date->day);                         // 1–7
    i2c_write_byte(dec_to_bcd(date->date));
    i2c_write_byte(dec_to_bcd(date->month));
    i2c_write_byte(dec_to_bcd(date->year % 100));

    i2c_stop();
}

/* Get RTC date */
void rtc_get_date(rtc_date *date)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x03);

    i2c_start();
    i2c_write_byte(RTC_ADDRESS_READ);

    date->day   = i2c_read_byte_with_ack();               // 1–7
    date->date  = bcd_to_dec(i2c_read_byte_with_ack());
    date->month = bcd_to_dec(i2c_read_byte_with_ack());
    date->year  = 2000 + bcd_to_dec(i2c_read_byte_with_nack());

    i2c_stop();
}

/* Enable 1Hz square wave output */
void rtc_enable_1hz_square_wave(void)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x0E);   // control register
    i2c_write_byte(0x40);   // enable 1Hz
    i2c_stop();
}

/* Disable square wave output */
void rtc_disable_square_wave(void)
{
    i2c_start();
    i2c_write_byte(RTC_ADDRESS_WRITE);
    i2c_write_byte(0x0E);   // control register
    i2c_write_byte(0x00);   // disable
    i2c_stop();
}
