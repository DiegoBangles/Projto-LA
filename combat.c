
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapa.h"
#include "state.h"

void atacar (STATE *st, MAP *map,int raio){
    int i,j,k,mobx,moby;
    int playerx=(state->playerX),playery=(state->playerY);

    for(i=-raio; i<=raio; i++){
        if (playerx-i <= 0 && playerx-i >= 499){
            continue;
            }
        for(j=-raio; j<=raio; j++){
            if (playery-j <= 0 && playery-j >= 499){
                continue;
                }
                for(k=1; k<50; k++){
                    mobx = map -> mobs[k].posx;
                    moby = map -> mobs[k].posy;

                    if(mobx == i-playerx && moby == j-playery){
                        (map -> mobs[k].vida) -=  (state -> damage);
                    }
                }
        }
    }
    
}

void mobatacar (STATE *st, MAP *map,int raio){
    int i,j,k,playerx,playery;
    int mobx=(map->mob.posx),moby=(map->mob.posy);

    for(i=-raio; i<=raio; i++){
        if (mobx-i <= 0 && mobx-i >= 499){
            continue;
            }
        for(j=-raio; j<=raio; j++){
            if (moby-j <= 0 && moby-j >= 499){
                continue;
                }
                    playerx = state-> playerX;
                    playery = state-> playerY;

                    if(playerx == i-mobx && playery == j-moby){
                        (state-> health) -=  (map-> mob.dano);
                    }
                }
        }
    }
    
