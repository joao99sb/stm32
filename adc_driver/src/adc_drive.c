
#include "./adc_drive.h"

void pa1_adc_init(void)
{

  /**configure the adc gpio pin**/
  // enable clock access to adc pin's port
  RCC->AHB1ENR |= GPIOAEN;

  // set the mode of pa1 to analog
  GPIOA->MODER |= (1U << 2);
  GPIOA->MODER |= (1U << 3);

  /**configure de adc module**/
}