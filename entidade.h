#include <stdint.h>
#include <stdlib.h>

#ifndef ENTIDADE_H 
#define ENTIDADE_H

typedef struct entidade {
    uint16_t x;
    uint16_t y;
    uint16_t tamanho;    
    uint8_t vida;
    uint8_t velocidade;
}entidade;

entidade *ENTIDADE_criar(uint16_t x, uint16_t y, uint16_t tamanho, uint8_t vida, uint8_t velocidade);
void ENTIDADE_remover(entidade *entidade);

#endif