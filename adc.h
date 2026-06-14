#include <msp430.h>
#include <stdint.h>

extern volatile int foi;

void setUpAdc();
int16_t getX();
int16_t getY();