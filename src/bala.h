#include "entidade.h"
#include "constantes.h"

#ifndef BALA_H
#define BALA_H

//Direção da bala em relação ao jogador
typedef enum Direcao{
    CIMA ,
    BAIXO ,
    ESQUERDA ,
    DIREITA
} Direcao;

entidade* BALA_disponivel();
void BALA_criar(uint16_t x, uint16_t y, Direcao direcao);
void BALA_process();

#endif