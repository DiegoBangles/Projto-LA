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


}
