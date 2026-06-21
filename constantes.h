#ifndef CONSTANTES_H
#define CONSTANTES_H
//LCD
#define LARGURA 240
#define ALTURA 320

//Constantes Jogo
#define ENTIDADES_MAX 5
typedef enum SpritesheetIdx {
    PLAYER,
    ZUMBI,
    BALA
} SpritesheetIdx;

#define VELOCIDADE_ZUMBI 2
#define VELOCIDADE_PLAYER 6

//Constantes Gerais
#define TAMANHO_SPRITE 32
#define COR_MASCARA 0xfb16

#endif