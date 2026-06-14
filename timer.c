#include <msp430.h>
#include "timer.h"

#define TIMER_B TB0CTL
#define CH_0_CONTROLADOR TB0CCTL0
#define CH_2_CONTROLADOR TB0CCTL2


#define CH_0 TB0CCR0
#define CH_2 TB0CCR2
#define CH_2_PINO BIT4

//Duracao do Timer

void setUpPWMT(uint16_t ch0, uint16_t chPrincipal, uint32_t duracao){

    P7DIR |= CH_2_PINO;
    P7SEL |= CH_2_PINO;

    ticks = duracao;
    CH_0 = ch0;
    CH_2  = chPrincipal;
    

    TIMER_B = TACLR | TASSEL__SMCLK | MC__UP;
    CH_0_CONTROLADOR |= CCIE;
    CH_2_CONTROLADOR |= OUTMOD_7;
}

void PWMT_habilitarPino(bool enable){
    P7SEL = (enable) ? (P7SEL | CH_2_PINO) : (P7SEL & ~CH_2_PINO);
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void PWMT_isr(){
    --ticks;
    if (ticks == 0){
        TIMER_B |= MC__STOP;
        P7SEL &= ~CH_2_PINO;
    }
}
