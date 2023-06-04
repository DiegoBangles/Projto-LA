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
		if (st->floor == 14) {
			st->floor++;
			change_level_final(map,st,max,wnd);
		} else {
			change_level(map,st,max,wnd);
			st->floor++;
		}
	}
	else if (map->cord[st->playerX][st->playerY] == 'K') {
		game_won (st,wnd);
	}
	else if (map->cord[st->playerX][st->playerY] != '.') {
		apanhaItem(st,map,wnd);
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
		case 'a': atacardir(2,map,st); break;
		case 'd': atacardir(3,map,st); break;
		case 's': atacardir(4,map,st); break;
		case 'p': st->light++; break;
		case 'l': st->floor++; break;
		case 'm': wclear(wnd); st->floor=1; break;
		case 'z': change_level(map,st,max,wnd); break;
		case 'x': change_level_final(map,st,max,wnd); break;
		case 'o': player_death(st,wnd); break;
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
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

	

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
	gerarItem(&map,max,&st);


	st.light = 5;
	st.health = 100;
	st.maxhealth = 100;
	st.damage = 2;
	st.radius = 2;
	st.floor = -1;
	st.mobskilled = 0;

	printw("O teu objetivo é derrotar o malvado Chefe Passadini! Mas cuidado, os seus empregados farão desta tarefa muito difícil!! Passa por todas as portas para chegares até ao nível final, onde encontrarás o grande vilão.\n");
	printw("\nPara te moveres, usa o teclado numérico ou as setas. Para te moveres para cima, usa 8. Para te moveres para baixo, usa 2, e assim por adiante. Podes também mover-te na diagonal, sê estratégico!\n");
	printw("\nPara atacar em diferentes direções, usa as teclas (w,a,s,d). Se quiseres podes atacar em todas as direções simultaneamente (e), mas tens menor alcance!\n");
	printw("\nCuidado com as armadilhas (a,A), elas causam dano!\n"); 
	printw("\nComeças com um raio de visão de 5. Para o aumentar, apanha as tochas (L,l).\n");
	printw("Começas com um raio de dano de 2. Para o aumentar, apanha os suplementos de alcance (R,r).\n");
	printw("Começas com dano de 2. Para o aumentar, apanha melhores armas (g,f,t,c). Estas surgem a cada 5 níveis.\n");
	printw("Se levares algum tipo de dano, apanha as curas (m,h).\n");
	printw("A tua vida máxima é 10. Para a aumentar, apanha os suplementos de vida (v). Estes surgem a cada 5 níveis.\n");
	printw("\nComeças no nível 1. O jogo tem 15 níveis.\n");
	printw("\nAperta M para iniciar o jogo.\n");
	printw("Boa Sorte.\n");

	while(1) {

		if (st.floor != -1) {

		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d HP: %d/%d Light: %d Dmg: %d Radius: %d Floor: %d", st.playerX, st.playerY, ncols, nrows, st.health,st.maxhealth,st.light,st.damage,st.radius,st.floor);
		attroff(COLOR_PAIR(COLOR_BLUE));
		radius(&map,&st,st.light);
		radius2(&map,&st,st.light);
		radiusdistance(&map,&st,20);

		for (i=0;i<nrows-1;i++) {

			for (j=0;j<ncols;j++) {
				if (map.seen[i][j] > 0) {
					if (map.cord[i][j] == 'L' || map.cord[i][j] == 'l') {
						attron(COLOR_PAIR(COLOR_YELLOW));
						mvaddch(i, j, map.cord[i][j] | A_BOLD);
						attroff(COLOR_PAIR(COLOR_YELLOW));
					} else if (map.cord[i][j] == 'g' || map.cord[i][j] == 'f'|| map.cord[i][j] == 't'|| map.cord[i][j] == 'c') {
						attron(COLOR_PAIR(COLOR_RED));
						mvaddch(i, j, map.cord[i][j]);
						attroff(COLOR_PAIR(COLOR_RED));
					} else if (map.cord[i][j] == 'm' || map.cord[i][j]== 'h') {
						attron(COLOR_PAIR(COLOR_GREEN));
						mvaddch(i, j, map.cord[i][j] | A_BOLD);
						attroff(COLOR_PAIR(COLOR_GREEN));
					} else if (map.cord[i][j] == 'v') {
						attron(COLOR_PAIR(COLOR_GREEN));
						mvaddch(i, j, map.cord[i][j]);
						attroff(COLOR_PAIR(COLOR_GREEN));
					} else if (map.cord[i][j] == 'A' || map.cord[i][j]== 'a') {
						attron(COLOR_PAIR(COLOR_MAGENTA));
						mvaddch(i, j, map.cord[i][j]);
						attroff(COLOR_PAIR(COLOR_MAGENTA));
					} else if (map.cord[i][j] == 'R' || map.cord[i][j]== 'r') {
						attron(COLOR_PAIR(COLOR_CYAN));
						mvaddch(i, j, map.cord[i][j]);
						attroff(COLOR_PAIR(COLOR_CYAN));
					} else if (map.cord[i][j] == 'D') {
						attron(COLOR_PAIR(COLOR_MAGENTA));
						mvaddch(i, j, map.cord[i][j] | A_BOLD);
						attroff(COLOR_PAIR(COLOR_MAGENTA));
					} else {
						if (map.seen[i][j] == 1) {
							attron(COLOR_PAIR(COLOR_WHITE));
							mvaddch(i, j, map.cord[i][j] | A_BOLD);
							attroff(COLOR_PAIR(COLOR_WHITE));
						} else if (map.seen[i][j] == 2) {
							attron(COLOR_PAIR(COLOR_YELLOW));
							mvaddch(i, j, map.cord[i][j]);
							attroff(COLOR_PAIR(COLOR_YELLOW));
						} else if (map.seen[i][j] == 3) {
							attron(COLOR_PAIR(COLOR_CYAN));
							mvaddch(i, j, map.cord[i][j] | A_BOLD);
							attroff(COLOR_PAIR(COLOR_CYAN));
							map.seen[i][j] = 2;
						} else if (map.seen[i][j] == 4) {
							attron(COLOR_PAIR(COLOR_RED));
							mvaddch(i, j, map.cord[i][j] | A_BOLD);
							attroff(COLOR_PAIR(COLOR_RED));
							map.seen[i][j] = 2;
						}
					}
				}	
			}

		}

		for (i=1;i<50;i++) {

			if (map.mobs[i].nome == '\0') continue;;

			int x = map.mobs[i].posx;
			int y = map.mobs[i].posy;
			if (map.seen[x][y] >= 2) {

				attroff(COLOR_PAIR(COLOR_WHITE));
				attron(COLOR_PAIR(COLOR_RED));
				mvaddch(x, y, map.mobs[i].nome | A_BOLD);
				attroff(COLOR_PAIR(COLOR_RED));
				attron(COLOR_PAIR(COLOR_WHITE));

			}
		
			if (i==49) {
				int random = rand() %10;

				if (random == 0 || random == 1) { //4 directions attack
					bossAttackdir(&st,&map.mobs[49],&map,wnd);
				} else if (random == 2 || random == 3)  { //diagonal
					bossAttackdia(&st,&map.mobs[49],&map,wnd);
				} else if (random == 4 || random == 5)  { //circle
					bossAttackcir(&st,&map.mobs[49],&map,wnd);
				} else if (random == 6)  { //spawn
					bossAttackSpawn(&map.mobs[49],&map);
				} else {} //nothing
			} 
			else {
				atualizarPos(&st,&map.mobs[i],&map,wnd);
			}
			
		}

		mvaddch(st.playerX, st.playerY, '@' | A_BOLD);
		//mvaddch(map.mobs[1].posx, map.mobs[1].posy, map.mobs[1].nome | A_BOLD);

		attroff(COLOR_PAIR(COLOR_WHITE));
		move(st.playerX, st.playerY);}
		update(&st,&map,max,wnd);
		
	}

	return 0;
}
