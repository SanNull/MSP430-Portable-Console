#include <stdint.h>
#include <stdbool.h>

#ifndef TIMER_H
#define TIMER_H


//PWM Timer B
    //Configuração inicial do Timer B
    void setUpPWMT(uint16_t ch0, uint16_t chPrincipal, uint32_t duracao);
    void PWMT_habilitarPino(bool enable);
    bool PWMT_estaParado(); //Checa se o TimerB está parado

//Timer T1
    void setUpTA(uint16_t ms);
    bool TA_flagUp();

//ADC timer (T0)
    void setupADCTimer();
#endif
