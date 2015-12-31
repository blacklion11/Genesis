
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include "genmap.h"


void halp(const char *prog)
{
    printf("Usage: %s [-hwf]\n  --help\tDisplay this help screen\n  -h <number>\tSpecify the height (must be a 2^n + 1)\n  -w <number>\tSpecify the width (must be a 2^n + 1)\n  -r <number>\tSpecify the roughness of the terrain (positive number, may be a fractional decimal)\n  -f <filename>\tThe file to save the map to\n", prog);
}

void print_map(int **map, int width, int height)
{
     /* fill map with 0's */
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}


/* Average function that takes in any number of parameters but is prefaced with the number 
 * of arguments being averaged
 */
int average(int num, ... )
{
    va_list args;
    int sum = 0;

    /* Initializing arguments to store all values after num */
    va_start( args, num );
    /* Sum all the inputs; we still rely on the function caller to tell us how many there are */
    for( int i = 0; i < num; i++)
    {
        sum += va_arg(args, int);
    }
    va_end(args);
    
    return sum / num;
}

/* This function gives a boolean value back of whether a value should be added (true) or subtracted (false)
 */
bool should_add()
{
    return rand() % 2;
}



int** generate_map(int width, int height)
{
    /* malloc map*/
    int **map;
    map = (int **) malloc(sizeof(int *) * height);

    for(int i = 0; i < height; i++)
    {
        map[i] = (int *) malloc(sizeof(int) * width);
    }

    /* fill map with -1's */
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            map[y][x] = -1;
        }
    }


    return map;
}

/*
 * Randomizes the map with 0's and 1's
 */
void randomize(int **map, int width, int height)
{
    srand(time(NULL));
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            map[y][x] = rand() % 2;
        }
    }
}


int** build_map(int **map, int width, int height, float roughness)
{
    // set the corner seeds
    srand(time(NULL));
    int seed1, seed2, seed3, seed4;
    seed1 = rand() % 5000;
    seed2 = rand() % 5000;
    seed3 = rand() % 5000;
    seed4 = rand() % 5000;

    map[0][0] = seed1;
    map[0][width - 1] = seed2;
    map[height - 1][0] = seed3;
    map[height - 1][width -1] = seed4;
    
    printf("Seeds:\n%d\t%d\n%d\t%d\n", seed1, seed2, seed3, seed4);

    /* fill center tile */
    map[(height - 1) / 2][(width - 1) / 2] = average(4, seed1, seed2, seed3, seed4);

    int length = width / 2;
    while(length > 0)
    {
    
        /* Do Diamond Step */
        for(int y = 0; y < height / 2 / length; y++)
        {
            for(int x = 0; x < width / 2 / length; x++)
            {
                //printf("length: %d\n", length);
                diamond(map, width, height, length + (x * 2 * length), length + (y * 2 * length), length, roughness);
            }
        }

        /* Do Square Step */
        for(int y = 0; y < height / 2 / length; y++)
        {
            for(int x = 0; x < width / 2 / length; x++)
            {
                if(length > 1)
                {
                    square(map, length + (x * 2 * length), length + (y * 2 * length), length, roughness);
                }
            }
        }


        /* Adjust the length left */
        if(length == 1) length = 0;
        length -= length / 2;
    }

    return map;
}

void diamond (int** map, int width, int height, int x, int y, int length, float roughness)
{
    int salt;

    // top edge
    if(y - length == 0)
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y - length][x] = average(3, map[y][x], map[y - length][x - length], map[y - length][x + length]) + (salt * roughness);       
        }
        else
        {
            map[y - length][x] = average(3, map[y][x], map[y - length][x - length], map[y - length][x + length]) - (salt * roughness);
        }
    }
    // bottom edge
    if(y + length == height - 1)
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y + length][x] = average(3, map[y][x], map[y + length][x - length], map[y + length][x + length]) + (salt * roughness);
        }
        else
        {
            map[y + length][x] = average(3, map[y][x], map[y + length][x - length], map[y + length][x + length]) - (salt * roughness);
        }
    }
    //internal y index
    else
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y + length][x] = average(4, map[y][x], map[y + length][x - length], map[y + length][x + length], map[y + 2 * length][x]) + (salt * roughness);
        }
        else
        {
            map[y + length][x] = average(4, map[y][x], map[y + length][x - length], map[y + length][x + length], map[y + 2 * length][x]) - (salt * roughness);
        }
    }


    // left edge
    if(x - length == 0)
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y][x - length] = average(3, map[y][x], map[y - length][x - length], map[y + length][x - length]) + (salt * roughness);
        }
        else
        {
            map[y][x - length] = average(3, map[y][x], map[y - length][x - length], map[y + length][x - length]) - (salt * roughness);
        }
    }
    // right edge
    if(x + length == width - 1)
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y][x + length] = average(3, map[y][x], map[y - length][x + length], map[y + length][x + length]) + (salt * roughness);
        }
        else
        {
            map[y][x + length] = average(3, map[y][x], map[y - length][x + length], map[y + length][x + length]) - (salt * roughness);
        }
    }
    //internal x index
    else
    {
        salt = rand() % length;
        if(should_add())
        {
            map[y][x + length] = average(4, map[y][x], map[y - length][x - length], map[y + length][x + length], map[y][x + 2 * length]) + (salt * roughness);
        }
        else
        {
            map[y][x + length] = average(4, map[y][x], map[y - length][x - length], map[y + length][x + length], map[y][x + 2 * length]) - (salt * roughness);
        }
    }

}


