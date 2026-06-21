#include <msp430.h>
#include "periferico-gpio/timer.h"
#include "som.h"
#include "periferico-gpio/spi.h"
#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"

#include "spritesheet.h"
#include "entidade.h"
#include "game.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
    setUpBotoes();
  __enable_interrupt();
  while (1) {
  
  }
  // setUpLcd();
  // setUpAdc();
  // //LCD_preencherTela(0x00);
  // GAME_init();
  // GAME_loop();
                  
}
