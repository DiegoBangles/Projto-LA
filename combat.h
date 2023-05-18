#include "mapa.h"
#include "state.h"



void atacar (STATE *st, MAP *map,int raio);
void mobatacar (STATE *st,MOBS mob,int raio);
void atacardir (int dir, MAP *map,STATE *st);
void mobatacardir(int dir,int radius, MAP* map, STATE* st,MOBS* mob);