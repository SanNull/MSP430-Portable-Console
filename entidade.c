#include "entidade.h"

entidade *ENTIDADE_criar(uint16_t x, uint16_t y, uint16_t tamanho, uint8_t vida, uint8_t velocidade){
    entidade *e = malloc(sizeof(entidade));
    e->x = x;
    e->y = y;
    e->xAnterior = x;
    e->yAnterior = y;
    e->tamanho = tamanho;
    e->vida = vida;
    e->velocidade = velocidade;
    return  e;
}

void ENTIDADE_remover(entidade *entidade){
    free(entidade);
    entidade = NULL;
}

void ENTIDADE_moverX(entidade *entidade){
    entidade->xAnterior = entidade->x;
    entidade->x += entidade->velocidade;
}

void ENTIDADE_moverY(entidade *entidade){
    entidade->yAnterior = entidade->y;
    entidade->y += entidade->velocidade;
}

void ENTIDADE_tomarDano(entidade *entidade){
    --entidade->vida;
}