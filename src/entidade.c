#include "entidade.h"

entidade listaEntidades[ENTIDADES_MAX] = 
{
    {.x = 0, .y = 0, .yAnterior = 0, .xAnterior = 0}, //Jogador
    //Zumbis
    {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
    {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
    {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
    {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX}, 
        
    {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX} //Bala
};

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

void ENTIDADE_habilitar(entidade *entidade, uint16_t x, uint16_t y){
    entidade->x = x;
    entidade->y = y;
}

void ENTIDADE_desabilitar(entidade *entidade){
    ENTIDADE_tomarDano(entidade);
}

bool ENTIDADE_disponivel(entidade *entidade){
    return (entidade->x == UINT16_MAX && entidade->y == UINT16_MAX);
}