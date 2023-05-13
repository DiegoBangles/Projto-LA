#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"
#include "mapa.h"
#include "mobs.h"


void gerarMobs (MAP *map, POS max, STATE* st) {
    int i, numMobs, randomx, randomy, nivel, tipomob;
    Mobs *mob;

    nivel = st->floor;

    Mobs tiposMobs[3] = {
        cozinheiro = {"c", 10, 2},
        SousChefe = {"S", 20, 5},
        Mobs Chefe = {"C", 30, 8},
    };

    numMobs = rand() % (2+nivel) + 1;
    
    for (i=0; i<numMobs; i++) {

        tipomob = rand() % (nivel / 5 + 1);

        mob->nome = tiposMobs[tipomob].nome;
        mob->dano = tiposMobs[tipomob].dano + nivel * 3;
        mob->vida = tiposMobs[tipomob].vida + nivel * 3;

        randomx = rand() % max.x;
        randomy = rand() % max.y;

        if (vizinhanca(map,randomx,randomy,3) < 5) {
		    mob->posx = randomx;
		    mob->posy = randomy;
	    } else gerar(mob,map,max);
    }
}

void atualizarPos (Mobs *mob, POS max, MAP *map) {
    int direcao, direcaox, direcaoy,novox, novoy;
    
    if (map->distance[mob->posx][mob->posy] <= radius) {
        if (map->distance[mob->posx][mob->posy] > 0) {
            
            direcaoX = st->playerX - mob->posx;
            direcaoY = st->playerY - mob->posy;

            if (abs(direcaoX) > abs(direcaoY)) {
                if (direcaoX > 0 && map->cord[mob->posx+1][mob->posy] != '#') {
                    mob->posx++;
                } else if (direcaoX < 0 && map->cord[mob->posx-1][mob->posy] != '#') {
                    mob->posx--;
                }
            } else {
                if (direcaoY > 0 && map->cord[mob->posx][mob->posy+1] != '#') {
                    mob->posy++;
                } else if (direcaoY < 0 && map->cord[mob->posx][mob->posy-1] != '#') {
                    mob->posy--;
                }
            }
        }
        else
        {
            //atacar player
        }
    }
    else
    {
        direcao = rand() % 4;

        novox = mob->posx;
        novoy = mob->posy;

        switch (direcao) {
            case 0: //cima
                if (map->cord[novox][novoy++] != '#') {
                    mob->posy++;
                }
            case 1://baixo
                if (map->cord[novox][novoy--] != '#') {
                    mob->posy--;
                } 
            case 2: //direita
                if (map->cord[novox++][novoy] != '#') {
                    mob->posx++;
                }
            case 3: //esquerda
                if (map->cord[novox--][novoy] != '#') {
                    mob->posx--;
                }
        }
    }
}