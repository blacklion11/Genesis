
#include "genesis.h"


int camera_update(struct Camera* camera)
{


    //make sure the camera is on the map
    if(camera->x + camera->width > camera->worldwidth)
    {
        camera->x = camera->worldwidth - camera->width;
    }
    if(camera->x < 0)
    {
        camera->x = 0;
    }
    if(camera->y + camera->height > camera->worldheight)
    {
        camera->y = camera->worldheight - camera->height;
    }
    if(camera->y < 0)
    {
        camera->y = 0;
    }
    
    LOG("Camera Position: %d, %d\nCamera Dimensions: %dx%d\nWorld Size: %dx%d\n",camera->x, camera->y, camera->width, camera->height, camera->worldwidth, camera->worldheight);
}



int camera_set_size(struct Camera* camera, int width, int height)
{
    camera->width = width;
    camera->height = height;
}
