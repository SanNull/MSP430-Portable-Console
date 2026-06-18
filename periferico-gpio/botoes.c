#include "botoes.h"
#include <stdint.h>
#include <stdbool.h>

#define ACTION_PIN BIT5;
#define CIMA_PIN BIT4
#define BAIXO_PIN BIT3
#define ESQUERDA_PIN BIT2
#define DIREITA_PIN BIT6

#define BITS_BOTOES 0x7C

bool habilitado = false;

volatile int xInput = 0;
volatile int yInput = 0;
volatile int action = 0;

void setUpBotoes(){
    habilitado = true;
    P1SEL &= ~(BITS_BOTOES);
    P1DIR &= ~(BITS_BOTOES);

    P1IE |= BITS_BOTOES;
//Low-To-High transition
    P1IES |= ~BITS_BOTOES;

    //Ter certeza que IFG está zerada
    do {
        P1IFG = 0;
    } while (P1IFG != 0);

}

static void habilitarTimer(){
    TA0CTL = TASSEL__SMCLK | ID_0 | MC__CONTINUOUS | TACLR;
    TA0CCR0 = 5000;
    TA0CCTL0 = CCIE;
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer_isr(void)
{
    TA0CTL |= MC__STOP;
    TA0CTL &= ~TAIFG;
    P1IE |= BITS_BOTOES;
}


#pragma vector = PORT1_VECTOR;
__interrupt void port1_isr(void)
{
    switch (__even_in_range(P1IV, 0x10))
    {
    case P1IV_NONE:
        //Nem deveria estar aqui...
        break;

    case P1IV_P1IFG0:
        //P1.0
        break;

    case P1IV_P1IFG1:
        //P1.1
        break;

    case P1IV_P1IFG2:
    P1IE &= ~BIT2;
        //P1.2
        break;

    case P1IV_P1IFG3:
        P1IE &= ~BIT3;
        //P1.3
        break;

    case P1IV_P1IFG4:
    P1IE &= ~BIT4;
        //P1.4
        break;

    case P1IV_P1IFG5:
    P1IE &= ~BIT5;
        //P1.5
        break;

    case P1IV_P1IFG6:
    P1IE &= ~BIT6;
        //P1.6
        break;

    case P1IV_P1IFG7:
        //P1.7
        break;

    default:
        break;
    }
}
