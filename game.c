#include "game.h"

entidade **listaEntidades = NULL;
entidade *player;
uint8_t idx = 0;

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
    if (listaEntidades == NULL){
        listaEntidades = malloc(sizeof(entidade) * ENTIDADES_MAX);
    }
    listaEntidades[idx++] = ENTIDADE_criar(0, 0, TAMANHO_SPRITE, 1, 16);
    listaEntidades[idx++] = ENTIDADE_criar(64, 64, TAMANHO_SPRITE, 1,8 );
    player = listaEntidades[0];
    estadoAtual = SET;
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
            __delay_cycles(100000*2);
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
    //Prioriza Eixo X
    if (dirX != 0 && dirY != 0) {
        ENTIDADE_moverX(player, dirX);
        return;
    }
    ENTIDADE_moverX(player, dirX);
    ENTIDADE_moverY(player, dirY);
}

static void processar(){
    balaProcess();
    zumbiProcess(); //Perseguiçao dos zumbis
    playerProcess();
}

static void renderizar(){
    int8_t i;
    entidade *e;
    for (i = 0; i < idx; i++){
        e = listaEntidades[i];
        if (e->vida == 0){
            LCD_preencherRectangulo(e->x, e->y, e->tamanho, e->tamanho, 0x00);
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
        LCD_preencherRectangulo(e->xAnterior, e->y, e->tamanho, e->tamanho, 0x00);
    }
    else if (e->y != e->yAnterior) {
        LCD_preencherRectangulo(e->x, e->yAnterior, e->tamanho, e->tamanho, 0x00);
    } 
}

//////////////////////////////

static void zumbiProcess(){
    int8_t i;
    entidade *zumbi;
    for (i = 1; i < idx; i++) {
        zumbi = listaEntidades[i];
        if (zumbi->vida == 0) {
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
    if (player->vida == 0){
        estadoAtual = GAMEOVER;
        SOM_tocarNota(C4, 1000);
    }
}

static void balaProcess(){

}

///////////////////////////////////////

static void reset() {
    int8_t i;
    for ( i = 0; i < idx; i++){
        ENTIDADE_remover(listaEntidades[i]);    
    }
    idx = 0;
    player = NULL;
    GAME_init();
}
