#include "i2c_driver.h"

void i2c_init()
{
  // enable clock access to I2C1
  RCC->APB1ENR |= I2C1EN;

  // enable clock access to GPIOB
  RCC->AHB1ENR |= GPIOBEN;

  // set PB6 and PB7 as I2C1 pins
  configPin(GPIOB, PIN6, ALTERNATE);
  configPin(GPIOB, PIN7, ALTERNATE);

  // set PB6 and PB7 as open drain
  configOutputPin(GPIOB, PIN6, MODE_OPENDRAIN);
  configOutputPin(GPIOB, PIN7, MODE_OPENDRAIN);

  // set PB6 and PB7 as fast speed
  setPortSpeed(GPIOB, PIN6, HIGH_SPEED);
  setPortSpeed(GPIOB, PIN7, HIGH_SPEED);

  // set PB6 and PB7 as I2C1 pins
  GPIOB->AFR[0] |= (0b0100 << (PIN6 * 4)); // SCL
  GPIOB->AFR[0] |= (0b0100 << (PIN7 * 4)); // SDA

  // set I2C1 to standard mode
  I2C1->CCR = 0x28;

  I2C1->CR2 = 0x30;   // Configura o clock periférico para 48 MHz
  I2C1->CCR = 0x8028; // Configura para 100 kHz
  I2C1->TRISE = 0x0F; // Configura o tempo de subida

  I2C1->CR1 |= I2C_CR1_PE; // Habilita o I2C
}
