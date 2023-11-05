#include <stdint.h>
// port C, A
// pin 13, 12

// Memory map
// BLOCK DIAGRAM

// BUS TO CONNECT THIS PIN IN CLOCK IS AHB1

// RCC config clocks sistem

// to enable AHB1, search in reference manula AHB1EN

#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_OFFSET (0x20000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET (0x0UL)
#define GPIOA_BASE (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define GPIOC_OFFSET (0x0800UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET (0x30UL) // AHB1 eneble register
#define RCC_AHB1EN_R (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

// to get the bin mode, search in reference manula moder
#define MODE_R_OFFSET (0X00UL)

#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define GPIOC_MODE_R (*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))

// search in reference manula ODR
#define OD_R_OFFSET (0X14UL)

#define GPIOC_OD_R (*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET)) // output data register
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET)) // output data register

#define GPIOCEN (1U << 0) // 0b00001
#define GPIOAEN (1U << 2) // 0b00100

#define PIN12 (1U << 12)
#define PIN13 (1U << 13)

#define LED_PIN PIN13

// asm code
#define NOP() asm volatile("nop")

void delay(uint32_t time)
{
  while (time--)
  {
    NOP();
  }
}

int main(void)
{

  RCC_AHB1EN_R |= GPIOCEN;
  RCC_AHB1EN_R |= GPIOAEN;

  GPIOC_MODE_R |= (1U << 26);
  GPIOC_MODE_R &= ~(1U << 27);

  GPIOA_MODE_R |= (1U << 24);
  GPIOA_MODE_R &= ~(1U << 25);

  while (1)
  {

    GPIOC_OD_R &= ~LED_PIN;
    GPIOA_OD_R &= ~PIN12;
    delay(1000000);

    GPIOA_OD_R |= PIN12;
    GPIOC_OD_R |= LED_PIN;
    delay(1000000);
  }
  return 0; //
}