#include "spawner.h"

#define MEIO_ALTURA 160
#define MEIO_LARGURA 120

typedef enum Posicoes {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
} Posicoes;

Posicoes spawnPosicao = BAIXO;
uint16_t vetor[2] = {0x0, 0x0};

void setUpSpawner(){
    setUpTA(0xffff);
}

uint16_t *SPAWN_podeSpawnar(){
    if (!TA_flagUp()){
        return NULL;
    }
    vetor[0] = 0; 
    vetor[1] = 0;
    switch (spawnPosicao) {
        case BAIXO:
        vetor[0] = 0;
        vetor[1] = 284;
        break;
    }
    return vetor;
}