void square_without_salt(int **map, int x, int y, int length)
{

    map[y - length / 2][x - length / 2] = average(4, map[y - length][x - length], map[y - length][x], map[y][x - length], map[y][x]);

    map[y - length / 2][x + length / 2] = average(4, map[y - length][x], map[y - length][x + length], map[y][x + length], map[y][x]);

    map[y + length / 2][x - length / 2] = average(4, map[y][x - length], map[y + length][x - length], map[y + length][x], map[y][x]);

    map[y + length / 2][x + length / 2] = average(4, map[y][x + length], map[y + length][x], map[y + length][x + length], map[y][x]);


}

void square(int **map, int x, int y, int length, float roughness)
{
    int salt;

    salt = rand() % length;

    if(should_add())
    {
        map[y - length / 2][x - length / 2] = average(4, map[y - length][x - length], map[y - length][x], map[y][x - length], map[y][x]) + (salt * roughness);
    }
    else
    {
        map[y - length / 2][x - length / 2] = average(4, map[y - length][x - length], map[y - length][x], map[y][x - length], map[y][x]) - (salt * roughness);
    }
    
    
    salt = rand() % length;

    if(should_add())
    {
        map[y - length / 2][x + length / 2] = average(4, map[y - length][x], map[y - length][x + length], map[y][x + length], map[y][x]) + (salt * roughness);
    }
    else
    {
        map[y - length / 2][x + length / 2] = average(4, map[y - length][x], map[y - length][x + length], map[y][x + length], map[y][x]) - (salt * roughness);
    }
   

    salt = rand() % length;

    if(should_add())
    {
        map[y + length / 2][x - length / 2] = average(4, map[y][x - length], map[y + length][x - length], map[y + length][x], map[y][x]) + (salt * roughness);
    }
    else
    {
        map[y + length / 2][x - length / 2] = average(4, map[y][x - length], map[y + length][x - length], map[y + length][x], map[y][x]) - (salt * roughness); 
    }


    salt = rand() % length;

    if(should_add())
    {
        map[y + length / 2][x + length / 2] = average(4, map[y][x + length], map[y + length][x], map[y + length][x + length], map[y][x]) + (salt * roughness);
    }
    else
    {
        map[y + length / 2][x + length / 2] = average(4, map[y][x + length], map[y + length][x], map[y + length][x + length], map[y][x]) - (salt * roughness);  
    }
}


/*
 * this function makes sure the heightmap is within a given bounds
 */
void clip(int **map, int width, int height, int top, int bottom)
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



void write_map(char *filename, int **map, int width, int height)
{
    FILE *file = fopen(filename, "w");
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            fprintf(file, "%d ", map[y][x]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


int main(int argc, char **argv)
{

    if(argc < 3)
    {
        halp(argv[0]);
        return EXIT_FAILURE;
    }
    if(strcmp(argv[1], "--help") == 0)
    {
        halp(argv[0]);
        return EXIT_SUCCESS;
    }

    int c,width, height;
    float roughness;
    char filename[BUFSIZ];
    while((c = getopt(argc, argv, "h:w:f:r:")) > 0)
    {
        switch(c)
        {
            case 'h':
                height = atoi(optarg);
                break;
            case 'w':
                width = atoi(optarg);
                break;
            case 'f':
                strcpy(filename, optarg);
                break;
            case 'r':
                roughness = atof(optarg);
        }
    }

    printf("parameters parsed\n");
    printf("map is %dx%d\n", width, height);

    int **map = generate_map(width, height);
    //printf("Original:\n");
    //print_map(map, width, height);
    printf("Building map...\n");
    build_map(map, width, height, roughness);
    clip(map, width, height, 10000, -10000);
    //print_map(map, width, height);

    /*
    printf("\n\n---mod 100 for testing---\n\n");
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(map[y][x] < 0)
            {
                map[y][x] = 0 -((0 - map[y][x]) % 100);
            }
            else
            {
                map[y][x] %= 100;
            }
        }
    }
    */

    //print_map(map, width, height);
    printf("Writing map to file: %s\n", filename);
    write_map(filename, map, width, height);

    return EXIT_SUCCESS;
}









