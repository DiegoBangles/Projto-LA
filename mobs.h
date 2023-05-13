#include "mapa.h"
#include "state.h"

typedef struct mobs{
    char nome[20];
    int vida;
    int dano;
    int posx;
    int posy;
} Mobs;

void gerarMobs (MAP *map, POS max, STATE* st);

void atualizarPos (Mobs *mob, POS max, MAP *map);