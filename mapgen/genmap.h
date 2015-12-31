
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>

struct Block
{
    int     id;
    int     elevation;
};

struct Map
{
    int     width;
    int     height;
    struct  Block*** blocks;
};


/*
 * Terrain Generation functions
 */
void    diamond(int**, int, int, int, int, int, float);
void    square(int**, int, int, int, float);
void    square_without_salt(int**, int, int, int);

/*
 * Util functions
 */
int     average( int, ... );
bool    should_add();
void    write_heightmap(char *, struct Map*);
void    clip_heightmap(int**, int, int, int, int);
struct  Map* malloc_map(int, int);
