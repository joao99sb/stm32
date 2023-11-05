#include <stdint.h>
// port C
// pin 13

// Memory map
// BLOCK DIAGRAM

// BUS TO CONNECT THIS PIN IN CLOCK IS AHB1

// RCC config clocks sistem

// to enable AHB1, search in reference manula AHB1EN

#define NOP() asm volatile("nop")

#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_OFFSET (0x20000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOC_OFFSET (0x0800UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET (0x30UL) // AHB1 eneble register
#define RCC_AHB1EN_R (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

// to get the bin mode, search in reference manula moder

#define MODE_R_OFFSET (0X00UL)
#define GPIOC_MODE_R (*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))

// search in reference manula ODR
#define OD_R_OFFSET (0X14UL)
#define GPIOC_OD_R (*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET)) // output data register

// to enable GPIOC, flip 2 bit to 1

// (1U<<n) => set bit in position n+1 to 1
// ~(1U << n) => set bit in position n+1 to 0

#define GPIOCEN (1U << 2) // 0b00100

#define PIN13 (1U << 13)
#define LED_PIN PIN13

void delay(uint32_t time)
{
  while (time--)
  {
    NOP(); // No Operation - Aguarda um curto período de tempo
  }
}

int main(void)
{

  // enable clock access to GPIOC
  RCC_AHB1EN_R |= GPIOCEN;

  // set P13 as output pin
  GPIOC_MODE_R |= (1U << 26);
  GPIOC_MODE_R &= ~(1U << 27);

  while (1)
  {
    // set P13 high
    GPIOC_OD_R &= ~LED_PIN;
    delay(1000000);
    GPIOC_OD_R |= LED_PIN;
    delay(1000000);
  }
  return 0; //
}