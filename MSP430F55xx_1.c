#include <msp430.h>
#include "timer.h"
#include "som.h"
#include "spi.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  setUpSpi();
  spiSend(0x55);
  spiSend(0x00);

  __enable_interrupt();

  NOTAS n = C4;
  NOTAS n2 = NENHUMA;
  
  while(1){
    
  }                               
}
