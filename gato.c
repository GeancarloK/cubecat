#define mapa_tam_x 80
#define mapa_tam_y 80

#include<stdio.h>
#include<stdlib.h>
#ifndef GATO.H
#define GATO.H

#include "raylib.h"
#include "mapa.h"
#include "structs.h"
#include "cursor.h"
#include "camera.h"
#define screenHeight GetScreenWidth()
#define screenWidth GetScreenHeight()
#define gravity 60
#define acceleration 6
#define max_vel_x 60
#define max_vel_y 60
#define jump -30
#define start_vel 12
#define size_cube 40
#define dash 30
#define SlowMotion 2
#define ROTATION_DASH 10


Cat Setup_cat()
{
    return (Cat)
    {
coll:
        (Rectangle) {50,50,size_cube,size_cube},
accel:
        (Vector2) {0,0},
veloc:
        (Vector2) {5,0},
grounded:
        false,
dashable:
        true,
preparing_dash:
        false,
dash_wait:
        0,
arrow:
        Setup_arrow() /*(Arrow){(Circle){0,0}, (Vector2){0,0}, (Vector2) {0, acceleration}, true, LoadTexture("./textures/arrow/arrow.png")}*/,
running:
        none_side,
running_last:
        right_side,
Image:
        LoadTexture("./textures/cat_frajola/cat_right_1.png"),
Image_dash:
        LoadTexture("./textures/cat_frajola/cat_right_dash.png")
    };
}

void DrawCat(Cat *gato)
{
    if(!gato->dashable)
    {
        //Girando no dash
        DrawTexturePro(gato->Image_dash, (Rectangle){0, 0, gato->running_last * gato->Image_dash.width, gato->Image_dash.height}, (Rectangle){floor(gato->coll.x) + gato->Image_dash.width/2,floor(gato->coll.y) + gato->Image_dash.height/2,gato->Image_dash.width, gato->Image_dash.height}, (Vector2){gato->Image_dash.width/2, gato->Image_dash.height/2}, gato->running_last*gato->turning, WHITE);
        gato->turning += ROTATION_DASH;
    }
    else
    {
        //Gato normal
        DrawTexturePro(gato->Image, (Rectangle){0, 0, gato->running_last * gato->Image.width, gato->Image.height}, (Rectangle){floor(gato->coll.x), floor(gato->coll.y)+1, gato->Image.width, gato->Image.height}, (Vector2){0, 0}, 0, WHITE);
        gato->turning = 0;
    }
}

void Gravity_cat(Cat *gato, Map *Mapa)
{

    if(GetFPS() != 0)
    {
        gato->accel.y = (float)gravity/GetFPS();
        if(abs((int)gato->veloc.y) <= max_vel_y)
        {
            //acelera o gato no eixo y
            gato->veloc.y += gato->accel.y/(1+SlowMotion*gato->preparing_dash);
        }
        //move o gato
        gato->coll.y += floor(gato->veloc.y)/(1+SlowMotion*gato->preparing_dash);
        Collision_cat_y_blocks(gato, Mapa);
    }
    else
    {
        //Para não bugar divisao por zero
        gato->accel.y = 0;
        gato->veloc.y = 0;
    }
}
void Collision_cat_y_blocks(Cat *gato, Map *Mapa)
{
    Blocos *B = Mapa->list_walls;
    int volta;
    if(gato->veloc.y > 0) volta = -1;
    else volta = 1;
    while(B != NULL)
    {
        while(CheckCollisionRecs(gato->coll, (Rectangle)
    {
        B->coll.x*size_cube, B->coll.y*size_cube, B->coll.width, B->coll.height
    }))
        {
            gato->coll.y += volta;
            if(volta == -1) gato->grounded = gato->dashable = true;
            if(!CheckCollisionRecs(gato->coll, (Rectangle)
        {
            B->coll.x*size_cube, B->coll.y*size_cube, B->coll.width, B->coll.height
        }))
            {
                //Colidiu em cima ou em baixo
                //gato->accel.y = 0;
                gato->veloc.y = 0;
                //if(volta == 1) gato->grounded = true;
                return;
            }
        }
        B = B->prox;
    }
    gato->grounded = false;
    return;
}

