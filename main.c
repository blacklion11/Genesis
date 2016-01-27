
#include "genesis.h"


int init_ncurses()
{
    initscr();  //initialize and allocate stdscr
    cbreak();   //allows things like ^C to be used
    noecho();   //don't echo key presses in the terminal
    keypad(stdscr, TRUE);   //allows the use of the function keys and the arrow keys

    return 0;
}

int main(int argc, char** argv)
{
    if(!init_ncurses()) // Will return 0 (false) if completed successfully
    {
        init_game();
        run();
    }

    return 0;
}
