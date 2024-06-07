#ifndef __GPIO_H__
#define __GPIO_H__

#include "core.h"

#define PORTB GPIOB
#define PORTC GPIOC

#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

#define LOW 0
#define HIGH 1

#define BIT(n) (1U << (n))
#define PIN_TO_BIT(pin) BIT(pin)

#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#define LED_PIN PIN13

#define GPIOBEN (1U << 1) // 0b00010
#define GPIOCEN (1U << 2) // 0b00100

typedef struct
{
  GPIO_TYPE *port;
  int pin;
  int mode;

} GPIO_CONFIG;

void configPin(GPIO_TYPE *port, int pin, int mode);
void setPin(GPIO_TYPE *port, int pin, int value);

#endif // __GPIO_H__