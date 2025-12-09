#include "gpio.h"
#include <avr/io.h>

/*
 * Description :
 * Setup the direction of the required pin .
 */
void gpio_setup_pin_direction(uint8 port_num , uint8 pin_num , uint8 direction)
{
	switch(port_num) 
	{
	case 1:
		if(direction == 1)
		{
			SET_BIT(DDRB,pin_num); /*set pin as output*/
		}
		else
		{
			CLEAR_BIT(DDRB,pin_num); /*set pin as input*/
		}
		break;
	case 2:
		if(direction == 1)
		{
			SET_BIT(DDRC,pin_num); /*set pin as output*/
		}
		else
		{
			CLEAR_BIT(DDRC,pin_num); /*set pin as input*/
		}
		break;
	case 3:
		if(direction == 1)
		{
			SET_BIT(DDRD,pin_num); /*set pin as output*/
		}
		else
		{
			CLEAR_BIT(DDRD,pin_num); /*set pin as input*/
		}
		break;
	}
}

 /*
 * Description :
 * Write the value on the required pin.
 */
void gpio_write_pin(uint8 port_num, uint8 pin_num, uint8 value)
{
   	if(value == 1) /* Check if pin value is high */
    {
    	switch(port_num) /* Check port selected */
    	{
		/* Set the pin high */
    	case 1:
    		SET_BIT(PORTB,pin_num); 
    		break;
    	case 2:
    		SET_BIT(PORTC,pin_num);
    		break;
    	case 3:
    		SET_BIT(PORTD,pin_num);
    		break;
    	}
    }
    else /* Pin value is low */
    {
    	switch(port_num) /* Check port selected */
    	{
    	case 1:
    		CLEAR_BIT(PORTB,pin_num);
    		break;
    	case 2:
    		CLEAR_BIT(PORTC,pin_num);
    		break;
    	case 3:
    		CLEAR_BIT(PORTD,pin_num);
    		break;
    	}
    }
}

/*
 * Description :
 * Read and return the value of the required pin.
 */
uint8 gpio_read_pin(uint8 port_num, uint8 pin_num)
{
    uint8 pin_value = 0;
	switch(port_num) /* Check port selected */
	{
	    case 1:
	    	if(BIT_IS_SET(PINB,pin_num)) /* Check if pin is high */
	    	{
	    		pin_value = 1;
	    	}
	    	else /* Pin is low */
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	    case 2:
	    	if(BIT_IS_SET(PINC,pin_num)) /* Check if pin is high */
	    	{
	    		pin_value = 1;
	    	}
	    	else /* Pin is low */
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	    case 3:
	    	if(BIT_IS_SET(PIND,pin_num)) /* Check if pin is high */
	    	{
	    		pin_value = 1;
	    	}
	    	else /* Pin is low */
	    	{
	    		pin_value = 0;
	    	}
	    	break;
	}
    return pin_value; /* Return pin value */
}
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 */
void gpio_setup_port_direction(uint8 port_num, uint8 direction)
{
	switch(port_num) /* Check port selected */
	{
	case 1:
		DDRB = direction; /* Set port B direction */
		break;
	case 2:
		DDRC = direction; /* Set port C direction */
		break;
	case 3:
		DDRD = direction; /* Set port D direction */
		break;
	}
}


 /*
 * Description :
 * Write the value on the required port.
 */
void gpio_write_port(uint8 port_num, uint8 value)
{
	switch(port_num) /* Check port selected */
	{
	case 1:
		PORTB = value; /* Write value to port B */
		break;
	case 2:
		PORTC = value; /* Write value to port C */
		break;
	case 3:
		PORTD = value; /* Write value to port D */
		break;
	}
}


 /*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 gpio_read_port(uint8 port_num)
{
	uint8 value = 0;
	switch(port_num) /* Check port selected */
	{
	case 1:
		value = PINB; /* Read value from port B */
		break;
	case 2:
		value = PINC; /* Read value from port C */
		break;
	case 3:
		value = PIND; /* Read value from port D */
		break;
	}
	return value; /* Return port value */
}