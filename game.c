#include "game.h"

entidade listaEntidades[ENTIDADES_MAX] = {
    {.x = 0, .y = 0, .yAnterior = 0, .xAnterior = 0}, //Jogador
    //Zumbi
     {.x = 64, .y = 64, .yAnterior = 64, .xAnterior = 64},
      {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
       {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX},
        {.x = UINT16_MAX, .y = UINT16_MAX, .yAnterior = UINT16_MAX, .xAnterior = UINT16_MAX}, 
};

entidade *player;

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
    for (i = 1; i < ENTIDADES_MAX; i++) {
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
    }
}

static void playerProcess(){
    if (player->x == UINT16_MAX && player->y == UINT16_MAX){
        estadoAtual = GAMEOVER;
        SOM_tocarNota(C4, 1000);
    }
}

static void balaProcess(){

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
