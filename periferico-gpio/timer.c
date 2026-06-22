#include <msp430.h>
#include "timer.h"

#define TIMER_B TB0CTL
#define CH_0_CONTROLADOR TB0CCTL0
#define CH_2_CONTROLADOR TB0CCTL2


#define CH_0 TB0CCR0
#define CH_2 TB0CCR2
#define CH_2_PINO BIT4

uint16_t ticks = 0;
//Duracao do Timer

bool taFlag = false;

void setUpPWMT(uint16_t ch0, uint16_t chPrincipal, uint32_t duracao){

    P7DIR |= CH_2_PINO;
    P7SEL |= CH_2_PINO;

    ticks = duracao;
    CH_0 = ch0;
    CH_2  = chPrincipal;
    

    TIMER_B = TACLR | TASSEL__SMCLK | MC__UP;
    CH_0_CONTROLADOR |= CCIE;
    CH_2_CONTROLADOR |= OUTMOD_7; //RESET/SET
}

void PWMT_habilitarPino(bool enable){
    P7SEL = (enable) ? (P7SEL | CH_2_PINO) : (P7SEL & ~CH_2_PINO);
}

bool PWMT_estaParado(){
    return ticks == 0;
}

void setUpTA(uint16_t duracao){
    taFlag = false;
    TA1CTL = TACLR | TASSEL__ACLK | MC__UP | ID_1;
    TA1CCR0 = duracao;
    TA1CCTL0 |= CCIE;
}
bool TA_flagUp(){
    bool flag = taFlag;
    if (taFlag){
        taFlag = false;
    }
    return flag;
}

void setupADCTimer(){
    TA0CTL = TASSEL__ACLK | MC__UP | TACLR;     //Usa o ACLK: 32768

    TA0CCTL1 =OUTMOD_2;

    TA0CCR0 = 4096;
    TA0CCR1 = 4096/2; 
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void PWMT_isr(){
    if (ticks != 0){
        --ticks;
    }
    if (ticks == 0){
        TIMER_B |= MC__STOP;
        P7SEL &= ~CH_2_PINO;
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA_isr(){
    TA1CTL = TACLR | TASSEL__ACLK | MC__UP | ID_3;
    TA1CCR0 = 0xffff;
    taFlag = true;
}
