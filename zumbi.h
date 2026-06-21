#include "entidade.h"
#include <stdbool.h>
#include "constantes.h" 
#ifndef  ZUMBI_H
#define ZUMBI_H

void ZUMBI_perseguirPlayer(entidade *zumbi, entidade *player);
bool ZUMBI_tocouPlayer(entidade *zumbi, entidade *player);

#endif