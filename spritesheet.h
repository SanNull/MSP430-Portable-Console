#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include "constantes.h"
#include "periferico-gpio/lcd.h"
#ifndef SPRITE_H
#define SPRITE_H

void SPRITESHEET_carregarSritesheet(char *arquivo);
void SPRITESHEET_desenharSprite(SpritesheetIdx index, uint16_t x, uint16_t y);

#endif