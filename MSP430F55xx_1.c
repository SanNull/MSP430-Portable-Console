#include <msp430.h>
#include "timer.h"
#include "som.h"
#include "spi.h"
#include "adc.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  setUpAdc();

  __enable_interrupt();

  
  while(1){
      while (!foi) {
      
      }
      volatile int assda;
      assda = 0;
      foi = 0;
  }                               
}
