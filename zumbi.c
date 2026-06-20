#include "zumbi.h"

void ZUMBI_perseguirPlayer(entidade *zumbi, entidade *player){
    if (zumbi->x == player->x) {
        if(zumbi->y == player->y) {
            return;
        }
    }

    if (zumbi->x > player->x){
        ENTIDADE_moverX(zumbi, -1);
        return;
    }
    else if (zumbi->x < player->x){
        ENTIDADE_moverX(zumbi, 1);
        return;
    }

    if (zumbi->y > player->y){
        ENTIDADE_moverY(zumbi, -1);
        return;
    }
    else if (zumbi->y < player->y){
        ENTIDADE_moverY(zumbi, 1);
        return;
    }    

    //TODO fazer  o caminho com base na menor distancia do eixo.

    // uint16_t xDiff = (zumbi->x > player->x) ? zumbi->x - player->x : player->x - zumbi->x;
    // uint16_t yDiff = (zumbi->y > player->y) ? zumbi->y - player->y : player->y - zumbi->y;

}

bool ZUMBI_tocouPlayer(entidade *zumbi, entidade *player){
    //Todo adicionar limiares para perdoar mais o jogador
    return  (zumbi->x <= player->x + player->tamanho && zumbi->x + zumbi->tamanho >= player->x) &&
            (zumbi->y <= player->y + player->tamanho && zumbi->y + zumbi->tamanho >= player->y);
}
