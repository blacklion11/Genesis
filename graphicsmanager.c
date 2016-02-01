
#include "genesis.h"



int draw_player(struct Player* player)
{
    int x,y;
    getmaxyx(stdscr, y, x);
    NDEBUG("Width=%d Height=%d", x, y);
    mvprintw(y/2,x/2,"%c", player->token);
}

int draw_map(struct Map* map)
{
    
}
