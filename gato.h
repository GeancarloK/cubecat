#define mapa_tam_x 80
#define mapa_tam_y 80

#include<stdio.h>
#include<stdlib.h>
#ifndef GATO.H
#define GATO.H

#include "raylib.h"
#include "mapa.h"
#include "structs.h"
#define screenHeight GetScreenWidth()
#define screenWidth GetScreenHeight()
#define gravity 30
#define acceleration 6
#define max_vel_x 160
#define max_vel_y 160
#define jump -20
#define start_vel 12
#define size_cube 40
#define dash 30
#define SlowMotion 2

Cat Setup_cat();

void DrawCat(Cat *gato);

void Acceleration_cat(Cat *gato);

void Gravity_cat(Cat *gato, Map *Mapa);

void Collision_cat_y_blocks(Cat *gato, Map *Mapa);

void Jump_cat(Cat *gato);

void Loop_cat(Cat *gato);

Vector2 Center_cat(Cat gato);

Color Color_Dash(bool preparing_dash, int *dash_wait);

void Dash_cat(Cat *gato, Map *Mapa, Camera2D camera);

void Directions_cat(Cat *gato, Map *Mapa, Camera2D camera);

#endif
