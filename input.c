
#include "genesis.h"



int get_input(struct Game* game)
{

    if(getch() == 'q')
    {
        game->running = false;
    }


}


int w_get_input(struct Game* game, WINDOW* win)
{



}
