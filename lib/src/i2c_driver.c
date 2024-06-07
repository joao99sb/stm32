#include "i2c_driver.h"

void i2c_init()
{
  // enable clock access to I2C1
  RCC->APB1ENR |= I2C1EN;
  // enable clock access to GPIOB
  // RCC->AHB1ENR |= GPIOBEN;

  // set PB6 and PB7 as I2C1 pins
}