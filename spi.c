#include "spi.h"

#define MISO_PIN BIT0
#define SCK BIT2

void setUpSpi(){
    //Reseta SPI
    UCB0CTL1 = UCSWRST;

    //3PIN SPI, CS -> Always 0
    UCB0CTL0 = UCMSB | UCMST | UCMODE_0 | UCSYNC;

    //Definição de Clock
    UCB0CTL1 |= UCSSEL__ACLK | UCSWRST;
    UCB0BR0 = 64;
    UCB0BR1 = 64;

    //Definição de Pino
    P3SEL |= MISO_PIN + SCK;

    UCB0CTL1 &= ~UCSWRST;
}

void spiSend(uint8_t byte){
    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = byte;
    volatile int x;
    x = 10;
}