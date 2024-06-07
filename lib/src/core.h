#ifndef __CORE_H__
#define __CORE_H__
#include <stdint.h>

#define PERIPH_BASE (0x40000000UL)

// BUS
#define AHB1PERIPH_OFFSET (0x20000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define APB1PERIPH_OFFSET (0x0000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + APB1PERIPH_OFFSET)

// BUS AHB1
#define GPIOC_OFFSET (0x0800UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + GPIOC_OFFSET)

#define GPIOB_OFFSET (0x0400UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

// BUSS APB1
#define I2C1_OFFSET (0x5400UL)
#define I2C1_BASE (APB1PERIPH_BASE + I2C1_OFFSET)

#define GPIOBEN (1U << 1) // 0b00010
#define GPIOCEN (1U << 2) // 0b00100
#define I2C1EN (1U << 21)


// BUS AHB1 STRUCT

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
  volatile uint32_t ARF[2];  // ALTERNATE FUNCTION REGISTER        addr offset: 0x20-0X24

} GPIO_TYPE;

typedef struct
{
  volatile uint32_t DUMMY[12];
  volatile uint32_t AHB1ENR; // RCC AHB1 PERIPHERAL CLOCK REGISTER
  volatile uint32_t DUMMY2[3];
  volatile uint32_t APB1ENR; // RCC APB1 PERIPHERAL CLOCK ENABLE REGISTER

} RCC_TYPE;

#define GPIOC ((GPIO_TYPE *)GPIOC_BASE)
#define GPIOB ((GPIO_TYPE *)GPIOB_BASE)

#define RCC ((RCC_TYPE *)RCC_BASE)

// BUS APB1 STRUCT

typedef struct
{
  volatile uint32_t CR1;   // CONTROL REGISTER 1
  volatile uint32_t CR2;   // CONTROL REGISTER 2
  volatile uint32_t OAR1;  // OWN ADDRESS REGISTER 1
  volatile uint32_t OAR2;  // OWN ADDRESS REGISTER 2
  volatile uint32_t DR;    // DATA REGISTER
  volatile uint32_t SR1;   // STATUS REGISTER 1
  volatile uint32_t SR2;   // STATUS REGISTER 2
  volatile uint32_t CCR;   // CLOCK CONTROL REGISTER
  volatile uint32_t TRISE; // TRISE REGISTER
  volatile uint32_t FLTR;  // FLTR REGISTER
} I2C_TYPE;

// asm code
#define NOP() asm volatile("nop")

void delay(int time);

#endif /* __CORE_H__ */