
#include "genesis.h"


int draw_shit(struct Game* game)
{

    // draw the world first
    world_draw(game->world); 

    // draw the player last
    player_draw(game->player);

    // draw any windows that may cover the player (e.g. menus)
}


