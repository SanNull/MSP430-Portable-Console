#include <stdint.h>
#include "periferico-gpio/adc.h"

#ifndef INPUT_H
#define INPUT_H

//Funções Privadas
// int8_t getJoystickX();
// int8_t getJoystickY();
// int8_t getDpadX();
// int8_t getDpadY();

int8_t INPUT_getX();
int8_t INPUT_getY();

#endif