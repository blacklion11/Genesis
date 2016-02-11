
#include "genesis.h"



int world_update(struct World* world)
{
    //update the camera
    camera_update(world->camera);
}

int world_draw(struct World* world)
{
    for(int y = 0; y < world->camera->height; y++)
    {
        for(int x = 0; x < world->camera->width; x++)
        {
            struct Block* block = world->map->blocks[y + world->camera->y][x + world->camera->x];
            attron(COLOR_PAIR(block->color));
            mvprintw(y, x, "%c", block->token);
            attroff(COLOR_PAIR(block->color));
        }
    }
}




