
#include <stdio.h>
#include <stdlib.h>
#include "genmap.h"


/*
 * Average function that takes in any number of arguments but is prefaced with the number 
 * of arguments being averaged
 */
int average( int num, ... )
{
    va_list args;
    int sum = 0;
    /* Initializing arguments to store all values after num */
    va_start(args, num);
    /* Sum all the inputs; We still rely on the function caller to tell us how many there are */
    for(int i = 0; i < num; i++)
    {
        sum += va_arg(args, int);
    }
    va_end(args);

    return sum / num;
}

/*
 * This function returns a boolean value indicating if we should add (true) or subtract (false)
 * We also rely on the function caller having initialized srand() beforehand
 */
bool should_add()
{
    return rand() % 2;
}

/*
 * This function writes the heightmap out to the specified file
 */
void write_heightmap(char* filename, struct Map* map)
{
    FILE *file = fopen(filename, "w");
   
    fprintf(file, "%d\n", map->width);
    fprintf(file, "%d\n", map->height);

    for(int y = 0; y < map->height; y++)
    {
        for(int x = 0; x < map->width; x++)
        {
            fprintf(file, "%d ", map->blocks[y][x]->elevation);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/*
 * This function writes the generated map to the file
 */
void write_map(char* filename, struct Map* map)
{
    FILE *file = fopen(filename, "w");

    fprintf(file, "%d\n", map->width);
    fprintf(file, "%d\n", map->width);

    for(int y = 0; y < map->height; y++)
    {
        for(int x = 0; x < map->width; x++)
        {
            fprintf(file, "%d ", map->blocks[y][x]->id);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/*
 * This function makes sure the heightmap is within a given bounds
 */

void clip_heightmap(int **map, int width, int height, int top, int bottom)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(map[y][x] > top) map[y][x] = top;
            if(map[y][x] < bottom) map[y][x] = bottom;
        }
    }
}

struct Map* malloc_map(int width, int height)
{
    struct Map* map = (struct Map*) malloc(sizeof(struct Map));

    map->blocks = (struct Block***) malloc(sizeof(struct Block**) * width * height);


    for(int i = 0; i < height; i++)
    {
        map->blocks[i] = (struct Block**) malloc(sizeof(struct Block*) * width);
    }

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            map->blocks[y][x] = (struct Block*) malloc(sizeof(struct Block));
        }
    }

    map->width = width;
    map->height = height;

    return map;
}

