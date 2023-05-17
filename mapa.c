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
			if (map->seen[st->playerX + x][st->playerY + y] <= 2) {
				map->seen[st->playerX + x][st->playerY + y] = 2;
			}

			if (map->cord[st->playerX + x][st->playerY + y] == '#') {

				break;

			}

		}
	}

}

void radius2 (MAP *map, STATE *st,int radius) {

	double i; int j,x,y;
	
	for (i=0;i<6.28;i+=0.05) {

		for (j=radius;j<radius*2;j++) {

			x = round(sin(i)*j);
			y = round(cos(i)*j);

			if (st->playerX + x < 0 || st->playerX + x > 500 || st->playerY + y < 0 || st->playerY + y > 500) {continue;}

			if (map->seen[st->playerX + x][st->playerY + y] == 2) {

				map->seen[st->playerX + x][st->playerY + y] = 1;

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
    int i, j, k, numMobs, nivel, tipomob;
    MOBS mob;

    nivel = st->floor;

    MOBS tiposMobs[5] = {
        {'c', 10, 2,0,0},
        {'S', 20, 5,0,0},
        {'B', 30, 8,0,0},
		{'M', 45, 10,0,0},
		{'P', 50, 15,0,0},
    };
    
    if (nivel % 15 == 0 && nivel>1) {
		numMobs = 2;

		for (j=0; j<numMobs; j++) {

            mob.nome = tiposMobs[4].nome;
			mob.dano = tiposMobs[4].dano + nivel * 3;
			mob.vida = tiposMobs[4].vida + nivel * 3;
			
            map->mobs[j] = mob;
            gerarSpawn(&mob,map,max);
		}
	}
    else 
	{
		if (nivel % 6 == 0) {
			numMobs = nivel/2;

			for (k=0; k<numMobs; k++) {
				
				if (k==1 || k==2) {
					mob.nome = tiposMobs[3].nome;
					mob.dano = tiposMobs[3].dano + nivel * 2;
					mob.vida = tiposMobs[3].vida + nivel * 2;
					
					map->mobs[k] = mob;
					gerarSpawn(&mob,map,max);
				}
				else
				{
					tipomob = rand() % (nivel / 5 + 1);

					mob.nome = tiposMobs[tipomob].nome;
					mob.dano = tiposMobs[tipomob].dano + nivel * 3;
					mob.vida = tiposMobs[tipomob].vida + nivel * 3;
					
					map->mobs[k] = mob;
					gerarSpawn(&mob,map,max);
				}
			}
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
}

void atualizarPos (STATE *st, MOBS *mob, MAP *map) {
    int direcaoX, direcaoY;
    
    if (map->distance[mob->posx][mob->posy] > 0) {
        direcaoX = st->playerX - mob->posx;
        direcaoY = st->playerY - mob->posy;

        if (abs(direcaoX) > abs(direcaoY)) {
            if (direcaoX > 0) {
                if (map->cord[mob->posx+1][mob->posy] != '#') {
					mob->posx++;
				}
				else
				{
					randomPos (mob,map);
				}
            } else if (direcaoX < 0) {
                if (map->cord[mob->posx-1][mob->posy] != '#') {
					mob->posx--;
				}
				else
				{
					randomPos (mob,map);
				}
            }
        } else {
            if (direcaoY > 0) {
                if (map->cord[mob->posx][mob->posy+1] != '#') {
					mob->posy++;
				}
				else
				{
					randomPos (mob,map);
				}
            } else if (direcaoY < 0) {
                if (map->cord[mob->posx][mob->posy-1] != '#') {
					mob->posy--;
				}
				else
				{
					randomPos (mob,map);
				}
            }
        }
    } 
	else 
	{
        randomPos (mob,map);
    }
}

void randomPos (MOBS *mob, MAP *map){
	int direcao;
	char anterior = 's';

	direcao = rand() % 4;

        switch (direcao) {
            case 0: //cima
                if (map->cord[mob->posx][mob->posy+1] != '#') {
                    if (anterior != 'b') {
						mob->posy++;
						anterior = 'c';
					} 
					else
					{
						randomPos (mob, map);	
					} 
				}
				else
				{
					randomPos (mob, map);
				} break;
            case 1://baixo
                if (map->cord[mob->posx][mob->posy-1] != '#') {
                    if (anterior != 'c') {
						mob->posy--;
						anterior = 'b';
					} 
					else
					{
						randomPos (mob, map);	
					}	
				}
				else
				{
					randomPos (mob, map);	
				} break;
            case 2: //direita
                if (map->cord[mob->posx+1][mob->posy] != '#') {
                    if (anterior != 'e') {
						mob->posx++;
						anterior = 'd';
					} 
					else
					{
						randomPos (mob, map);	
					}
				} 
				else
				{
					randomPos (mob, map);	
				} break;
            case 3: //esquerda
                if (map->cord[mob->posx-1][mob->posy] != '#') {
                    if (anterior != 'd') {
						mob->posx--;
						anterior = 'e';
					} 
					else
					{
						randomPos (mob, map);	
					}	
				}
				else
				{
					randomPos (mob, map);	
				} break;
	}
}

void gerarSpawn2(ITENS *s,MAP *map,POS max) {
	int randomx = rand() % max.x;
	int randomy = rand() % max.y;

	if (vizinhanca(map,randomx,randomy,3) < 5) {
		map->cord[randomx][randomy] = s->nome;
	} else gerarSpawn2(s,map,max);
}




void gerarItem(MAP *map, POS max, STATE* st) { 
	int i, tipo, nivel;
	nivel = st->floor;
	
	ITENS tiposTocha[2] = {
		{'T', 10}, //mudem a luminosidade como quiserem
		{'t', 5},
	};
	
	ITENS tiposArma[5] = { 
		{'p', 2}, //mudem o dano como quiserem
		{'f', 3},
		{'F', 5},
		{'m', 7},
		{'s', 10},
	};
	
	ITENS tiposCura[2] = { 
		{'C', 4}, //mudem o aumento de vida como quiserem
		{'c', 2},
	};
	
	ITENS aumentaVida[1] = { 
		{'v', 5}, 
	};
	
	for (i=0; i<nivel; i++) {
		tipo = nivel % 2;
		gerarSpawn2(&tiposTocha[tipo],map,max);
		gerarSpawn2(&tiposCura[tipo],map,max);
		gerarSpawn2(&tiposCura[tipo],map,max);
	}
	
	if (nivel == 1) gerarSpawn2(&tiposArma[0],map,max);
	
	if (nivel % 5 == 0) {
		gerarSpawn2(&aumentaVida[1],map,max);
		for (i=0; i<5; i++) {
			gerarSpawn2(&tiposArma[nivel/5],map,max);
		}
	}
}

void apanhaItem(STATE *st,MAP *map) {
	int i;
	char tipoItem[10] = {'T', 't', 'p', 'f', 'F', 'm', 's', 'C', 'c', 'v'};

	ITENS tiposTocha[2] = {
		{'T', 2}, //mudem a luminosidade como quiserem
		{'t', 1},
	};
	
	ITENS tiposArma[5] = { 
		{'p', 2}, //mudem o dano como quiserem
		{'f', 3},
		{'F', 5},
		{'m', 7},
		{'s', 10},
	};
	
	ITENS tiposCura[2] = { 
		{'C', 4}, //mudem o aumento de vida como quiserem
		{'c', 2},
	};
	
	ITENS aumentaVida[1] = { 
		{'v', 5}, 
	};

	

		for (i=0; i<10; i++) {
			if (map->cord[st->playerX][st->playerY] == tipoItem[i]) {
				if (i==0 || i==1) {if (st->light + tiposTocha[i].funcionalidade > 20) {st->light = 20;} else {st->light += tiposTocha[i].funcionalidade;}}
				if (i==2 || i==3 || i==4 || i==5 || i==6) st->damage += tiposArma[i-2].funcionalidade;
				if (i==7 || i==8) {if (st->health == st->maxhealth) {return;} else if (st->health + tiposCura[i-7].funcionalidade > st->maxhealth) {st->health = st->maxhealth;} else {st->health += tiposCura[i-7].funcionalidade;}}
				if (i==9) st->maxhealth += aumentaVida[i-9].funcionalidade;
				map->cord[st->playerX][st->playerY] = '.';
			}
		}
	
}