//  I will use B7 as default SDA
//  I will use B6 as default SCL

#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__
#include "core.h"
#include <stdint.h>

void i2c_init();
void i2c_send_byte(uint8_t address, uint8_t data);

uint8_t I2C_read_byte(uint8_t address, uint8_t regAddress);

#endif /* __I2C_DRIVER_H__ */