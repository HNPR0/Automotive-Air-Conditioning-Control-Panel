#include "lm35.h"
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
void lm35_init(void)
{
	adc_init();
}

uint8 lm35_get_temperature(void)
{
	uint8 temp_value = 0;
	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = adc_read_channel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*5)/(1023*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}


