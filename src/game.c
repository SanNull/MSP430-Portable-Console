#include "game.h"

entidade listaEntidades[ENTIDADES_MAX] = {
    {.x = 0, .y = 0, .yAnterior = 0, .xAnterior = 0}, //Jogador
    //Zumbi
     {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
      {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
       {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
        {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX}, 
        {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX} //Bala
};


entidade *player;
uint8_t direcaoBala = 0;
uint8_t direcaoYBala = 0;

typedef enum Estados {
    SET,
    GAMEOVER,
    RESET
}Estados;

Estados estadoAtual = SET;

//Game loop
static void input();
static void processar();
static void renderizar();
static void limparFrame(entidade *e); //limpa resquísios de frame anterior

//Processos
static void zumbiProcess();
static void playerProcess();
static void balaProcess();

//Estados
static void gameover();
static void reset();

void GAME_init(){
    LCD_preencherTela(0x00);
    player = &listaEntidades[0];
    estadoAtual = SET;
    setUpSpawner();
}

void GAME_loop(){
    while (1) {
        switch (estadoAtual) {
            case SET:
            input();
            processar();
            renderizar();
            break;
            case GAMEOVER:
            __delay_cycles(500000*2);
            LCD_preencherTela(0x00);
            estadoAtual = RESET;
            break;
            case RESET:
            reset();
            break;
        }
    }
}

static void input(){
    //Salva posição antes
    ENTIDADE_salvarPosicao(player);
    int8_t dirX = INPUT_getX();
    int8_t dirY = INPUT_getY();

    //Bala

    if (INPUT_getAction()){
        entidade *bala = &listaEntidades[ENTIDADES_MAX - 1];
        if (bala->x == UINT16_MAX && bala->y == UINT16_MAX) {
            bala->x = player->x;
            bala->y = player->y + TAMANHO_SPRITE;
            bala->xAnterior = player->x + TAMANHO_SPRITE;
            bala->yAnterior = player->y;
            direcaoYBala = 1;
        }
    }

    //Prioriza Eixo X
    if (dirX != 0 && dirY != 0) {
        ENTIDADE_moverX(player, dirX, VELOCIDADE_PLAYER);
        return;
    }
    ENTIDADE_moverX(player, dirX, VELOCIDADE_PLAYER);
    ENTIDADE_moverY(player, dirY, VELOCIDADE_PLAYER);

}

static void processar(){
    balaProcess();
    zumbiProcess(); //Perseguiçao dos zumbis
    playerProcess();
    uint16_t *v = SPAWN_podeSpawnar(); 
    if (v != NULL){
        uint8_t i = 1;
        entidade *e = NULL;
        for (i = 1; i < ENTIDADES_MAX; i++) {
            e = &listaEntidades[i];
            if (e->x == UINT16_MAX && e->y == UINT16_MAX){
                break;
            }
            else {
                e = NULL;
            }
        }
        if (e != NULL){
            e->x = v[0];
            e->y = v[1];
            e->xAnterior = v[0];
            e->yAnterior = v[1];
        }
        v = NULL;
    }
}

static void renderizar(){
    int8_t i;
    entidade *e;
    for (i = 0; i < ENTIDADES_MAX; i++){
        e = &listaEntidades[i];
        if (e->x == UINT16_MAX && e->y == UINT16_MAX){
            LCD_preencherRectangulo(e->x, e->y, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x00);
            continue;            
        }
        limparFrame(e);
            if (i == 0){
                SPRITESHEET_desenharSprite(PLAYER, e->x, e->y);
            }
            else {
                SPRITESHEET_desenharSprite(PLAYER, e->x, e->y);
            }        
    }
}

static void limparFrame(entidade *e){
    if (e->x != e->xAnterior){
        LCD_preencherRectangulo(e->xAnterior, e->y, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x00);
    }
    else if (e->y != e->yAnterior) {
        LCD_preencherRectangulo(e->x, e->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x00);
    } 
}

//////////////////////////////

static void zumbiProcess(){
    int8_t i;
    entidade *zumbi;
    for (i = 1; i < ENTIDADES_MAX - 1; i++) {
        zumbi = &listaEntidades[i];
        if (zumbi->x == UINT16_MAX && zumbi->y == UINT16_MAX) {
            continue;
        }
        ENTIDADE_salvarPosicao(zumbi);
        ZUMBI_perseguirPlayer(zumbi, player);
        if (ZUMBI_tocouPlayer(zumbi, player)){
            ENTIDADE_tomarDano(player);
            break;
        }
        else if (ZUMBI_tocouPlayer(zumbi, &listaEntidades[ENTIDADES_MAX-1])) {
            ENTIDADE_tomarDano(zumbi);
            ENTIDADE_tomarDano( &listaEntidades[ENTIDADES_MAX-1]);
        }
    }
}

static void playerProcess(){
    if (player->x == UINT16_MAX && player->y == UINT16_MAX){
        estadoAtual = GAMEOVER;
        SOM_tocarNota(C4, 1000);
    }
}

static void balaProcess(){
    ENTIDADE_salvarPosicao(&listaEntidades[ENTIDADES_MAX-1]);
    if (direcaoBala == 0 && direcaoYBala == 0){
        return;
    }
    if (direcaoBala){
        ENTIDADE_moverX(&listaEntidades[ENTIDADES_MAX-1], direcaoBala, 12);
    }
    else {
        ENTIDADE_moverY(&listaEntidades[ENTIDADES_MAX-1], direcaoYBala, 12);
    }
    if (listaEntidades[ENTIDADES_MAX-1].x >= LARGURA || listaEntidades[ENTIDADES_MAX-1].x < 0) {
        ENTIDADE_tomarDano(&listaEntidades[ENTIDADES_MAX-1]);
    }
}

///////////////////////////////////////

static void reset() {
    int8_t i;
    entidade *e = &listaEntidades[0];
    e->x = 0;
    e->y = 0;
    e->xAnterior = 0;
    e->yAnterior = 0;
    for ( i = 1; i < ENTIDADES_MAX; i++){
       e = &listaEntidades[i];
        e->x = UINT16_MAX;
        e->y = UINT16_MAX;
        e->xAnterior = UINT16_MAX;
        e->yAnterior = UINT16_MAX;       
    }
    player = NULL;
    GAME_init();
}
