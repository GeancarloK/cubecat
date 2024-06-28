#ifndef STRUCTS.H
#define STRUCTS.H
#include "raylib.h"

typedef enum {empty = 0, empty_static, wall, photo, scratch, Blocks_size} Blocks;
typedef enum {photo_enemy, Enemies_size} Enemies;
typedef struct blocos Blocos;
struct blocos
{
    Rectangle coll;
    Blocks tipo;
    Blocos *pai;
    Blocos *prox;
};

/*typedef struct inimigos Inimigos;
struct inimigos
{
    Rectangle coll;
    Enemies tipo;
    Inimigos *prox;
};*/

typedef struct {
    Blocks map[mapa_tam_y][mapa_tam_x];
    char *text;
    Blocos *list_walls;
    //Inimigos *list_enemies;
    Texture2D Images[Blocks_size];
    int Numero;
} Map;


typedef enum {left_side = -1, none_side = 0, right_side = 1} side;

typedef struct
{
    /*Circle coll;*/
    Vector2 center;
    float radius;
    Vector2 veloc;
    bool on_hand;
    int side_rotation;
    int rotation;
    Color color;
    Texture2D texture;
} Arrow;

typedef struct
{
    Rectangle coll;
    Vector2 accel;
    Vector2 veloc;
    bool grounded;
    bool dashable;
    bool preparing_dash;
    int dash_wait;
    Arrow *arrow;
    side running;
    side running_last;
    int turning;
    Texture2D Image;
    Texture2D Image_dash;
} Cat;

#endif // STRUCTS
