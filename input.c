
#include "genesis.h"

extern struct Game game;


int get_input()
{

    if(getch() == 'q')
    {
        game.running = false;
    }


}


int w_get_input(WINDOW* win)
{



}
