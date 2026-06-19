#include <msp430.h>
#include "periferico-gpio/timer.h"
#include "som.h"
#include "periferico-gpio/spi.h"
#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"

#include "entidade.h"

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;
  __enable_interrupt();
  setUpLcd();
  setUpAdc();
  LCD_setCursor(0, 0);

  entidade *player  =ENTIDADE_criar(0, 0, 24, 2, 2);
  entidade *inimigo = ENTIDADE_criar(64, 64, 24, 1, 1);
  
  LCD_preencherRectangulo(player->x, player->y, player->tamanho, player->tamanho, 0xff);
  LCD_preencherRectangulo(inimigo->x, inimigo->y, inimigo->tamanho, inimigo->tamanho, 0xf800);

  ENTIDADE_remover(inimigo);
  inimigo;

  int y = 0;
  int x = 0;

  int previousX = 0;


  int i = 0;
  y = 0;

  while (1) {
    previousX = x;
    if(getVRX() > 1500){
      //Anda pra direita
      
      ++x;
    }
      else if (getVRX() < -1500){
        --x;
      }

    //CleanUp
    if (previousX != x){
          for (i = 0; i <= 24; i++) {
      LCD_setCursor(previousX, y++);
      draw_pixel(0x00);
    }
    y = 0;
    }
    LCD_setCursor(x, y);
  for (i = 0; i < 576; i++){
    if ((i % 24) == 0) {
      LCD_setCursor(x, ++y);
    }
    draw_pixel(0xffc0);
  }
  y = 0;
  }                      
}
