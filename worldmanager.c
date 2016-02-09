
#include "genesis.h"


int draw_world(struct World* world)
{
    for(int y = 0; y < world->height; y++)
    {
        for(int x = 0; x < world->width; x++)
        {
            mvprintw(y, x, "%c", world->map->blocks[y][x]->token);
        }
    }
}
