#include "input.h"

//Limiares para determinar Direção do joystick
#define DIRECAO_POSITIVO 2000
#define DIREACAO_NEGATIVO -2000

static int8_t getJoystickX();
static int8_t getJoystickY();
static int8_t getDpadX();
static int8_t getDpadY();

int8_t INPUT_getX(){
    int8_t xJoy = getJoystickX();
    int8_t xBtn = BOTOES_getX();
    return  (xJoy != 0) ? xJoy : xBtn;
}

int8_t INPUT_getY() {
    int8_t yJoy = getJoystickY();
    int8_t yBtn = BOTOES_getY();
    return  (yJoy != 0) ? yJoy : yBtn;
}

bool INPUT_getAction(){
    return BOTOES_getAction();
}

int8_t getJoystickX(){
    int16_t x = getVRY();
    //Limiar zero
    if (x > DIREACAO_NEGATIVO && x < DIRECAO_POSITIVO){
        return  0;
    }
    //Verifica se MSB é 1 (numero negativo)
    return (x & 1 << 15) ? -1: 1;
}

int8_t getJoystickY(){
    int16_t y = getVRX();
    //Limiar zero
    if (y > DIREACAO_NEGATIVO && y < DIRECAO_POSITIVO){
        return  0;
    }
    //Verifica se MSB é 1 (numero negativo)
    return (y & 1 << 15) ? 1: -1;
}