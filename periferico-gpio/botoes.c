#include "botoes.h"
#include <stdint.h>
#include <stdbool.h>

#define ACTION_PIN BIT5;
#define CIMA_PIN BIT4
#define BAIXO_PIN BIT3
#define ESQUERDA_PIN BIT2
#define DIREITA_PIN BIT6
#define BITS_BOTOES 0x7C


volatile uint8_t xInput = 0;
volatile uint8_t yInput = 0;
volatile bool action = 0;

void setUpBotoes(){
    P1SEL &= ~(BITS_BOTOES);
    P1DIR &= ~(BITS_BOTOES);
    //Resitor de Pulldown
    P1REN |= BITS_BOTOES;
    P1OUT &= ~BITS_BOTOES;
}
