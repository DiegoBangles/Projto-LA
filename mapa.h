#include "state.h"

void gerar(STATE *s);


#ifndef ___MAP_H___
#define ___MAP_H___

typedef struct map{
    char cord[500][500];
} MAP;

#endif

void gerarMapa (MAP *map,POS max);
int vizinhanca (MAP *map,int x,int y,int n);
int vizinhanca2 (MAP *map,int x,int y,int n);
void ajustarMapa (MAP *map,POS max);
void ajustarMapa2 (MAP *map,POS max);
void ajustarMapa3 (MAP *map,POS max);
void ajustarMapa4 (MAP *map,POS max);
void fronteiras (MAP *map,POS max);
