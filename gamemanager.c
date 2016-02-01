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
    LOG("World malloc'd\n");
   
    // malloc the map
    malloc_map(game);

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


        //draw the world
        //draw the player
        draw_player(game->player);

        //update the ui (this will include drawing any additional windows)
        

        // update the ncurses window
        refresh();
    }

    endwin();
    return 0;
}
