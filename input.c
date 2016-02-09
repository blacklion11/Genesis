
#include "genesis.h"



int get_input(struct Game* game)
{

    int key = getch();
    switch(key)
    {
        case 'q':
            game->running = false;
            break;
        case KEY_UP:
            game->player->ypos--;
            break;
        case KEY_DOWN:
            game->player->ypos++;
            break;
        case KEY_LEFT:
            game->player->xpos--;
            break;
        case KEY_RIGHT:
            game->player->xpos++;
            break;
    }
}


int w_get_input(struct Game* game, WINDOW* win)
{



}
