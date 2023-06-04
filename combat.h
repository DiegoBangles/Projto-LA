#include "mapa.h"
#include "state.h"



void atacar (STATE *st, MAP *map,int raio);
void mobatacar(STATE* st,MAP *map, MOBS *mob, int raio,WINDOW *wnd);
//void mobatacar2 (STATE *st,MAP *map,MOBS *mob,WINDOW *wnd);
void atacardir (int dir, MAP *map,STATE *st);
void mobatacardir(int dir,int radius, MAP* map, STATE* st,MOBS* mob,WINDOW *wnd);
void bossAttackdir (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd);
void bossAttackdia (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd);
void bossAttackcir (STATE *st,MOBS *mob,MAP *map,WINDOW *wnd);
void mobDeath (MOBS *mob,MAP *map,STATE *st);
void bossDrop (MOBS *mob,MAP *map);