#include "entidade.h"

void ENTIDADE_moverX(entidade *entidade, int8_t direcao, int8_t velocidade){
    uint16_t novoX = entidade->x + velocidade * direcao;
    if (novoX + TAMANHO_SPRITE >= LARGURA || novoX >= LARGURA) {
        return;
    }
    entidade->x = novoX;
}

void ENTIDADE_moverY(entidade *entidade, int8_t direcao, int8_t velocidade){
    uint16_t novoY = entidade->y + velocidade * direcao;
    if (novoY + TAMANHO_SPRITE >= ALTURA || novoY >= ALTURA) {
        return;
    }
    entidade->y = novoY;
}

void ENTIDADE_salvarPosicao(entidade *entidade){
    entidade->xAnterior = entidade->x;
    entidade->yAnterior = entidade->y;
}

void ENTIDADE_tomarDano(entidade *entidade){
    //Leva entidade pra fora do mapa
    entidade->x = UINT16_MAX;
    entidade->y = UINT16_MAX;
}