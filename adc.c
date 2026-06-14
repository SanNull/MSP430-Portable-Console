#include "adc.h"

//P6.0 - Eixo X, P6.1 Eixo Y
#define X_PIN BIT0
#define Y_PIN BIT1

volatile int16_t eixo_x;
volatile int16_t eixo_y;

volatile int foi = 0;

void setUpAdc(){

    TA0CTL = TASSEL__ACLK |     //Usa o ACLK: 32768
                     MC__UP | TACLR;              //Timer parado

    TA0CCTL1 =OUTMOD_2;

    TA0CCR0 = 32768;
    TA0CCR1 = 16384;    

    P6SEL |= BIT0 + BIT1;    

    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 |= ADC12SHT0_2 | ADC12ON; // | ADC12MSC

    // Canais múltiplos, SHP pelo timer, MODCLOCK
    ADC12CTL1 = ADC12CSTARTADD_0 | ADC12SHS_1 | ADC12SHP | ADC12SSEL_0 | ADC12CONSEQ_3;

    ADC12CTL2 = ADC12TCOFF | ADC12RES_0 | ADC12DF;

    ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_0;
    ADC12MCTL1 = ADC12SREF_0 | ADC12INCH_1 | ADC12EOS;

    //Interrupções
    ADC12IE = ADC12IE0 | ADC12IE1;

    ADC12CTL0 |= ADC12ENC;
}

int16_t getX(){
    return eixo_x;
}

int16_t getY(){
    return eixo_y;
}

#pragma vector = ADC12_VECTOR
__interrupt void adc12_isr(){
    switch (ADC12IV) {
        case ADC12IV_ADC12IFG0:
            eixo_x = ADC12MEM0;
            foi = 1;
            break;
        case ADC12IV_ADC12IFG1:
            eixo_y = ADC12MEM1;
            foi = 1;
            break;
        default: break;
    }
}