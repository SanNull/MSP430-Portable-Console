#include "spawner.h"

//Locais do spawn
#define MEIO_ALTURA 160
#define MEIO_LARGURA 120
#define FIM_ALTURA 320 - 40
#define INICIO_ALTURA 0
#define FIM_LARGURA 200


typedef enum TempoSpawn{
    SEG5 = 40958,
    SEG3 = 24575,
    SEG2 = 16383
} TempoSpawn;

TempoSpawn tempoAtual = SEG5;

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
    setUpTA(SEG5);
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
    switch (tempoAtual) {
        case SEG5:
            tempoAtual = SEG2;
            break;
        case SEG3:
            tempoAtual = SEG5;
            break;
        case SEG2:
            tempoAtual = SEG3;
            break;
    }
    setUpTA(tempoAtual);
    return true;
}

uint16_t SPAWN_localX() {
    return  posX;
}
uint16_t SPAWN_localY() {
    return  posY;
}