#ifndef ARROW.H
#define ARROW.H
#include "raylib.h"
#include "math.h"
#include "gato.h"
#include "cursor.h"
#define ARROW_VELOC 10
#define ROTATION_ARROW 7

Color Color_arrow()
{
    return (Color)
    {
        GetRandomValue(192, 255) - 128*GetRandomValue(0, 1), GetRandomValue(192, 255) - 128*GetRandomValue(0, 1), GetRandomValue(192, 255) - 128*GetRandomValue(0, 1), 255
    };
}

void Move_arrow(Cat *gato, Camera2D camera, Map Mapa)
{
    if(gato->arrow->on_hand)
    {
        //Flecha na mão
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            gato->arrow->on_hand = !gato->arrow->on_hand;
            gato->arrow->side_rotation = (GetCursor(camera).x >= Center_cat(*gato).x)*2-1;
            gato->arrow->center.x = Center_cat(*gato).x;
            gato->arrow->center.y = Center_cat(*gato).y;
            gato->arrow->veloc.x = ARROW_VELOC * (GetCursor(camera).x - Center_cat(*gato).x) / DistanceCatCursor(*gato, camera);
            gato->arrow->veloc.y = ARROW_VELOC * (GetCursor(camera).y - Center_cat(*gato).y) / DistanceCatCursor(*gato, camera);
            gato->arrow->color = Color_arrow();
        }
    }
    else
    {
        //Flecha no ar
        gato->arrow->rotation += gato->arrow->side_rotation * ROTATION_ARROW;
        gato->arrow->center.x += gato->arrow->veloc.x/(1+SlowMotion*gato->preparing_dash);
        gato->arrow->center.y += gato->arrow->veloc.y/(1+SlowMotion*gato->preparing_dash);
        Collision_arrow_blocks(gato, Mapa);

    }
}

void Collision_arrow_blocks(Cat *gato, Map Mapa)
{
    Blocos *B = Mapa.list_walls;
    while(B != NULL)
    {
        if(CheckCollisionCircleRec(gato->arrow->center, gato->arrow->radius, (Rectangle)
        {
            B->coll.x*size_cube, B->coll.y*size_cube, B->coll.width, B->coll.height
        }))
        {
            gato->arrow->on_hand = 1;
            break;
        }
        else
        {
            B = B->prox;
        }
    }
    return;
}

Arrow *Setup_arrow()
{
    Arrow *A = malloc(sizeof(Arrow));
    *A = (Arrow)
    {
        on_hand: true, texture: LoadTexture("./textures/arrow/arrow2.png")
    };
    A->radius = (A->texture.height +  A->texture.width)*3/16;
    return A;
}

void DrawArrowsAround(Cat gato)
{
    //Arruma posicao da flecha
    if(gato.arrow->center.x >= size_cube * mapa_tam_x || gato.arrow->center.x < 0)
    {
        gato.arrow->center.x = ((int)gato.arrow->center.x + size_cube * mapa_tam_y) % (size_cube * mapa_tam_x);
    }
    if(gato.arrow->center.y >= size_cube * mapa_tam_y || gato.arrow->center.y < 0)
    {
        gato.arrow->center.y = ((int)gato.arrow->center.y + size_cube * mapa_tam_y) % (size_cube * mapa_tam_y);
    }
    //Desenha flecha nos 9 mapas
    for(int loc_x = -1; loc_x <= 1; loc_x++)
    {
        for(int loc_y = -1; loc_y <= 1; loc_y++)
        {
            DrawArrow(gato, loc_x, loc_y);
        }
    }
}

void DrawArrow(Cat gato, int loc_x, int loc_y)
{
    //Desenha flecha daquele mapa
    if(!gato.arrow->on_hand)
    {
        DrawTexturePro(gato.arrow->texture, (Rectangle)
        {
            0, 0, gato.arrow->texture.width, gato.arrow->texture.height
        }, (Rectangle)
        {
            gato.arrow->center.x + loc_x * size_cube * mapa_tam_x, gato.arrow->center.y + loc_y * size_cube * mapa_tam_y, gato.arrow->texture.width, gato.arrow->texture.height
        }, (Vector2)
        {
            gato.arrow->texture.width/2, gato.arrow->texture.height/2
        }, gato.arrow->rotation, gato.arrow->color);
    }
}


#endif

