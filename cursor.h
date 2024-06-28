#ifndef CURSOR.H
#define CURSOR.H
#include"raylib.h"

void Setup_cursor(Texture2D *Cursor);

Vector2 GetCursor(Camera2D camera);

float DistanceCatCursor(Cat gato, Camera2D camera);

#endif
