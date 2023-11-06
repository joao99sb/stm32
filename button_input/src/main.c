#include <stdint.h>

// output
// port C, A
// pin 13, 12

// input
// port A
// pin 7

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
// output data register
#define OD_R_OFFSET (0X14UL)

#define GPIOC_OD_R (*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET))
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

// input data register
#define ID_R_OFFSET (0X10UL)

#define GPIOA_ID_R (*(volatile unsigned int *)(GPIOA_BASE + ID_R_OFFSET))

#define GPIOCEN (1U << 0) // 0b00001
#define GPIOAEN (1U << 2) // 0b00100

#define PIN7 (1U << 7)
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

void config_outpu(void)
{

  GPIOC_MODE_R |= (1U << 26);
  GPIOC_MODE_R &= ~(1U << 27);

  GPIOA_MODE_R |= (1U << 24);
  GPIOA_MODE_R &= ~(1U << 25);

  GPIOC_OD_R |= LED_PIN;
}
void config_input(void)
{
  GPIOA_MODE_R &= ~(1U << 14);
  GPIOA_MODE_R &= ~(1U << 15);
}
void config(void)
{
  // enable clock in GPIO
  RCC_AHB1EN_R |= GPIOCEN;
  RCC_AHB1EN_R |= GPIOAEN;

  config_outpu();
  config_input();
}

void blink(void)
{
  GPIOC_OD_R &= ~LED_PIN;
  GPIOA_OD_R &= ~PIN12; // led turn off when bit is high

  delay(1000000);

  GPIOA_OD_R |= PIN12; // led turn on when bit is high
  GPIOC_OD_R |= LED_PIN;
  delay(1000000);
}

int main(void)
{
  config();

  while (1)
  {

    uint32_t has_input_A7 = GPIOA_ID_R & PIN7;
    if (has_input_A7)
    {
      blink();
    }
    else
    {
      GPIOA_OD_R &= ~PIN12;
    }
  }
  return 0; //
}