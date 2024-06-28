#include <stdio.h>
#include "raylib.h"
#include "camera.h"
#include "gato.h"
#include "mapa.h"
#include "cursor.h"
#include "arrow.h"
#define screenHeight GetScreenWidth()
#define screenWidth GetScreenHeight()
#define FPS 60

int main()
{

    //START: SETUP


    InitWindow(screenWidth, screenHeight, "CubeCat");
    SetTargetFPS(FPS);
    //ToggleFullscreen();
    Camera2D camera = {0};
    Cat gato = Setup_cat();
    Texture2D Cursor;
    Setup_cursor(&Cursor);
    Setup_camera(&camera, gato);
    Map Mapa;
    StartFirstMap(&Mapa, &gato);
    //END: SETUP

    while(!WindowShouldClose())
    {
        //START: PROGRAMMING

        Gravity_cat(&gato, &Mapa);
        Jump_cat(&gato);
        Dash_cat(&gato, &Mapa, camera);
        Directions_cat(&gato, &Mapa, camera);
        Loop_cat(&gato);
        Move_arrow(&gato, camera, Mapa);
        Update_camera(&camera, gato);

        //END: PROGRAMMING

        //START: DESENHOS

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(RAYWHITE);
        {
            DrawBackground(gato, Mapa, camera, &gato.dash_wait);
            DrawMapsAround(Mapa, gato.preparing_dash, &gato.dash_wait);
            //DrawTextureEx(gato.Image, (Vector2){floor(gato.coll.x), floor(gato.coll.y)}, 0, 1, WHITE);
            DrawCat(&gato);
            DrawText("Vidas: 9", Origin_camera(camera).x+5, Origin_camera(camera).y+5, 40, BLACK);
            //DrawLineV(Center_cat(gato), GetCursor(camera), Color_Dash(gato.preparing_dash, &gato.dash_wait));
            DrawArrowsAround(gato);
            DrawTextureV(Cursor, (Vector2){GetCursor(camera).x - Cursor.width/2, GetCursor(camera).y - Cursor.height/2}, WHITE);
            //ShowCollisions(Mapa);
        }
        EndMode2D();
        EndDrawing();

        //END: DESENHOS

    }
    while(true)
    {
        Blocos *B = Mapa.list_walls;
        if(Mapa.list_walls != NULL)
        {
            Mapa.list_walls = Mapa.list_walls->prox;
            free(B);
        }
        else break;
    }
    /*while(true)
    {
        Blocos *B = Mapa.list_enemies;
        if(Mapa.list_enemies != NULL)
        {
            Mapa.list_enemies = Mapa.list_enemies->prox;
            free(B);
        }
        else break;
    }*/
    free(gato.arrow);
    return 0;
}
