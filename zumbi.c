#include "zumbi.h"

void ZUMBI_perseguirPlayer(entidade *zumbi, entidade *player){
    if (zumbi->x == player->x) {
        if(zumbi->y == player->y) {
            return;
        }
    }

    if (zumbi->x > player->x){
        --zumbi->x;
        return;
    }
    else if (zumbi->x < player->x){
        ++zumbi->x;
        return;
    }

    if (zumbi->y > player->y){
        --zumbi->y;
        return;
    }
    else if (zumbi->y < player->y){
        ++zumbi->y;
        return;
    }    

    //TODO fazer  o caminho com base na menor distancia do eixo.

    // uint16_t xDiff = (zumbi->x > player->x) ? zumbi->x - player->x : player->x - zumbi->x;
    // uint16_t yDiff = (zumbi->y > player->y) ? zumbi->y - player->y : player->y - zumbi->y;

}