void Collision_cat_x_blocks(Cat *gato, Map *Mapa)
{
    Blocos *B = Mapa->list_walls;
    int volta;
    if(gato->veloc.x > 0) volta = -1;
    else volta = 1;
    while(B != NULL)
    {
        while(CheckCollisionRecs(gato->coll, (Rectangle)
    {
        B->coll.x*size_cube, B->coll.y*size_cube, B->coll.width, B->coll.height
    }))
        {
            gato->coll.x += volta;
            if(!CheckCollisionRecs(gato->coll, (Rectangle)
        {
            B->coll.x*size_cube, B->coll.y*size_cube, B->coll.width, B->coll.height
        }))
            {
                gato->accel.x = 0;
                gato->veloc.x = 0;
                return;
            }
        }
        B = B->prox;
    }
    return;
}

void Acceleration_cat(Cat *gato)
{
    if(GetFPS() != 0) gato->accel.x = (float)acceleration*gato->running/(GetFPS()*(1+SlowMotion*gato->preparing_dash));
}

void Jump_cat(Cat *gato)
{
    if(gato->grounded && IsKeyPressed(KEY_SPACE))
    {
        gato->veloc.y = jump;
        gato->grounded = false;
    }
    if(!gato->grounded && IsKeyReleased(KEY_SPACE) && gato->veloc.y < 0)
    {
        gato->veloc.y /= 2;
    }
}

Vector2 Center_cat(Cat gato)
{
    return (Vector2)
    {
        gato.coll.x+(gato.coll.width)/2, gato.coll.y+(gato.coll.height)/2
    };
}

void Loop_cat(Cat *gato)
{
    //Loop Mapa do Gato
    if(gato->coll.x > mapa_tam_x * size_cube || gato->coll.x < 0)
    {
        gato->coll.x += mapa_tam_x * size_cube;
        gato->coll.x = (int)gato->coll.x %(mapa_tam_x * size_cube);

    }
    if(gato->coll.y > mapa_tam_y * size_cube || gato->coll.y < 0)
    {
        gato->coll.y += mapa_tam_y * size_cube;
        gato->coll.y = (int)gato->coll.y % (mapa_tam_y * size_cube);
    }
}

Color Color_Dash(bool preparing_dash, int *dash_wait)
{

    if(preparing_dash)
    {
        return (Color){255-*dash_wait, 255-*dash_wait, 255-*dash_wait, 255};
    }
    return WHITE;
}

void Dash_cat(Cat *gato, Map *Mapa, Camera2D camera)
{
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && gato->dashable)
    {
        if(gato->dash_wait == 0)
        {
            gato->dash_wait = 127;
        }
        gato->preparing_dash = true;
        gato->dash_wait += 1;
        if(gato->dash_wait>255) gato->dash_wait = 255;
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && gato->preparing_dash)
    {
        gato->dashable = gato->preparing_dash = false;
        gato->dash_wait = 0;
        gato->veloc.x = dash * (GetCursor(camera).x - Center_cat(*gato).x) / DistanceCatCursor(*gato, camera);
        gato->veloc.y = dash * (GetCursor(camera).y - Center_cat(*gato).y) / DistanceCatCursor(*gato, camera);

    }
}

void Directions_cat(Cat *gato, Map *Mapa, Camera2D camera)
{
    //Velocidade limite gato
    if(abs((int)gato->veloc.x) <= max_vel_x)
    {
        gato->veloc.x += gato->accel.x/(1+SlowMotion*gato->preparing_dash);
    }

    if(0 < gato->veloc.x && gato->veloc.x < start_vel && gato->dashable) gato->veloc.x = start_vel;
    else if(0 > gato->veloc.x && gato->veloc.x > -start_vel && gato->dashable) gato->veloc.x = -start_vel;
    gato->coll.x += gato->veloc.x/(1+SlowMotion*gato->preparing_dash);
    Collision_cat_x_blocks(gato, Mapa);
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
    {
        //Stopped
        gato->accel.x = 0;
        gato->running = none_side;
        gato->running_last = 2*(Center_cat(*gato).x <= GetCursor(camera).x)-1;
        if(gato->dashable)
        {
            gato->veloc.x = 0;
        }
    }
    else
    {

        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_D))
        {
            //Left
            if(gato->running != left_side)
            {
                gato->veloc.x = -start_vel;
            }
            gato->running = left_side;
            gato->running_last = left_side;
            Acceleration_cat(gato);
        }
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_A))
        {
            //Right
            if(gato->running != right_side)
            {
                gato->veloc.x = start_vel;
            }
            gato->running = right_side;
            gato->running_last = right_side;
            Acceleration_cat(gato);
        }
    }
}

#endif
