
#include <stdio.h>
#include <stdlib.h>

struct Block
{
    int id;
};

struct Map
{
    int width;
    int height;
    struct Block** blocks;
};


void diamond(int**, int, int, int, int, int, float);
void square(int**, int, int, int, float);
void square_without_salt(int**, int, int, int);
