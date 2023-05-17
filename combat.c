
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapa.h"
#include "state.h"

void atacar (STATE *st, MAP *map,int raio){
    int i,j,k;
    int playerx=(st->playerX),playery=(st->playerY);

    for(i=-raio; i<=raio; i++){
        if (playerx-i <= 0 && playerx-i >= 499) {continue;}

        for(j=-raio; j<=raio; j++){
            if (playery-j <= 0 && playery-j >= 499) {continue;}
            map->seen[playerx-i][playery-j] = 3;
                for(k=1; k<50; k++){

                    if(map->mobs[k].posx == playerx-i && map->mobs[k].posy == playery-j){
                        (map->mobs[k].vida) -=  (st->damage);

                        if (map->mobs[k].vida <= 0) {

                            map->mobs[k].nome = '\0';
                            map->mobs[k].vida = 0;
                            map->mobs[k].dano = 0;
                            map->mobs[k].posx = 0;
                            map->mobs[k].posy = 0;
                            //FAZER MOB DROPAR ALGUMA COISA
                        }

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

                if (st->playerY == map->mobs[k].posy && st->playerX-i == map->mobs[k].posx) {

                    map->mobs[k].vida -= st->damage;

                    if (map->mobs[k].vida <= 0) {

                        map->mobs[k].nome = '\0';
                        map->mobs[k].vida = 0;
                        map->mobs[k].dano = 0;
                        map->mobs[k].posx = 0;
                        map->mobs[k].posy = 0;
                        //FAZER MOB DROPAR ALGUMA COISA
                    }

                }

            }

            map->seen[st->playerX-i][st->playerY] = 3;

        }

    }
       else if (dir == 2) { //esquerda

        for (i=0;i<=st->radius;i++) {

            for (k=1;k<50;k++) {

                if (st->playerY-i == map->mobs[k].posy && st->playerX == map->mobs[k].posx) {

                    map->mobs[k].vida -= st->damage;

                    if (map->mobs[k].vida <= 0) {

                        map->mobs[k].nome = '\0';
                        map->mobs[k].vida = 0;
                        map->mobs[k].dano = 0;
                        map->mobs[k].posx = 0;
                        map->mobs[k].posy = 0;
                        //FAZER MOB DROPAR ALGUMA COISA
                    }

                }

            }

            map->seen[st->playerX][st->playerY-i] = 3;

        }

    }
       else if (dir == 3) { //direita

        for (i=0;i<=st->radius;i++) {

            for (k=1;k<50;k++) {

                if (st->playerY+i == map->mobs[k].posy && st->playerX == map->mobs[k].posx) {

                    map->mobs[k].vida -= st->damage;


                    if (map->mobs[k].vida <= 0) {

                        map->mobs[k].nome = '\0';
                        map->mobs[k].vida = 0;
                        map->mobs[k].dano = 0;
                        map->mobs[k].posx = 0;
                        map->mobs[k].posy = 0;
                        //FAZER MOB DROPAR ALGUMA COISA
                    }

                }

            }

            map->seen[st->playerX][st->playerY+i] = 3;

        }

    }
       else if (dir == 4) { //baixo

        for (i=0;i<=st->radius;i++) {

            for (k=1;k<50;k++) {

                if (st->playerY == map->mobs[k].posy && st->playerX+i == map->mobs[k].posx) {

                    map->mobs[k].vida -= st->damage;

                    if (map->mobs[k].vida <= 0) {

                        map->mobs[k].nome = '\0';
                        map->mobs[k].vida = 0;
                        map->mobs[k].dano = 0;
                        map->mobs[k].posx = 0;
                        map->mobs[k].posy = 0;
                        //FAZER MOB DROPAR ALGUMA COISA
                    }


                }

            }

            map->seen[st->playerX+i][st->playerY] = 3;

        }

    }


}
