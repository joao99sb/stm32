// in this moment, the only i2c register in use is I2C1

//  I will use B7 as default SDA
//  I will use B6 as default SCL

#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__
#include "core.h"
#include "GPIO.h"
#include <stdint.h>

#define I2C_CR1_PE ((uint16_t)0x0001)    // Peripheral Enable
#define I2C_CR1_START ((uint16_t)0x0100) // Start bit
#define I2C_SR1_SB ((uint16_t)0x0001)
#define I2C_CR1_STOP ((uint16_t)0x0200)
#define I2C_SR1_TXE ((uint16_t)0x0080)
#define I2C_SR1_ADDR ((uint16_t)0x0002)
typedef struct
{
  volatile uint16_t CR1; // CONTROL REGISTER 1
  volatile uint16_t reserved1;
  volatile uint16_t CR2; // CONTROL REGISTER 2
  volatile uint16_t reserved2;
  volatile uint16_t OAR1; // OWN ADDRESS REGISTER 1
  volatile uint16_t reserved3;
  volatile uint16_t OAR2; // OWN ADDRESS REGISTER 2
  volatile uint16_t reserved4;
  volatile uint16_t DR; // DATA REGISTER
  volatile uint16_t reserved5;
  volatile uint16_t SR1; // STATUS REGISTER 1
  volatile uint16_t reserved6;
  volatile uint16_t SR2; // STATUS REGISTER 2
  volatile uint16_t reserved7;
  volatile uint16_t CCR; // CLOCK CONTROL REGISTER
  volatile uint16_t reserved8;
  volatile uint16_t TRISE; // TRISE REGISTER
  volatile uint16_t reserved9;
  volatile uint16_t FLTR; // FLTR REGISTER
} I2C_TYPE;

#define I2C1 ((I2C_TYPE *)I2C1_BASE)

void i2c_init();
void i2c_send_byte(uint8_t address, uint8_t data);

uint8_t I2C_read_byte(uint8_t address, uint8_t regAddress);

#endif /* __I2C_DRIVER_H__ */