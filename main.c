
#include "genesis.h"
#include <locale.h>

int init_ncurses()
{
    initscr();  //initialize and allocate stdscr
    cbreak();   //allows things like ^C to be used
    noecho();   //don't echo key presses in the terminal
    keypad(stdscr, TRUE);   //allows the use of the function keys and the arrow keys
    curs_set(0);    //hides the cursor
    start_color();  //initializes the 8 basic colors
    init_colors();  // initialize the color pairs we'll be using

    setlocale(LC_ALL, "en_US.IBM437");
    
    return 0;
}

int main(int argc, char** argv)
{
    if(!init_ncurses()) // Will return 0 (false) if completed successfully
    {
        struct Game* game = malloc_game();
        init_game(game);
        run(game);
    }

    return 0;
}
