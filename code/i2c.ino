#include "i2c.h"
#include "common_macros.h"
#include <avr/io.h>

/* Initialise I2C using macros */
void i2c_init(void)
{
    /* Set prescaler */
    TWSR &= ~((1<<TWPS0)|(1<<TWPS1));
    TWSR |= (I2C_PRESCALER & 0x03);

    /* Set bit rate */
    TWBR = I2C_BIT_RATE;

    /* Load slave address (7-bit) and disable general call */
    TWAR = (I2C_ADDRESS & 0xFE);

    /* Enable TWI */
    TWCR = (1<<TWEN);
}


/* Send START condition on I2C bus */
void i2c_start(void)
{
    /* Clear interrupt flag, send START */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for START to complete       */
    while (BIT_IS_CLEAR(TWCR, TWINT));
}

/* Send STOP condition on I2C bus */
void i2c_stop(void)
{
    /* Clear flag, issue STOP */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/* Send a single data byte over I2C */
void i2c_write_byte(uint8 data)
{
    /* Load data into register */
    TWDR = data;                                        
    
    /* Start transmission */
    TWCR = (1 << TWINT) | (1 << TWEN);                  
    
    /* Wait until transmission completes */
    while (BIT_IS_CLEAR(TWCR, TWINT));                
}

/* Read one byte and send ACK (request more bytes) */
uint8 i2c_read_byte_with_ack(void)
{
    /* Enable ACK */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);    
    
    /* Wait for reception */ 
    while (BIT_IS_CLEAR(TWCR, TWINT));                  
    
    /* Return received byte */ 
    return TWDR;                                        
}

/* Read one byte and send NACK (final byte) */
uint8 i2c_read_byte_with_nack(void)
{
    /* NACK: TWEA=0          */
    TWCR = (1 << TWINT) | (1 << TWEN);                  
    /* Wait for reception    */
    while (BIT_IS_CLEAR(TWCR, TWINT));                  
    /* Return received byte  */
    return TWDR;                                        
}

/* Get current I2C status */
uint8 i2c_get_status(void)
{
    /* Mask status bits */
    return (TWSR & 0xF8);
}