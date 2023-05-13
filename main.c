#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"
#include "mapa.h"
#include "changer.h"




void do_movement_action(STATE *st, int dx, int dy,MAP *map,POS max,WINDOW *wnd) {
	if (map->cord[st->playerX + dx][st->playerY + dy] != '#') {
		st->playerX += dx;
		st->playerY += dy;
	}
	if (map->cord[st->playerX][st->playerY] == 'D') {
		change_level(map,st,max,wnd);
		st->floor++;
	}
}

void update(STATE *st,MAP *map,POS max,WINDOW *wnd) {
	int key = getch();

	mvaddch(st->playerX, st->playerY, ' ');
	switch(key) {
		case KEY_A1:
		case '7': do_movement_action(st, -1, -1,map,max,wnd); break;
		case KEY_UP:
		case '8': do_movement_action(st, -1, +0,map,max,wnd); break;
		case KEY_A3:
		case '9': do_movement_action(st, -1, +1,map,max,wnd); break;
		case KEY_LEFT:
		case '4': do_movement_action(st, +0, -1,map,max,wnd); break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6': do_movement_action(st, +0, +1,map,max,wnd); break;
		case KEY_C1:
		case '1': do_movement_action(st, +1, -1,map,max,wnd); break;
		case KEY_DOWN:
		case '2': do_movement_action(st, +1, +0,map,max,wnd); break;
		case KEY_C3:
		case '3': do_movement_action(st, +1, +1,map,max,wnd); break;
		case 'p': st->light++; break;
		case 'z': change_level(map,st,max,wnd); break;
		case 'q': endwin(); exit(0); break;
	}
}

int main() {
	STATE st;
	WINDOW *wnd = initscr();
	MAP map;
	POS max;
	int ncols, nrows,i,j;
	getmaxyx(wnd,nrows,ncols);

	max.x = nrows;
	max.y = ncols;

	srand(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

	

	gerarMapa(&map,max);
	fronteiras(&map,max);
	ajustarMapa3(&map,max);
	ajustarMapa(&map,max);
	ajustarMapa(&map,max);
	ajustarMapa(&map,max);
	ajustarMapa2(&map,max);
	ajustarMapa2(&map,max);
	ajustarMapa4(&map,max);
	fronteiras(&map,max);
	
	gerar(&st,&map,max);
	spawnporta(&map,max);

	st.light = 5;
	st.health = 10;
	st.maxhealth = 10;
	st.damage = 2;
	st.floor = 1;

	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d HP: %d/%d Light: %d Dmg: %d Floor: %d", st.playerX, st.playerY, ncols, nrows, st.health,st.maxhealth,st.light,st.damage,st.floor);
		attroff(COLOR_PAIR(COLOR_BLUE));
		attron(COLOR_PAIR(COLOR_WHITE));
		radius(&map,&st,st.light);
		radius2(&map,&st,st.light);
		radiusdistance(&map,&st,20);

		for (i=0;i<nrows-1;i++) {

			for (j=0;j<ncols;j++) {
				if (map.seen[i][j] == 1) {
					mvaddch(i, j, map.cord[i][j] | A_BOLD);
				} 
				if (map.seen[i][j] == 2) {

					attroff(COLOR_PAIR(COLOR_WHITE));
					attron(COLOR_PAIR(COLOR_YELLOW));
					mvaddch(i, j, map.cord[i][j] | A_BOLD);
					attroff(COLOR_PAIR(COLOR_YELLOW));
					attron(COLOR_PAIR(COLOR_WHITE));
				}

			}

		}
		mvaddch(st.playerX, st.playerY, '@' | A_BOLD);

		attroff(COLOR_PAIR(COLOR_WHITE));
		move(st.playerX, st.playerY);
		update(&st,&map,max,wnd);
	}

	return 0;
}
