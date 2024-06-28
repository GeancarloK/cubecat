#ifndef MAPA.H
#define MAPA.H

#include"raylib.h"
#include "gato.h"
#include "structs.h"

void CallMap(Map *Mapa, Cat *gato);

void ShowCollisions(Map Mapa);

void ShowCollisionsEnemies(Map Mapa);

void StartFirstMap(Map *Mapa, Cat *gato);

void DrawMapsAround(Map Mapa, bool preparing_dash, int *dash_wait);

void DrawBackground(Cat gato, Map Mapa, Camera2D camera, int *dash_wait);

void DrawMap(Map Mapa, int loc_y, int loc_x, bool preparing_dash, int *dash_wait);

Blocks LoadBlock(char mapa, bool *cat_pos, bool *add_wall);

void AddStaticEnemy(Map *Mapa, int x, int y, int type);

void AddWall(Blocos *list_walls, int x, int y);

void LoadMap(Map *Mapa, Cat *gato);

#endif
