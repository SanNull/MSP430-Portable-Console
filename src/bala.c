#include "bala.h"


Direcao dir = CIMA;
entidade *e = NULL;

void BALA_criar(uint16_t x, uint16_t y, Direcao direcao){
    e = BALA_disponivel();
    if (e != NULL){
        ENTIDADE_habilitar(e, x, y);
        dir = direcao;
    }
}

void BALA_process(){
    if (e == NULL){
        return;
    }
    ENTIDADE_salvarPosicao(e);
    bool desabilitar = false;
    switch (dir) {
        case CIMA:
            ENTIDADE_moverY(e, -1, VELOCIDADE_BALA);
            if (e->y <= 20 || e->y >= ALTURA) desabilitar = true;
        break;
        case BAIXO:
            ENTIDADE_moverY(e, 1, VELOCIDADE_BALA);
            if (e->y >= 270) desabilitar = true;
        break;
        case ESQUERDA:
            ENTIDADE_moverX(e, -1, VELOCIDADE_BALA);
             if (e->x <= 10 || e->x >= LARGURA) desabilitar = true;
        break;
        case DIREITA:
            ENTIDADE_moverX(e, 1, VELOCIDADE_BALA);
            if (e->x >= 190) desabilitar = true;
        break;                        
    }
    if (desabilitar){
        ENTIDADE_desabilitar(e);
        e = NULL;
    }
}

entidade* BALA_disponivel(){
    entidade *b = &listaEntidades[ENTIDADES_MAX - 1];
    if (ENTIDADE_disponivel(b)){
        return b;
    }
    return  NULL;
}