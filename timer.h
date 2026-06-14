#include <stdint.h>
#include <stdbool.h>

#ifndef TIMER_H
#define TIMER_H

uint16_t ticks;

//PWM Timer B
    //Configuração inicial do Timer B
    void setUpPWMT(uint16_t ch0, uint16_t chPrincipal, uint32_t duracao);
    void PWMT_habilitarPino(bool enable);
#endif
