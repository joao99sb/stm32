#include "core.h"
void delay(int time)
{
  while (time--)
  {
    NOP();
  }
}