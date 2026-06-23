#include "spi.h"

#define MOSI_PIN BIT0
#define SCK BIT2

void setUpSpi(){
    //Reseta SPI
    UCB0CTL1 = UCSWRST;

    //3PIN SPI, CS -> Always 0
    UCB0CTL0 = UCMSB | UCMST | UCMODE_0 | UCSYNC | UCCKPH;

    //Definição de Clock
    UCB0CTL1 |= UCSSEL__SMCLK | UCSWRST;
    UCB0BR0 = 0;
    UCB0BR1 = 0;

    //Definição de Pino
    P3SEL |= MOSI_PIN + SCK;

    UCB0CTL1 &= ~UCSWRST;
    UCB0IFG &= ~UCTXIFG;
}

void SPI_enviar(uint8_t byte){
    while (UCB0STAT & UCBUSY ); //TX Buffer está vazio?
    UCB0TXBUF = byte;
}

bool SPI_estaOcupado(){
    return UCB0STAT & UCBUSY;
}
