#include <msp430.h>
#include "timer.h"
#include "som.h"
#include "spi.h"
#include "adc.h"
#include "lcd.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  __enable_interrupt();
  setUpLcd();

  while (1) {
  
  }                      
}
