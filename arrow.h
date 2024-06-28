#ifndef ARROW.H
#define ARROW.H
#include "raylib.h"
#include "gato.h"

Color Color_arrow();

void Move_arrow(Cat *gato, Camera2D camera, Map Mapa);

Arrow Setup_arrow();

void DrawArrowsAround(Cat gato);

void DrawArrow(Cat gato, int loc_x, int loc_y);

void Collision_arrow_blocks(Cat *gato, Map *Mapa);

#endif

