
#include "genesis.h"



int draw_player(struct Player* player)
{
    int x,y;
    getmaxyx(stdscr, y, x);
    NDEBUG("Width=%d Height=%d", x, y);
    mvprintw(y/2,x/2,"%c", player->token);
}

int draw_world(struct World* world)
{
   for(int y = 0; y < world->height; y++)
   {
       for(int x = 0; x < world->width; x++)
       {
           mvprintw(y,x, "%d", world->map->blocks[y][x]->id);
       }
   }
}
