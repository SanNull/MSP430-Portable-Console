#include <msp430.h>
#include <stdint.h>

extern volatile int foi;

void setUpAdc();
int16_t getVRX();
int16_t getVRY();