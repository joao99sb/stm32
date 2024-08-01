#include "./core.h"

void configureCPin()
{
  // enable clock access to GPIOC
  RCC->AHB1ENR |= GPIOCEN;

  // set P13 as output pin

  GPIOC->MODER |= (1U << 26);
  GPIOC->MODER &= ~(1U << 27);
}

int main(void)
{

  configureCPin();

  while (1)
  {
    GPIOC->ODR &= ~LED_PIN; // Ligar o LED (nível lógico baixo)

    delay(1000000);
    GPIOC->ODR |= LED_PIN;
    delay(1000000);
  }
  return 0;
}