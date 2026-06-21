#include <stdint.h>
#include "periferico-gpio/timer.h"
#include <stdlib.h>

#ifndef SPAWNER_H
#define SPAWNER_H

void setUpSpawner();
//Retorna localização do inimigo caso seja momento de spawnar um
uint16_t* SPAWN_podeSpawnar();

#endif