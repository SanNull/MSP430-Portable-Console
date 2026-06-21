#include <stdint.h>
#include <stdbool.h>

#ifndef SOUND_H
#define SOUND_H

#define CPU_CLK 16000000L

typedef enum NOTAS {
    NENHUMA = 0,
    C4 = 262
} NOTAS;

void SOM_tocarNota(NOTAS nota, uint16_t ms);
void SOM_habilitarMusica(bool habilitar);

#endif