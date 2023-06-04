
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapa.h"
#include "state.h"
#include "changer.h"
#include "combat.h"

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
                            mobDeath(&map->mobs[k],map,st);
                        }

                    }
                }
        }
    }
    
}
void mobatacar(STATE* st,MAP *map, MOBS *mob, int raio,WINDOW *wnd) {
    int i, j, playerx, playery;
    int mobx = mob->posx;
    int moby = mob->posy;
    for (i = -raio; i <= raio; i++) {
        if (mobx + i < 0 || mobx + i >= 500) {
            continue;}
        for (j = -raio; j <= raio; j++) {
            if (moby + j < 0 || moby + j >= 500) {
                continue;}
                map->seen[mobx+i][moby+j] = 4;
            playerx = st->playerX;
            playery = st->playerY;
            if (playerx == mobx + i && playery == moby + j) {
                st->health -= mob->dano;
                    if (st->health <= 0) {

                        player_death(st,wnd);

                    }
            }
        }
    }
}

/*void mobatacar2(STATE* st,MAP *map, MOBS *mob, WINDOW *wnd) {

    int i, j,raio = mob->raio;
    int mobx = mob->posx;
    int moby = mob->posy;

    for (i = -raio; i <= raio; i++) {
        for (j = -raio; j <= raio; j++) {

            map->seen[mobx+i][moby+j] = 4;

            if (st->playerX == mobx + i && st->playerY == moby + j) {
                st->health -= mob->dano;

                    if (st->health <= 0) {

                        player_death(st,wnd);

                    }

            }
        }
    }
}*/

void mobatacardir(int dir,int radius, MAP* map, STATE* st,MOBS* mob,WINDOW *wnd) {
    int i;
    int dx = 0, dy = 0;

    
    if (dir == 1) { //cima
        dx = -1;
    } else if (dir == 2) { //esq
        dy = -1;
    } else if (dir == 3) { //dir
        dy = 1;
    } else if (dir == 4) { //baixo
        dx = 1;
    }

    for (i = 0; i <= radius+1; i++) {

        int targetX = mob->posx + (i * dx);
        int targetY = mob->posy + (i * dy);

        map->seen[targetX][targetY] = 4;

        if (targetX == st->playerX && targetY == st->playerY) {

            st->health -= mob->dano;
            if (st->health <= 0) {

                player_death(st,wnd);

            }
        }

    }
}

void atacardir(int dir, MAP* map, STATE* st) {
    int i, k;
    int dx = 0, dy = 0;

    
    if (dir == 1) { //cima
        dx = -1;
    } else if (dir == 2) { //esq
        dy = -1;
    } else if (dir == 3) { //dir
        dy = 1;
    } else if (dir == 4) { //baixo
        dx = 1;
    }

    for (i = 0; i <= st->radius; i++) {

        int targetX = st->playerX + (i * dx);
        int targetY = st->playerY + (i * dy);
        map->seen[targetX][targetY] = 3;
        if (map->cord[targetX][targetY] == '#') break;

        for (k = 1; k < 50; k++) {
            if (targetX == map->mobs[k].posx && targetY == map->mobs[k].posy) {

                map->mobs[k].vida -= st->damage;
                if (map->mobs[k].vida <= 0) {
                    mobDeath(&map->mobs[k],map,st);
                }
            }
        }

    }
}

void bossAttackdir (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd) {
    int i,j;
    int dx = 0, dy = 0;

    


    for (j=1;j<5;j++) {

        if (j == 1) {
            dx = -1;
            dy = 0;
        } else if (j == 2) {
            dy = -1;
            dx=0;
        } else if (j == 3) { 
            dy = 1;
            dx=0;
        } else if (j == 4) {
            dx = 1;
            dy=0;
        }

        for (i = 0; i <= 20; i++) {

            int targetX = mob->posx + (i * dx);
            int targetY = mob->posy + (i * dy);
            map->seen[targetX][targetY] = 4;
            if (map->cord[targetX][targetY] == '#') break;

                if (targetX == st->playerX && targetY == st->playerY) {

                    st->health -= mob->dano;
                    if (st->health <= 0) {

                        player_death(st,wnd);

                    }
                }
            
        }
    }



}

void bossAttackdia (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd) {

    int i,j;
    int dx = 0, dy = 0;

    


    for (j=1;j<5;j++) {

        if (j == 1) {
            dx = -1;
            dy = 1;
        } else if (j == 2) {
            dy = -1;
            dx=1;
        } else if (j == 3) { 
            dy = 1;
            dx=1;
        } else if (j == 4) {
            dx = -1;
            dy=-1;
        }

        for (i = 0; i <= 20; i++) {

            int targetX = mob->posx + (i * dx);
            int targetY = mob->posy + (i * dy);
            map->seen[targetX][targetY] = 4;
            if (map->cord[targetX][targetY] == '#') break;

                if (targetX == st->playerX && targetY == st->playerY) {

                    st->health -= mob->dano;
                    if (st->health <= 0) {

                        player_death(st,wnd);

                    }
                }
            
        }
    }
}

void bossAttackcir (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd) {
    int i, j;
    int mobx = mob->posx;
    int moby = mob->posy;

    for (i = -3; i <= 3; i++) {
        if (mobx + i < 0 || mobx + i >= 500) {
            continue;
        }
        for (j = -3; j <= 3; j++) {
            if (moby + j < 0 || moby + j >= 500) {
                continue;
            }
            map->seen[mobx+i][moby+j] = 4;

            if (st->playerX == mobx + i && st->playerY == moby + j) {
                st->health -= mob->dano;

                    if (st->health <= 0) {

                        player_death(st,wnd);

                    }

            }
        }
    }
}

void mobDeath (MOBS *mob,MAP *map,STATE *st) {

    if (mob->nome == 'C') {
        //mob drop miniboss
    } else if (mob->nome == 'P') {
        bossDrop(mob,map);
    } else {
        //mob drop resto
    }

    mob->nome = '\0';
    mob->vida = 0;
    mob->dano = 0;
    mob->posx = 0;
    mob->posy = 0;

    st->mobskilled++;

}

void bossDrop (MOBS *mob,MAP *map) {

    map->cord[mob->posx][mob->posy] = 'K';

}

/*void mobDrop (MAP *map,MOB *mob,STATE *st) {

    char tipoItem[8] = {'L', 'l', 'g', 'f', 't', 'c', 'm', 'h'};

    int random = rand() % 8;

    map->cord[mob->posx][mob->posy] = tipoItem[random];


}

void mobDropBtr (MAP *map,MOB *mob,STATE *st) {

    char tipoItem[9] = {'L', 'l', 'g', 'f', 't', 'c', 'm', 'h', 'v'};

    int random = rand() % 13;

    map->cord[mob->posx][mob->posy] = tipoItem[random];


}*/