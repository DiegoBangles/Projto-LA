
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapa.h"
#include "state.h"

void atacar (STATE *st, MAP *map,int raio){
    int i,j,k,mobx,moby;
    int playerx=(st->playerX),playery=(st->playerY);

    for(i=-raio; i<=raio; i++){
        if (playerx-i <= 0 && playerx-i >= 499) {continue;}

        for(j=-raio; j<=raio; j++){
            if (playery-j <= 0 && playery-j >= 499) {continue;}
            map->seen[playerx-i][playery-j] = 3;
                for(k=1; k<50; k++){
                    mobx = map -> mobs[k].posx;
                    moby = map -> mobs[k].posy;

                    if(mobx == i-playerx && moby == j-playery){
                        (map -> mobs[k].vida) -=  (st -> damage);
                    }
                }
        }
    }
    
}

void mobatacar (STATE *st,MOBS mob,int raio){
    int i,j,playerx,playery;
    int mobx=(mob.posx),moby=(mob.posy);

    for(i=-raio; i<=raio; i++){
        if (mobx-i <= 0 && mobx-i >= 499) {continue;}
        for(j=-raio; j<=raio; j++){
            if (moby-j <= 0 && moby-j >= 499) {continue;}
                    playerx = st-> playerX;
                    playery = st-> playerY;

                    if(playerx == i-mobx && playery == j-moby){
                        (st-> health) -=  (mob.dano);
                    }
            }
    }
}

void atacardir (int dir, MAP *map,STATE *st) {

    int i,k;

    if (dir == 1) { //cima

        for (i=0;i<=st->radius;i++) {

            for (k=1;k<50;k++) {

                if (st->playerY+i == map->mobs[k].posy && st->playerX == map->mobs[k].posx) {

                    map->mobs[k].vida -= st->damage;

                }

            }

            map->seen[st->playerX][st->playerY+i] = 3;

        }

    }

}
