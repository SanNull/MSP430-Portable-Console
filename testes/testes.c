#include "testes.h"

#define constante 0.03

void TEST_joystick(){
  __enable_interrupt();
  setUpAdc();
  setUpLcd();

  entidade *player = &listaEntidades[0];

  volatile int16_t joyX;
  volatile int16_t x;
  volatile int16_t joyY;
  volatile int16_t y;  

while (1){

    ENTIDADE_salvarPosicao(player);

//Eixo X
joyX = getVRY();
    if (joyX >= 2000 ||  joyX <= -2000){
         x =  (joyX & 1 << 15) ? -1: 1;   //Verifica se MSB é 1 (numero negativo)
    }
    else{
      x = 0;     //Limiar zero
    }

//eixo Y
  joyY = getVRX();
    if (joyY >= 2000 ||  joyY <= -2000){
        y =  (joyY & 1 << 15) ? -1: 1;     //Verifica se MSB é 1 (numero negativo)
    }
    else{
      y =  0;     //Limiar zero
    }

    ENTIDADE_moverX(player, x, VELOCIDADE_PLAYER);
    ENTIDADE_moverY(player, y, VELOCIDADE_PLAYER);
    LCD_preencherRectangulo(player->xAnterior, player->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0X00);
    SPRITESHEET_desenharSprite(PLAYER, player->x, player->y);

    volatile int temp;
    temp = 0;
    __delay_cycles(1000000);
}

}

void TEST_dpad(){
  __enable_interrupt();
  setUpBotoes();
  setUpLcd();

  entidade *player = &listaEntidades[0];

  volatile int16_t diffX;
  volatile int16_t diffY;
  volatile int16_t xPad;
  volatile int16_t yPad;  

while (1){

    ENTIDADE_salvarPosicao(player);

//Eixo X
xPad = BOTOES_getX();

//eixo Y
yPad = BOTOES_getY();

  ENTIDADE_moverX(player, xPad, VELOCIDADE_PLAYER);
  ENTIDADE_moverY(player, yPad, VELOCIDADE_PLAYER);
  LCD_preencherRectangulo(player->xAnterior, player->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0X00);
  SPRITESHEET_desenharSprite(PLAYER, player->x, player->y);

diffX = player->x - player->xAnterior;
diffY = player->y - player->yAnterior;

  __delay_cycles(1000000);
}  
}

void TEST_piezzoTrigger(){
  //Já que player tem 32 pixels de largura e começa na posição (0,0), a colisão entre zumbi-player acontecerá quando posição do zumbi for igual a (32,0)
  volatile uint16_t posicaoContatoJogador[6] = {32,32,32, 32, 32, 32} ; 
  volatile uint16_t posicaoZumbi[6]= {0};
  volatile bool buzzerIsOn[15] = {0};
  int idx = 0;

  //Inicializando Entidades
  entidade *player = &listaEntidades[0];
  entidade *zumbi = &listaEntidades[1];
  zumbi->x = 42;
  zumbi->y = 0;
  while (!ZUMBI_tocouPlayer(zumbi, player)) {
    posicaoZumbi[idx] = zumbi->x;
    buzzerIsOn[idx] = !PWMT_estaParado(); //Checa se o buzzer stá acionado 
    ZUMBI_perseguirPlayer(zumbi, player);
    ++idx;
  }
  posicaoZumbi[idx] = zumbi->x;
  SOM_tocarNota(C4, 100);
  while (idx < 15) {
    buzzerIsOn[idx++] = !PWMT_estaParado();
  }
  idx = 0;

}