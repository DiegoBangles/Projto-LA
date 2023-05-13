#include "state.h"




#ifndef ___MAP_H___
#define ___MAP_H___

typedef struct map{
    char cord[500][500];
    int seen[500][500];
} MAP;

#endif

void gerar(STATE *s,MAP *map,POS max);

void gerarMapa (MAP *map,POS max);
void spawnporta (MAP *map,POS max);
int vizinhanca (MAP *map,int x,int y,int n);
int vizinhanca2 (MAP *map,int x,int y,int n);
void ajustarMapa (MAP *map,POS max);
void ajustarMapa2 (MAP *map,POS max);
void ajustarMapa3 (MAP *map,POS max);
void ajustarMapa4 (MAP *map,POS max);
void fronteiras (MAP *map,POS max);
void radius (MAP *map, STATE *st,int radius);
void radius2 (MAP *map, STATE *st,int radius);
