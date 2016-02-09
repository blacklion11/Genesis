
#include "genesis.h"










int draw_player(struct Player* player)
{
    attron(COLOR_PAIR(1));
    mvprintw(player->ypos, player->xpos, "%c", player->token);
    attroff(COLOR_PAIR(1));
}
