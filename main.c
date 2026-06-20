#include <msp430.h>
#include "periferico-gpio/timer.h"
#include "som.h"
#include "periferico-gpio/spi.h"
#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"

#include "entidade.h"
#include "game.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  __enable_interrupt();
  setUpLcd();
  setUpAdc();
  //LCD_preencherTela(0x00);
  GAME_init();
  GAME_loop();
                  
}
