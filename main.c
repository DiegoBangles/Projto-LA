#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"
#include "mapa.h"
#include "changer.h"
#include "combat.h"




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
		case 'e': atacar(st,map,1); break;
		case 'w': atacardir(1,map,st); break;
		case 'p': st->light++; break;
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
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);

	

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
	gerarMobs(&map,max,&st);

	st.light = 5;
	st.health = 10;
	st.maxhealth = 10;
	st.damage = 2;
	st.radius = 3;
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
				if (map.seen[i][j] == 3) {

					attroff(COLOR_PAIR(COLOR_WHITE));
					attron(COLOR_PAIR(COLOR_CYAN));
					mvaddch(i, j, map.cord[i][j] | A_BOLD);
					attroff(COLOR_PAIR(COLOR_CYAN));
					attron(COLOR_PAIR(COLOR_WHITE));
					map.seen[i][j] = 2;
				}
				if (map.seen[i][j] == 4) {

					attroff(COLOR_PAIR(COLOR_WHITE));
					attron(COLOR_PAIR(COLOR_RED));
					mvaddch(i, j, map.cord[i][j] | A_BOLD);
					attroff(COLOR_PAIR(COLOR_RED));
					attron(COLOR_PAIR(COLOR_WHITE));
					map.seen[i][j] = 2;
				}

			}

		}

		for (i=1;i<50;i++) {
			int x = map.mobs[i].posx;
			int y = map.mobs[i].posy;
			if (map.seen[x][y] >= 2) {

					attroff(COLOR_PAIR(COLOR_WHITE));
					attron(COLOR_PAIR(COLOR_RED));
					mvaddch(x, y, map.mobs[i].nome | A_BOLD);
					attroff(COLOR_PAIR(COLOR_RED));
					attron(COLOR_PAIR(COLOR_WHITE));

			}

			atualizarPos(&st,&map.mobs[i],&map);

		}

		mvaddch(st.playerX, st.playerY, '@' | A_BOLD);
		//mvaddch(map.mobs[1].posx, map.mobs[1].posy, map.mobs[1].nome | A_BOLD);

		attroff(COLOR_PAIR(COLOR_WHITE));
		move(st.playerX, st.playerY);
		update(&st,&map,max,wnd);
		
	}

	return 0;
}
