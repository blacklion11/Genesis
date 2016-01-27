#include "genesis.h"

bool running;
struct Game game;

int init_game()
{ 
    game.running = true;
}

int run()
{
    while(game.running)
    {
        //get input from the player
        get_input();

    }

    endwin();
    return 0;
}
