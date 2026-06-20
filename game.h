#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "entidade.h"
#include "zumbi.h"
#include "constantes.h"
#include "input.h"
#include "som.h"
#include "periferico-gpio/lcd.h" //Todo criar middleware de modo que o jogo esteja desacoplado de hardware?

#ifndef GAME_H
#define GAME_H

void GAME_loop();
void GAME_init();

/* Funções Privadas */
// void input();
// void processar();
// void renderizar();

#endif