#include "eeprom.h"

/* Write a single byte to internal EEPROM */
void eeprom_write_byte(uint16 addr, uint8 data)
{
    /* Wait for any previous write to complete */
    while (EECR & (1 << EEPE));

    /* Set target EEPROM address */
    EEAR = addr;

    /* Load data into EEPROM data register */
    EEDR = data;

    /* Enable EEPROM write */
    EECR |= (1 << EEMPE);

    /* Start the EEPROM write operation */
    EECR |= (1 << EEPE);
}

/* Read a single byte from internal EEPROM */
void eeprom_read_byte(uint16 addr, uint8 *data)
{
    /* Wait for any previous write to complete */
    while (EECR & (1 << EEPE));

    /* Set target EEPROM address */
    EEAR = addr;

    /* Trigger EEPROM read */
    EECR |= (1 << EERE);

    /* Output the read data */
    *data = EEDR;
}
