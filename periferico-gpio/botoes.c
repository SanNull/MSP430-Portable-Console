#include "botoes.h"
#include <stdint.h>
#include <stdbool.h>

#define ACTION_PIN BIT5;
#define CIMA_PIN BIT3
#define BAIXO_PIN BIT4
#define ESQUERDA_PIN BIT6
#define DIREITA_PIN BIT2
#define BITS_BOTOES 0x7C


volatile uint8_t xInput = 0;
volatile uint8_t yInput = 0;
volatile bool action = false;
volatile bool safeGuard = true; //BUG interrupção começa assim que habilitada;

void setUpBotoes(){
    P1SEL &= ~(BITS_BOTOES);
    P1DIR &= ~(BITS_BOTOES);
    //Resitor de Pulldown
    P1REN |= BITS_BOTOES;
    P1OUT &= ~BITS_BOTOES;
    //Interrupção pro action pin
    P1IE |= ACTION_PIN;
    P1IES |= ACTION_PIN;
    do {
    P1IFG = 0;
    }while (P1IFG != 0);
}

bool BOTOES_getAction(){
    bool act = action;
    action = false; //Reseta Action se tiver sido pressionado
    return  act;
}

int8_t BOTOES_getX(){
    return (P1IN & DIREITA_PIN) ? 1 : ((P1IN & ESQUERDA_PIN) ? -1 : 0);
}

int8_t BOTOES_getY(){
    return (P1IN & BAIXO_PIN) ? 1 : ((P1IN & CIMA_PIN) ? -1 : 0);
}

#pragma vector = PORT1_VECTOR
__interrupt void action_isr(){
    //Skip primeira interrução que acontece depois de habilitá-la
    if (!safeGuard){
        action = true;
    }
    do {
    P1IFG = 0;
    }while (P1IFG != 0);    
    safeGuard = false;
}

