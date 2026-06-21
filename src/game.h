#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "entidade.h"
#include "zumbi.h"
#include "constantes.h"
#include "spritesheet.h"
#include "spawner.h"

#include "middleware/som.h"

#ifndef GAME_H
#define GAME_H

void GAME_loop();
void GAME_init();

/* Funções Privadas */
// void input();
// void processar();
// void renderizar();

#endif