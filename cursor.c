#ifndef CURSOR.H
#define CURSOR.H
#include "raylib.h"
#include "gato.h"

void Setup_cursor(Texture2D *Cursor)
{
    //ddaHideCursor();
    *Cursor = LoadTexture("./textures/mouse/seta.png");
}

Vector2 GetCursor(Camera2D camera)
{
    return (Vector2){GetMouseX() + camera.target.x - camera.offset.x, GetMouseY() + camera.target.y - camera.offset.y};
}

float DistanceCatCursor(Cat gato, Camera2D camera)
{
    return sqrt(pow(Center_cat(gato).x - GetCursor(camera).x,2) + pow(Center_cat(gato).y - GetCursor(camera).y,2));
}


#endif
