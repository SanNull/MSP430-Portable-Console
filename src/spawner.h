#include <stdint.h>
#include "periferico-gpio/timer.h"
#include <stdlib.h>

#ifndef SPAWNER_H
#define SPAWNER_H

void setUpSpawner();
bool SPAWN_podeSpawnar();
uint16_t SPAWN_localX();
uint16_t SPAWN_localY();
#endif