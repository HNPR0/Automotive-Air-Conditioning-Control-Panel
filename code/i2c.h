#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/* TWI Status Codes */
#define I2C_START               0x08
#define I2C_REP_START           0x10
#define I2C_MT_SLA_W_ACK        0x18
#define I2C_MT_DATA_ACK         0x28
#define I2C_MR_DATA_ACK         0x50
#define I2C_MR_DATA_NACK        0x58

/* ----- I2C Configuration Macros ----- */
#define I2C_BIT_RATE     72       // TWBR value
#define I2C_PRESCALER    0        // TWSR prescaler bits
#define I2C_ADDRESS      0x00     // Master address (if used as slave)

/* Function Prototypes */
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write_byte(uint8 data);
uint8 i2c_read_byte_with_ack(void);
uint8 i2c_read_byte_with_nack(void);
uint8 i2c_get_status(void);

#endif /* I2C_H_ */
