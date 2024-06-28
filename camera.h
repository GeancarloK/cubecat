#include "raylib.h"
#include "gato.h"
#define screenHeight GetScreenWidth()
#define screenWidth GetScreenHeight()

void Update_camera(Camera2D *camera, Cat gato);

void Setup_camera(Camera2D *camera, Cat gato);

Vector2 Origin_camera(Camera2D camera);
