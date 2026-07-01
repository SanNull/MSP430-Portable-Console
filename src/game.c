#include "game.h"

entidade *player;
Estados estadoAtual = SET;
bool firstInit = true;

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

static void balaInput(Direcao dir);

void GAME_init(){
    LCD_preencherTela(0x0);
    player = &listaEntidades[0];
    estadoAtual = SET;
    setUpSpawner();
    SOM_habilitarMusica(true);
    SOM_tocarNota(C4, 100);
    SOM_tocarNota(523, 100);
    SOM_tocarNota(2093, 200);
  //  SOM_habilitarMusica(false);
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
            LCD_preencherTela(0x0);
            estadoAtual = RESET;
            break;
            case RESET:
            reset();
            break;
        }
    }
}

static void input(){
    int16_t prevDirX = player->x - player->xAnterior;
    int16_t prevDirY = player->y - player->yAnterior;
    //Salva posição no inicio de todo frame
    ENTIDADE_salvarPosicao(player);
    int8_t dirX = INPUT_getX();
    int8_t dirY = INPUT_getY();

    //Prioriza Eixo X
    if (dirX != 0 && dirY != 0) {
        ENTIDADE_moverX(player, dirX, VELOCIDADE_PLAYER);
    }
    else {
        ENTIDADE_moverX(player, dirX, VELOCIDADE_PLAYER);
        ENTIDADE_moverY(player, dirY, VELOCIDADE_PLAYER);
    }

    //Bala
    if (INPUT_getAction()) {
        if (BALA_disponivel() == NULL){
            return;
        }
        Direcao dir = DIREITA;
        if (dirX != 0){
            dir = (dirX == 1) ? DIREITA : ESQUERDA;
        }
        else if (dirY != 0){
            dir = (dirY == 1) ? BAIXO : CIMA;
        }
        else{
            //caso ele não tenha se movido esse frame
        }
        balaInput(dir);
    }
}

static void balaInput(Direcao dir){
    switch (dir) {
        case BAIXO:
        BALA_criar(player->x, player->y + TAMANHO_SPRITE, dir);
        break;
        case CIMA:
        BALA_criar(player->x, player->y - TAMANHO_SPRITE, dir);
        break;
        case ESQUERDA:
        BALA_criar(player->x - TAMANHO_SPRITE, player->y, dir);
        break;
        case DIREITA:
        BALA_criar(player->x + TAMANHO_SPRITE, player->y, dir);
        break;
    }
}

static void processar(){
    balaProcess();
    zumbiProcess(); //Perseguiçao dos zumbis
    playerProcess();
    uint16_t v = SPAWN_podeSpawnar(); 
    if (v){
        uint16_t x = SPAWN_localX();
        uint16_t y = SPAWN_localY();
        uint8_t i = 1;
        entidade *e = ZUMBI_disponivel(&listaEntidades);
        if (e != NULL){
            ENTIDADE_habilitar(e, x, y);
        }
    }
}

static void renderizar(){
    int8_t i;
    entidade *e;
    for (i = 0; i < ENTIDADES_MAX; i++){
        e = &listaEntidades[i];
        if (e->x == UINT16_MAX && e->y == UINT16_MAX){
            LCD_preencherRectangulo(e->xAnterior, e->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x00);
            continue;            
        }
        limparFrame(e);
            if (i == 0){
                SPRITESHEET_desenharSprite(PLAYER, e->x, e->y);
            }
            else if (i < ENTIDADES_MAX - 1){
                SPRITESHEET_desenharSprite(ZUMBI, e->x, e->y);
            }
            else {
                LCD_preencherRectangulo(e->x, e->y, TAMANHO_SPRITE/2, TAMANHO_SPRITE/2, 0xfd00);
            }        
    }
}

static void limparFrame(entidade *e){
    LCD_preencherRectangulo(e->xAnterior, e->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x0);
    if (e->x != e->xAnterior){
        LCD_preencherRectangulo(e->xAnterior, e->y, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x0);
    }
    else if (e->y != e->yAnterior) {
        LCD_preencherRectangulo(e->x, e->yAnterior, TAMANHO_SPRITE, TAMANHO_SPRITE, 0x0);
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
        SOM_tocarNota(C4, 100);
        SOM_tocarNota(NENHUMA, 400);
        SOM_tocarNota(65, 100);
        SOM_tocarNota(NENHUMA, 400);
        SOM_tocarNota(16, 800);
    }
}

static void balaProcess(){
    BALA_process();
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
