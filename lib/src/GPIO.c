#include "GPIO.h"

void configPin(GPIO_TYPE *port, int pin, int mode)
{

  if (port == PORTB)
  {
    RCC->AHB1ENR |= GPIOBEN;
  }
  if (port == PORTC)
  {
    RCC->AHB1ENR |= GPIOCEN;
  }

  if (mode == INPUT)
  {
    port->MODER &= ~PIN_TO_BIT(pin * 2);
    port->MODER &= ~PIN_TO_BIT(pin * 2 + 1);
  }
  if (mode == OUTPUT)
  {
    port->MODER |= PIN_TO_BIT(pin * 2);
    port->MODER &= ~PIN_TO_BIT(pin * 2 + 1);
  }
  if (mode == ALTERNATE)
  {
    port->MODER &= ~PIN_TO_BIT(pin * 2);
    port->MODER |= PIN_TO_BIT(pin * 2 + 1);
  }
  if (mode == ANALOG)
  {
    port->MODER |= PIN_TO_BIT(pin * 2);
    port->MODER |= PIN_TO_BIT(pin * 2 + 1);
  }
}

void setPin(GPIO_TYPE *port, int pin, int value)
{
  if (value == HIGH) port->ODR |= PIN_TO_BIT(pin);
 
  else port->ODR &= ~PIN_TO_BIT(pin);
}