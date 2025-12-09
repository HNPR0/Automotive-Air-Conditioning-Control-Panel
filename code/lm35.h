#ifndef LM35_H_
#define LM35_H_

#include "std_types.h"

#define SENSOR_CHANNEL_ID         1      /* A1 / ADC1 */
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/* Functions Prototypes */
uint8 lm35_get_temperature(void);
void lm35_init(void);

#endif /* LM35_SENSOR_H_ */