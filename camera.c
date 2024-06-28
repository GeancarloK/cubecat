#include "camera.h"

void Update_camera(Camera2D *camera, Cat gato)
{
    camera->target = (Vector2)
    {
        floor(Center_cat(gato).x), floor(Center_cat(gato).y)
    };
}
void Setup_camera(Camera2D *camera, Cat gato)
{
    Update_camera(&camera, gato);
    camera->offset = (Vector2)
    {
        screenHeight/2,  screenWidth/2
    };
    camera->rotation = 0;
    camera->zoom = 1;
}
Vector2 Origin_camera(Camera2D camera)
{
    return (Vector2)
    {
        camera.target.x-camera.offset.x/camera.zoom, camera.target.y-camera.offset.y/camera.zoom
    };
}
