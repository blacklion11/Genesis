
#include "genesis.h"


int draw_shit(struct Game* game)
{

    // draw the world first
    draw_world(game->world); 

    // draw the player last
    draw_player(game->player);

    // draw any windows that may cover the player (e.g. menus)
}


