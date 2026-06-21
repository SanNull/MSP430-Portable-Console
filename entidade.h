#include <stdint.h>
#include <stdlib.h>
#include "constantes.h"
#include "helpers.h"

#ifndef ENTIDADE_H 
#define ENTIDADE_H

typedef struct entidade {
    uint16_t x;
    uint16_t y;
    uint16_t xAnterior;
    uint16_t yAnterior;
}entidade;

void ENTIDADE_moverX(entidade *entidade, int8_t direcao, int8_t velocidade);
void ENTIDADE_moverY(entidade *entidade, int8_t direcao, int8_t velocidade);
void ENTIDADE_tomarDano(entidade *entidade);
//Salvar posição do frame anterior
void ENTIDADE_salvarPosicao(entidade *entidade);

#endif