#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>

#include "mapa.h"

int vizinhanca (MAP *map,int x,int y,int n) {

	int i,j,count=0;

	for (i=-n;i<=n;i++) {

		if (x-i <= 0 && x-i >= 499) {continue;}

		for (j=-n;j<=n;j++) {

			if (y-j <= 0 && y-j >= 499) {continue;}

			if (map->cord[x-i][y-j] == '#') count++;

		}

	}

return count;

}

void spawnporta (MAP *map,POS max) {

    int randomx = rand() % max.x;
	int randomy = rand() % max.y;

	if (vizinhanca(map,randomx,randomy,4) < 5) {
		map->cord[randomx][randomy] = 'D';
	} else spawnporta(map,max);

}

void gerar(STATE *s,MAP *map,POS max) {
	int randomx = rand() % max.x;
	int randomy = rand() % max.y;

	if (vizinhanca(map,randomx,randomy,3) < 5) {
		s->playerX = randomx;
		s->playerY = randomy;
	} else gerar(s,map,max);
}

int vizinhanca2 (MAP *map,int x,int y,int n) {

	int j,count=0;

		for (j=-n;j<=n;j++) {

			if (y-j <= 0 && y-j >= 499) {continue;}

			if (map->cord[x][y-j] == '#') count++;

		}

return count;

}

void gerarMapa (MAP *map,POS max) {

	int i,j;


	for (i=1;i<max.x;i++) {

		for (j=1;j<max.y;j++) {

				int random = rand() % 100; //0-9

				if (random <= 48) {map->cord[i][j] = '#';} 
				else {map->cord[i][j] = '.';}
				

		}


	}

}

void ajustarMapa (MAP *map,POS max) {

	int i,j;

	MAP clone;
	clone = *map;


	for (i=1;i<max.x;i++) {

		for (j=1;j<max.y;j++) {

			if (vizinhanca(&clone,i,j,1) >= 5 || vizinhanca(&clone,i,j,2) <= 2) {

				clone.cord[i][j] = '#';

			} else {

				clone.cord[i][j] = '.';

			}

		}

	}

	*map = clone;

}

void ajustarMapa2 (MAP *map,POS max) {

	int i,j;

	MAP clone;
	clone = *map;


	for (i=1;i<max.x;i++) {

		for (j=1;j<max.y;j++) {

			if (vizinhanca(&clone,i,j,1) < 5) {

				clone.cord[i][j] = '.';

			}

		}

	}

	*map = clone;

}

void ajustarMapa3 (MAP *map,POS max) {

	int i,j;

	MAP clone;
	clone = *map;


	for (i=1;i<max.x;i++) {

		for (j=1;j<max.y;j++) {

			if (vizinhanca(&clone,i,j,1) < 4) {

				clone.cord[i][j] = '.';

			}

		}

	}

	*map = clone;

}

void ajustarMapa4 (MAP *map,POS max) {

	int i,j;

	MAP clone;
	clone = *map;


	for (i=1;i<max.x;i++) {

		for (j=1;j<max.y;j++) {

			if (vizinhanca2(&clone,i,j,7) == 3) {

				clone.cord[i][j] = '.';

			}

		}

	}

	*map = clone;

}

void fronteiras (MAP *map,POS max) {

	int i,j;


	for (i=0;i<max.x;i++) {

		for (j=0;j<max.y;j++) {

			if (i==0 || i==max.x-2 || j==0 || j==max.y-1) {map->cord[i][j] = '#';}
			map->seen[i][j] = 0;
			map->distance[i][j] = 0;
		}

	}

	for (i=0;i<50;i++) {

		map->mobs[i].nome = '\0';
		map->mobs[i].vida = 0;
		map->mobs[i].dano = 0;
		map->mobs[i].posx = 0;
		map->mobs[i].posy = 0;

	}


}

void radius (MAP *map, STATE *st,int radius) {

	double i; int j,x,y;
	for (i=0;i<6.28;i+=0.05) {

		for (j=1;j<radius;j++) {

			x = round(sin(i)*j);
			y = round(cos(i)*j);

			if (x==radius) {x=radius - 1;}
			if (x==-radius) {x=-radius + 1;}

			map->seen[st->playerX + x][st->playerY + y] = 2;

			if (map->cord[st->playerX + x][st->playerY + y] == '#') {

				break;

			}

		}
	}

}

void radius2 (MAP *map, STATE *st,int radius) {

	double i; int j,x,y;
	
	for (i=0;i<6.28;i+=0.05) {

		for (j=radius;j<radius+2;j++) {

			x = round(sin(i)*j);
			y = round(cos(i)*j);

			if (map->seen[st->playerX + x][st->playerY + y] == 2) {

				map->seen[st->playerX + x][st->playerY + y] = 1;

			}

			if (map->cord[st->playerX + x][st->playerY + y] == '#') {

				break;

			}

		}
	}

}

void radiusdistance (MAP *map, STATE *st,int radius) {

	double i; int j,x,y;
	
	for (i=0;i<6.28;i+=0.05) {

		for (j=1;j<radius + 4;j++) {

			x = round(sin(i)*j);
			y = round(cos(i)*j);

			if (j < radius) {

			 

			if (map->cord[st->playerX + x][st->playerY + y] == '#') {

				break;

			}

			map->distance[st->playerX + x][st->playerY + y] = sqrt(x*x + y*y);
			}
			else {

				map->distance[st->playerX + x][st->playerY + y] = 0;

			}
		}
	}

}


void gerarSpawn(MOBS *s, MAP *map, POS max) {
    int randomx = rand() % max.x;
    int randomy = rand() % max.y;

    if (vizinhanca(map,randomx,randomy,3) < 5) {
        s->posx = randomx;
        s->posy = randomy;
    } else gerarSpawn(s,map,max);
}

void gerarMobs (MAP *map, POS max, STATE* st) {
    int i, numMobs, nivel, tipomob;
    MOBS mob;

    nivel = st->floor;

    MOBS tiposMobs[4] = {
        {'c', 10, 2,0,0},
        {'S', 20, 5,0,0},
        {'B', 30, 8,0,0},
		{'P', 50, 15,0,0},
    };
    
    if (nivel % 4 == 0) {
		mob.nome = tiposMobs[3].nome;
		mob.dano = tiposMobs[3].dano + nivel * 3;
		mob.vida = tiposMobs[3].vida + nivel * 3;

		gerarSpawn(&mob, map, max);
		map->mobs[0] = mob;
	} 
 
    else 
	{
        numMobs = nivel+2;
        
        for (i=0; i<numMobs; i++) {
            tipomob = rand() % (nivel / 5 + 1);

            mob.nome = tiposMobs[tipomob].nome;
            mob.dano = tiposMobs[tipomob].dano + nivel * 3;
            mob.vida = tiposMobs[tipomob].vida + nivel * 3;
			
            map->mobs[i] = mob;
            gerarSpawn(&mob,map,max);
        }
    }
}

void atualizarPos (STATE *st,MOBS *mob, MAP *map) {
    int direcao, direcaoX, direcaoY,novox, novoy;
    
    if (map->distance[mob->posx][mob->posy] <= 20) {
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
                if (map->cord[novox][novoy+1] != '#') {
                    mob->posy++;
                } break;
            case 1://baixo
                if (map->cord[novox][novoy-1] != '#') {
                    mob->posy--;
                } break;
            case 2: //direita
                if (map->cord[novox+1][novoy] != '#') {
                    mob->posx++;
                } break;
            case 3: //esquerda
                if (map->cord[novox-1][novoy] != '#') {
                    mob->posx--;
                } break;
        }
    }
}