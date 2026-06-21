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
  //Mudar clock
  UCSCTL1 = DCORSEL_5; //Select DCO range 16MHz operation
  UCSCTL2 |= (249*2);   //Calcula pra gerar  clk de 16mhz
  UCSCTL3 = SELREF_2; //REFCLK 32K
  UCSCTL4 |= SELS_2; //SMLCK = REFO//     

  __enable_interrupt();
  setUpLcd();
  setUpAdc();
  //LCD_preencherTela(0x00);
  GAME_init();
  GAME_loop();
                  
}
