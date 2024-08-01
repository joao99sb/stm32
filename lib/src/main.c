#include "./core.h"
#include "./GPIO.h"
#include "i2c_driver.h"
// #define SCREEN_ADDRESS 0x3C

int main(void)
{
  i2c_init();
  configPin(PORTC, OUTPUT, LED_PIN);

  while (1)
  {

    setPin(PORTC, LED_PIN, LOW);
    delay(1000000);
    setPin(PORTC, LED_PIN, HIGH);
    delay(1000000);
  }
  return 0;
}