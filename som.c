#include "som.h"
#include "periferico-gpio/timer.h"

bool tocandoMusica = false;

void SOM_tocarNota(NOTAS nota, uint16_t ms){
    if (tocandoMusica) {
        while (!PWMT_estaParado());
    }
    uint16_t periodo = CPU_CLK/nota;
    if (nota > 0 && ms > 0) {
        PWMT_habilitarPino(true);
    }

    uint32_t ciclos = (ms * CPU_CLK) / (1000L * periodo);
    setUpPWMT(periodo, periodo/2, ciclos);
    
}

void SOM_habilitarMusica(bool enable){
    tocandoMusica = enable;
}