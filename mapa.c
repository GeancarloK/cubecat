#ifndef MAPA.H
#define MAPA.H
#define size_map 80
#include"raylib.h"
#include "gato.h"
#include "structs.h"

void CallMap(Map *Mapa, Cat *gato)
{
    char arq[20];
    sprintf(arq, "map%d.txt", Mapa->Numero);
    Mapa->text = LoadFileText(arq);
    UnloadFileText(arq);
    LoadMap(Mapa, gato);

}
void ShowCollisions(Map Mapa)
{
    Blocos *list = Mapa.list_walls;
    while(list != NULL)
    {
        DrawRectangle(list->coll.x*size_cube, list->coll.y*size_cube, size_cube,size_cube, BLACK);
        list = list->prox;
    }
}
/*void ShowCollisionsEnemies(Map Mapa)
{
    Inimigos *list = Mapa.list_enemies;
    while(list != NULL)
    {
        DrawRectangle(list->coll.x*size_cube, list->coll.y*size_cube, size_cube,size_cube, BLACK);
        list = list->prox;
    }
}*/

void StartFirstMap(Map *Mapa, Cat *gato)
{
    //Faz chamada do mapa
    Mapa->Numero = 1;
    Mapa->list_walls = NULL;
    /*Mapa->list_enemies = NULL;*/
    CallMap(Mapa, gato);
    Mapa->Images[empty] = LoadTexture("./textures/walls/Parede_Back4.png");
    Mapa->Images[empty_static] = LoadTexture("./textures/walls/Parede_Back3.png");
    Mapa->Images[wall] = LoadTexture("./textures/walls/Parede.png");
    Mapa->Images[photo] = LoadTexture("./textures/enemies/photo.png");
    Mapa->Images[scratch] = LoadTexture("./textures/walls/Arranhador.png");
}

void DrawMapsAround(Map Mapa, bool preparing_dash, int *dash_wait)
{
    for(int loc_x = -1; loc_x <= 1; loc_x++)
    {
        for(int loc_y = -1; loc_y <= 1; loc_y++)
        {
            DrawMap(Mapa, loc_y, loc_x, preparing_dash, dash_wait);
        }
    }
}

void DrawBackground(Cat gato, Map Mapa, Camera2D camera, int *dash_wait)
{
    //Estático
    for(int i = -1; i <= 2*GetScreenWidth()/Mapa.Images[empty_static].width+10; i++)
    {
        for(int j = -1; j <= 2*GetScreenHeight()/Mapa.Images[empty_static].height+10; j++)
        {
            DrawTexture(Mapa.Images[empty_static], i * Mapa.Images[empty_static].width + camera.target.x - camera.offset.x, j * Mapa.Images[empty_static].height + camera.target.y - camera.offset.y, Color_Dash(gato.preparing_dash, dash_wait));
        }
    }
    //Meia movimentacao
    for(int i = -1; i <= 2*GetScreenWidth()/Mapa.Images[empty].width+10; i++)
    {
        for(int j = -1; j <= 2*GetScreenHeight()/Mapa.Images[empty].height+10; j++)
        {
            DrawTexture(Mapa.Images[empty], i * Mapa.Images[empty].width + camera.target.x - camera.offset.x-gato.coll.x/2, j * Mapa.Images[empty].height + camera.target.y - camera.offset.y-gato.coll.y/2, Color_Dash(gato.preparing_dash, dash_wait));
        }
    }
}

void DrawMap(Map Mapa, int loc_y, int loc_x, bool preparing_dash, int *dash_wait)
{
    for(int j = 0; j < mapa_tam_y; j++)
    {
        for(int i = 0; i < mapa_tam_x; i++)
        {
            if(Mapa.map[j][i] != empty)
            {
                DrawTextureEx(Mapa.Images[Mapa.map[j][i]], (Vector2)
                {
                    i*size_cube + loc_x * size_cube * mapa_tam_x, j*size_cube + loc_y * size_cube * mapa_tam_y
                }, 0, 1, Color_Dash(preparing_dash, dash_wait));
            }

        }
    }
}

