#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "common_macros.h"
#include "std_types.h"

/* Function Prototypes */
void adc_init(void);
uint16_t adc_read_channel(uint8_t Ch_Num);

#endif /* ADC_H_ */