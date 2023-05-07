#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

void gerar(STATE *s) {
	s->playerX = 10;
	s->playerY = 10;
}

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

		}

	}


}








