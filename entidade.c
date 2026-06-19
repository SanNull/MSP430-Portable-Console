#include "entidade.h"

entidade *ENTIDADE_criar(uint16_t x, uint16_t y, uint16_t tamanho, uint8_t vida, uint8_t velocidade){
    entidade *e = malloc(sizeof(entidade));
    e->x = x;
    e->y = y;
    e->tamanho = tamanho;
    e->vida = vida;
    e->velocidade = velocidade;
    return  e;
}

void ENTIDADE_remover(entidade *entidade){
    free(entidade);
}