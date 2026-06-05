#include <stdint.h>
#ifndef SOUND_H
#define SOUND_H

#define CPU_CLK 1000000L

typedef enum NOTAS {
    NENHUMA = 0,
    C4 = 262
} NOTAS;

void tocarNota(NOTAS nota, uint16_t ms);

#endif