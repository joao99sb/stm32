// port C
// pin 13

// Memory map
// BLOCK DIAGRAM

// BUS TO CONNECT THIS PIN IN CLOCK IS AHB1

// RCC config clocks sistem

// to enable AHB1, search in reference manula AHB1EN
#include <stdint.h>

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
#define OBSR_R_OFFSET (0X18UL)
#define GPIOC_OBSR_R (*(volatile unsigned int *)(GPIOC_BASE + OBSR_R_OFFSET))
// to enable GPIOC, flip 2 bit to 1

// (1U<<n) => set bit in position n+1 to 1
// ~(1U << n) => set bit in position n+1 to 0

#define GPIOCEN (1U << 2) // 0b00100

#define PIN13 (1U << 13)
#define LED_PIN PIN13

#define __IO volatile

typedef struct
{
  __IO uint32_t DUMMY[2]; /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;  /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
} RCC_TypeDef;

typedef struct
{

  __IO uint32_t MODER; // GPIO port mode regiser                     address offset: 0x00

  __IO uint32_t DUMMY[4];
  __IO uint32_t ODR; // GPIO port output data register             address offset: 0x14

} GPIO_TypeDef;

int main(void)
{

  // enable clock access to GPIOC
  RCC_AHB1EN_R |= GPIOCEN;

  // set P13 as output pin
  GPIOC_MODE_R |= (1U << 26);
  GPIOC_MODE_R &= ~(1U << 27);

  // GPIOC_OD_R |= PIN13;
  while (1)
  {
    GPIOC_OD_R &= ~LED_PIN; // Ligar o LED (nível lógico baixo)
  }
  return 0; //
}