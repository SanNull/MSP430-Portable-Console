#include <msp430.h>
#include "timer.h"
#include "som.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                                       
  __enable_interrupt();

  NOTAS n = C4;
  NOTAS n2 = NENHUMA;
  
  while(1){
    
  }                               
}
