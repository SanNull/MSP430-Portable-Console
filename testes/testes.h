#include "periferico-gpio/adc.h"
#include "periferico-gpio/lcd.h"
#include "middleware/som.h"
#include "middleware/input.h"
#include <stdint.h>
#include <periferico-gpio/botoes.h>
#include "src/entidade.h"
#include "src/zumbi.h"
#include "periferico-gpio/lcd.h"
#include "src/spritesheet.h"
#include "src/constantes.h"


/*  Associa a saída pwm com a colisão entre o zumbi e o player
*/
void TEST_piezzoTrigger();
/*  Averigua se o joystick está bem mapeado para as 4  direções cardinais
    comparando os valores VRX e VRY com seus valores normalizados indicando direções(-1 e 1)
*/
void TEST_joystick();

/*  Averigua se o dpad está bem mapeado para as 4  direções cardinais, movendo o jogador nas 4 direções
*/

void TEST_dpad();
