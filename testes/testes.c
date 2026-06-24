#include "testes.h"

#define constante 0.03
#define constante8 0.122

void joystick_btn_test(){
    while (1) {
    volatile int8_t btnX = BOTOES_getX();
    volatile int8_t btnY = BOTOES_getY();
   volatile int16_t joyX = getJoystickX();
    volatile int16_t joyY = getJoystickY();

  volatile  int8_t inputX = INPUT_getX();
   volatile int8_t inputY = INPUT_getY();

    volatile int temp;
    temp = 0;
    }

}

void piezzoTest(){
  volatile uint16_t tempo = 0;
  volatile int i = 0;
    TA0CTL = TACLR | TASSEL__ACLK | MC__CONTINOUS;
    SOM_tocarNota(C4, 200);
    while (!(PWMT_estaParado())) {
    }
    tempo = TA0R * constante;
    i = 0;

  ///////////////

    TA0CTL = TACLR | TASSEL__ACLK | MC__CONTINOUS;
    SOM_tocarNota(C4, 1000);
    while (!(PWMT_estaParado())) {
    }
    tempo = TA0R * constante;
    i = 0;

/////

    TA0CTL = TACLR | TASSEL__ACLK | MC__CONTINOUS ;
    SOM_tocarNota(C4, 1700);
    while (!(PWMT_estaParado())) {
    }
    tempo = TA0R * constante;
    i = 0;

}