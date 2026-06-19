#include "game.h"
#include "entidade.h"

entidade **listaEntidades;
entidade *player;

uint8_t idx = 0;

static void input();
static void processar();
static void renderizar();
//limpa resquísios de frame anterior
static void limparFrame(entidade *e);

void GAME_init(){
    listaEntidades = malloc(sizeof(entidade) * ENTIDADES_MAX);
    listaEntidades[idx++] = ENTIDADE_criar(0, 0, 24, 1, 8);
    listaEntidades[idx++] = ENTIDADE_criar(64, 64, 24, 1, 4);
    player = listaEntidades[0];
}

void GAME_loop(){
    while (1) {
        input();
        processar();
        renderizar();
    }
}

static void input(){
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
    //Perseguiçao dos zumbis
    int8_t i;
    entidade *zumbi;
    for (i = 1; i < idx; i++) {
        zumbi = listaEntidades[i];
        ZUMBI_perseguirPlayer(zumbi, player);
        if (ZUMBI_tocouPlayer(zumbi, player)) {
            ENTIDADE_tomarDano(player);
            if (player->vida == 0){
                break;
            }
        }
    }
}

static void renderizar(){
    int8_t i;
    entidade *e;
    for(i = 0; i < idx; i++){
        e = listaEntidades[i];
        if (e->vida == 0){
            LCD_preencherRectangulo(e->x, e->y, e->tamanho, e->tamanho, 0x00);
            continue;
        }
        //CleanUp
        if (e->x != e->xAnterior){
            LCD_preencherRectangulo(e->xAnterior, e->y, e->tamanho, e->tamanho, 0x00);
        }
        else if (e->y != e->yAnterior) {
            LCD_preencherRectangulo(e->x, e->yAnterior, e->tamanho, e->tamanho, 0x00);
        } 
        //Desenha novo frame
        if (e->vida > 0) {
            if (i == 0){
                LCD_preencherRectangulo(e->x, e->y, e->tamanho, e->tamanho, 0xff);
            }
            else {
                LCD_preencherRectangulo(e->x, e->y, e->tamanho, e->tamanho, 0xf800);
            }
        }
    }
}

static void limparFrame(entidade *e){

}
