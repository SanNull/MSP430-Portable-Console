#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef BOTOES_H
#define BOTOES_H

void setUpBotoes();
bool BOTOES_getAction();
int8_t BOTOES_getX();
int8_t BOTOES_getY();


#endif