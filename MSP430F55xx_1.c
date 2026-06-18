#include <msp430.h>
#include "periferico-gpio/timer.h"
#include "som.h"
#include "periferico-gpio/spi.h"
#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  __enable_interrupt();
  //setUpLcd();
  SOM_habilitarMusica(true);
  SOM_tocarNota(C4, 2000);
  SOM_tocarNota(NENHUMA,200);


  while (1) {
  
  }                      
}
