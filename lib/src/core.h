#include <stdint.h>


#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_OFFSET (0x20000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOC_OFFSET (0x0800UL)
#define GPIOC_BASE (AHB1PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOCEN (1U << 2) // 0b00100

#define PIN13 (1U << 13)
#define LED_PIN PIN13

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

} RCC_TYPE;

#define GPIOC ((GPIO_TYPE *)GPIOC_BASE)
#define RCC ((RCC_TYPE *)RCC_BASE)

// asm code
#define NOP() asm volatile("nop")

void delay(int time)
{
  while (time--)
  {
    NOP();
  }
}