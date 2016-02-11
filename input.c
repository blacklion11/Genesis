
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
            move_player(game, 0);
            break;
        case KEY_DOWN:
            move_player(game, 1);
            break;
        case KEY_LEFT:
            move_player(game, 2);
            break;
        case KEY_RIGHT:
            move_player(game, 3);
            break;
    }
}

int w_get_input(struct Game* game, WINDOW* win)
{



}

int move_player(struct Game* game, short dir)
{
    switch(dir)
    {
        case 0:
            game->player->ypos--;
            if(game->player->ypos < 0)
            {
                game->player->ypos = 0;
                game->world->camera->y--;
            }
            break;
        case 1:
            game->player->ypos++;
            if(game->player->ypos > game->world->camera->height - 1)
            {
                game->player->ypos = game->world->camera->height - 1;
                game->world->camera->y++;
            }
            break;
        case 2:
            game->player->xpos--;
            if(game->player->xpos < 0)
            {
                game->player->xpos = 0;
                game->world->camera->x--;
            }
            break;
        case 3:
            game->player->xpos++;
            if(game->player->xpos > game->world->camera->width - 1)
            {
                game->player->xpos = game->world->camera->width - 1;
                game->world->camera->x++;
            }
            break;
    }
}
