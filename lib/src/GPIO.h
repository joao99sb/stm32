#ifndef __GPIO_H__
#define __GPIO_H__

#include "core.h"

#define PORTB GPIOB
#define PORTC GPIOC

#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

#define MODE_PUSHPULL 0
#define MODE_OPENDRAIN 1

#define LOW_SPEED 0
#define MEDIUM_SPEED 1
#define FAST_SPEED 2
#define HIGH_SPEED 3

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
  volatile uint32_t MODER;   // MODE REGISTER                      addr offset: 0x00
  volatile uint32_t OTYPER;  // PORT OUTPUT TYPE REGISTER          addr offset: 0x04
  volatile uint32_t OSPEEDR; // PORT OUTPUT SPEED REGISTER         addr offset: 0x08
  volatile uint32_t PUPDR;   // PORT PULL-UP//PULL-DOW             addr offset: 0x0C
  volatile uint32_t IDR;     // PORT INPUT DATA REGISTER           addr offset: 0x10
  volatile uint32_t ODR;     // PORT OUTPUT DATA REGISTER          addr offset: 0x14
  volatile uint32_t ESRR;    // PORT BIT SET/RESET REGISTER        addr offset: 0x18
  volatile uint32_t LCKR;    // PORT CONFIGURATION LOCK REGISTER   addr offset: 0x1C
  volatile uint32_t AFR[2];  // ALTERNATE FUNCTION REGISTER        addr offset: 0x20-0X24

} GPIO_TYPE;
#define GPIOC ((GPIO_TYPE *)GPIOC_BASE)
#define GPIOB ((GPIO_TYPE *)GPIOB_BASE)
typedef struct
{
  GPIO_TYPE *port;
  int pin;
  int mode;

} GPIO_CONFIG;

void configPin(GPIO_TYPE *port, int pin, int mode);
void configOutputPin(GPIO_TYPE *port, int pin, int mode);
void setPin(GPIO_TYPE *port, int pin, int value);
void setPortSpeed(GPIO_TYPE *port, int pin, int speed);

#endif // __GPIO_H__