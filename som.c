#include "som.h"
#include "timer.h"

void tocarNota(NOTAS nota, uint16_t ms){
    
    uint16_t periodo = CPU_CLK/nota;
    if (nota > 0 && ms > 0) {
        PWMT_habilitarPino(true);
    }

    uint32_t ciclos = (ms * CPU_CLK) / (1000L * periodo);
    setUpPWMT(periodo, periodo/2, ciclos);
    
}