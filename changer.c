#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"
#include "state.h"
#include "changer.h"


void change_level (MAP *map,STATE *st,POS max,WINDOW *wnd) {

	wclear(wnd);

    gerarMapa(map,max);
	fronteiras(map,max);
	ajustarMapa3(map,max);
	ajustarMapa(map,max);
	ajustarMapa(map,max);
	ajustarMapa(map,max);
	ajustarMapa2(map,max);
	ajustarMapa2(map,max);
	ajustarMapa4(map,max);
	fronteiras(map,max);
	
	gerar(st,map,max);
	spawnporta(map,max);
	gerarMobs(map,max,st);
	gerarItem(map,max,st);


}

void change_level_final (MAP *map,STATE *st,POS max,WINDOW *wnd) {

	wclear(wnd);

    gerarMapa(map,max);
	fronteiras(map,max);
	ajustarMapa2(map,max);
	ajustarMapa(map,max);
	ajustarMapa(map,max);
	ajustarMapa3(map,max);
	fronteiras(map,max);
	gerarMobs(map,max,st);
	gerarItem(map,max,st);

	gerar(st,map,max);


}

void player_death (STATE *st,WINDOW *wnd) {

	int floor = st->floor;
	st->floor = -1;

	wclear(wnd);

	printw("You have died at floor %d",floor);

}
