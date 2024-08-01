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

void configOutputPin(GPIO_TYPE *port, int pin, int mode)
{
  if (mode == MODE_OPENDRAIN)
  {
    port->OTYPER |= PIN_TO_BIT(pin);
  }
  else
  {
    port->OTYPER &= ~PIN_TO_BIT(pin);
  }
}

void setPin(GPIO_TYPE *port, int pin, int value)
{
  if (value == HIGH)
  {
    port->ODR |= PIN_TO_BIT(pin);
  }
  else
  {
    port->ODR &= ~PIN_TO_BIT(pin);
  }
}

void setPortSpeed(GPIO_TYPE *port, int pin, int speed)
{
  if (speed == LOW_SPEED)
  {
    port->OSPEEDR &= ~PIN_TO_BIT(pin * 2);
    port->OSPEEDR &= ~PIN_TO_BIT(pin * 2 + 1);
  }
  if (speed == MEDIUM_SPEED)
  {
    port->OSPEEDR |= PIN_TO_BIT(pin * 2);
    port->OSPEEDR &= ~PIN_TO_BIT(pin * 2 + 1);
  }
  if (speed == FAST_SPEED)
  {
    port->OSPEEDR &= ~PIN_TO_BIT(pin * 2);
    port->OSPEEDR |= PIN_TO_BIT(pin * 2 + 1);
  }
  if (speed == HIGH_SPEED)
  {
    port->OSPEEDR |= PIN_TO_BIT(pin * 2);
    port->OSPEEDR |= PIN_TO_BIT(pin * 2 + 1);
  }
}
