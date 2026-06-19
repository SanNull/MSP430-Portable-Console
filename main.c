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
 // fill_screen(0x00);
  GAME_init();
  GAME_loop();

  uint16_t previousX, previousY, i;

  // while (1) {
  //   previousX = player->x;
  //   previousY = player->y;
  //   if(INPUT_getX() == 1){
  //     //Anda pra direita
  //     player->x = (player->x < 240) ? ++player->x : player->x; 
  //   }
  //     else if (INPUT_getX() == -1){
  //       player->x = (player->x > 0 ) ? --player->x : player->x; 
  //     }
  //     else if (INPUT_getY() == -1){
  //      player->y = (player->y < 320) ? ++player->y : player->y; 
  //     }
  //     else if (INPUT_getY() == 1){
  //       player->y = (player->y > 0) ? --player->y : player->y; 
  //     }

  //     ZUMBI_perseguirPlayer(inimigo, player);
      
  //   //CleanUp
  //   if (previousX != player->x){
  //     if (previousX > player->x){
  //       LCD_preencherRectangulo(previousX + player->tamanho, previousY, 1, 25, 0x00);        
  //     }
  //     else {
  //       LCD_preencherRectangulo(previousX, previousY, 1, 25, 0x00);
  //     }
  //   }
  //   else if (previousY!= player->y){
  //     if (previousY > player->y){
  //       LCD_preencherRectangulo(previousX, previousY + player->tamanho , 25, 1, 0x00);        
  //     }
  //     else {
  //       LCD_preencherRectangulo(previousX, previousY, 25, 1, 0x00);
  //     }
  //   }    

  //   //Render
  //   LCD_preencherRectangulo(player->x, player->y, player->tamanho, player->tamanho, 0xff);
  //   LCD_preencherRectangulo(inimigo->x, inimigo->y, inimigo->tamanho, inimigo->tamanho, 0xf800);
  // }                      
}
