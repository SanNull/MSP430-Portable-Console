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

void ENTIDADE_moverX(entidade *entidade, int8_t direcao){
    uint16_t novoX = entidade->x + entidade->velocidade * direcao;
    if (novoX + entidade->tamanho >= LARGURA || novoX >= LARGURA) {
        return;
    }
    entidade->xAnterior = entidade->x;
    entidade->x = novoX;
}

void ENTIDADE_moverY(entidade *entidade, int8_t direcao){
    uint16_t novoY = entidade->y + entidade->velocidade * direcao;
    if (novoY + entidade->tamanho >= ALTURA || novoY >= ALTURA) {
        return;
    }
    entidade->yAnterior = entidade->y;
    entidade->y = novoY;
}

void ENTIDADE_tomarDano(entidade *entidade){
    --entidade->vida;
}