Blocks LoadBlock(char mapa, bool *cat_pos, bool *add_wall)
{
    switch (mapa)
    {
    case 'X':
        *add_wall = true;
        return wall;
        break;
    case ' ':
        return empty;
        break;
    case 'G':
        *cat_pos = true;
        return empty;
        break;
    case 'P':
        *add_wall = true;
        return photo;
        break;
    case 'A':
        *add_wall = true;
        return scratch;
        break;
    default:
        return empty;
        break;
    }
}

/*void AddStaticEnemy(Map *Mapa, int x, int y, int type)
{
    Inimigos *lista = Mapa->list_enemies;
    if(lista == NULL)
    {
         Mapa->list_enemies = malloc(sizeof(Inimigos));
        *(Mapa->list_enemies) = (Inimigos)
        {
            (Rectangle) {x, y, size_cube, size_cube}, type, NULL
        };
        lista = Mapa->list_walls;
    }
    else
    {
    while(true)
        {
            if(lista->prox != NULL)
            {
                //Procura ultimo elemento da lista;
                lista = lista->prox;
            }
            else break;
        }
        //Add bloco à lista
        lista->prox = malloc(sizeof(Inimigos));
        *lista->prox = (Inimigos)
        {
            (Rectangle) {x, y, size_cube, size_cube}, type, NULL
        };
    }
    printf("A");
}*/

void AddWall(Map *Mapa, int x, int y)
{
    Blocos *lista = Mapa->list_walls;
    Blocos *pai = NULL;
    if(lista == NULL)
    {
        //Lista vazia de blocos
        Mapa->list_walls = malloc(sizeof(Blocos));
        *(Mapa->list_walls) = (Blocos)
        {
            (Rectangle) {x, y, size_cube, size_cube}, wall, pai, NULL
        };
        pai = Mapa->list_walls;
        lista = Mapa->list_walls;
    }
    else
    {
        while(true)
        {
            if(lista->prox != NULL)
            {
                //Procura ultimo elemento da lista;
                lista = lista->prox;
            }
            else break;
        }
        //Add bloco à lista
        lista->prox = malloc(sizeof(Blocos));
        *lista->prox = (Blocos)
        {
            (Rectangle) {x, y, size_cube, size_cube}, wall, pai, NULL
        };
        pai = lista->prox;
        lista = lista->prox;
    }
    if(x == 0)
    {
        lista->prox = malloc(sizeof(Blocos));
        *lista->prox = (Blocos)
        {
            (Rectangle) {size_map, y, size_cube, size_cube}, wall, pai, NULL
        };
        lista = lista->prox;
    }
    if(y == 0)
    {

        lista->prox = malloc(sizeof(Blocos));
        *lista->prox = (Blocos)
        {
            (Rectangle) {x, size_map, size_cube, size_cube}, wall, pai, NULL
        };
        lista = lista->prox;

    }
    if(x == size_map - 1)
    {
        lista->prox = malloc(sizeof(Blocos));
        *lista->prox = (Blocos)
        {
            (Rectangle) {-1, y, size_cube, size_cube}, wall, pai, NULL
        };
        lista = lista->prox;
    }
    if(y == size_map - 1)
    {
        lista->prox = malloc(sizeof(Blocos));
        *lista->prox = (Blocos)
        {
            (Rectangle) {x, -1, size_cube, size_cube}, wall, pai, NULL
        };
        lista = lista->prox;
    }
}

void LoadMap(Map *Mapa, Cat *gato)
{
    int y = 0;
    int x = 0;
    char *arq = Mapa->text;
    while(*arq != '\0')
    {
        bool cat_pos = false;
        bool add_wall = false;
        //while !feof(mapa)
        if(*arq == '\n')
        {
            //end of line
            y++;
            x = 0;
        }
        else
        {

            Mapa->map[y][x] = LoadBlock(*arq, &cat_pos, &add_wall);
            if(cat_pos)
            {
                //Posicao do gato
                gato->coll.x = x * size_cube;
                gato->coll.y = y * size_cube;
            }
            if(add_wall)
            {
                //Adiciona parede
                AddWall(Mapa, x, y);
            }
            x++;
        }
        *arq++;
    }
}

#endif
