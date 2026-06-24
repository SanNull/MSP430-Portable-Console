#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"
#include "middleware/som.h"
#include "middleware/input.h"
#include <stdint.h>
#include <periferico-gpio/botoes.h>

/*  Averigua se o joystick está bem mapeado para as 4  direções cardinais
    comparando os valores VRX e VRY com seus valores normalizados indicando direções(-1 e 1)
*/
void  JOYSTICK_test();
void joystick_btn_test();

void piezzoTest();
void mapeamentoTest();
