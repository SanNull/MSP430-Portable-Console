#include <stdint.h>
#include <msp430.h>
#ifndef SPI_H
#define SPI_H

void setUpSpi();
void spiSend(uint8_t byte);

#endif