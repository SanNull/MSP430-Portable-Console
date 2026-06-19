#include "game.h"

static void input();
static void processar();
static void renderizar();

void GAME_loop(){
    while (1) {
        input();
        processar();
        renderizar();
    }
}