#ifndef RTC_H_
#define RTC_H_

#include "i2c.h"
#include "std_types.h"

/* RTC I2C addresses */
#define RTC_ADDRESS_WRITE 0xD0
#define RTC_ADDRESS_READ  0xD1

/* BCD helpers */
uint8 dec_to_bcd(uint8 val);
uint8 bcd_to_dec(uint8 val);

/* Time structure */
typedef struct {
    uint8 minutes;
    uint8 hours;
} rtc_time;

/* Date structure */
typedef struct {
    uint8 day;
    uint8 date;
    uint8 month;
    uint16 year;
} rtc_date;

/* RTC functions */
void rtc_set_time(rtc_time *time);
void rtc_get_time(rtc_time *time);

void rtc_set_date(rtc_date *date);
void rtc_get_date(rtc_date *date);

/* Square wave output */
void rtc_enable_1hz_square_wave(void);
void rtc_disable_square_wave(void);

#endif /* RTC_H_ */