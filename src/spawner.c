#include "spawner.h"

#define MEIO_ALTURA 160
#define MEIO_LARGURA 120
#define FIM_ALTURA 320 - 40
#define INICIO_ALTURA 0
#define FIM_LARGURA 200

uint16_t posX = 0;
uint16_t posY = 0;

typedef enum Posicoes {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
} Posicoes;

Posicoes spawnPosicao = BAIXO;

void setUpSpawner(){
    setUpTA(0xffff);
}

bool SPAWN_podeSpawnar(){
    if (!TA_flagUp()){
        return false;
    }
    posX = 0; 
    posY = 0;
    switch (spawnPosicao) {
        case BAIXO:
        posX = MEIO_LARGURA;
        posY = FIM_ALTURA;
        spawnPosicao = CIMA;
        break;
        case CIMA:
        posX = MEIO_LARGURA;
        posY = INICIO_ALTURA;
        spawnPosicao = ESQUERDA;
        break;
        case ESQUERDA:
        posX = 0;
        posY = MEIO_ALTURA;
        spawnPosicao = DIREITA;
        break;
        case DIREITA:
        posX = FIM_LARGURA;
        posY = MEIO_ALTURA;
        spawnPosicao = BAIXO;
        break;
    }
    return true;
}

uint16_t SPAWN_localX() {
    return  posX;
}
uint16_t SPAWN_localY() {
    return  posY;
}