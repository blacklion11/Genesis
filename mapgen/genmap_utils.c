
#include <stdio.h>
#include <stdlib.h>
#include "genmap.h"


void write_to_file()
{

}


/*
 * This function writes the heightmap out to the specified file
 */
void write_heightmap(char* filename, struct Map* map)
{
    FILE *file = fopen(filename, "w");
    
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

    map->blocks = (struct Block***) malloc(sizeof(struct Block**));


    for(int i = 0; i < height; i++)
    {
        map->blocks[i] = (struct Block**) malloc(sizeof(struct Block*));
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

