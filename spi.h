#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#ifndef SPI_H
#define SPI_H

void setUpSpi();
void SPI_enviar(uint8_t byte);
bool SPI_estaOcupado();

#endif