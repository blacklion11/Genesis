#include "genesis.h"


int init_game(struct Game* game)
{
    // clear out the log file
    FILE *logfile = fopen("log.txt", "w");
    fprintf(logfile, "%c", '\0');
    fclose(logfile);

    // malloc the player
    malloc_player(game);

    // malloc the world
    malloc_world(game);

    //malloc the camera
    malloc_camera(game->world);
    camera_set_size(game->world->camera, screen_width(stdscr), screen_height(stdscr));

    // load the game
    load_game(game);

    // set running to true
    game->running = true;
}

int run(struct Game* game)
{
    while(game->running)
    {
        //get input from the player
        get_input(game);
        
        // update the player
        // update the world
        world_update(game->world);

        // Draw the shit to the screen
        draw_shit(game);

        // update the ncurses window
        refresh();
    }

    endwin();
    return 0;
}
