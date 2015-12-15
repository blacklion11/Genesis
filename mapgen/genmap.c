
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

void diamond(int**, int, int, int, int, int);
void square(int**, int, int ,int);


void halp(const char *prog)
{
    printf("Usage: %s [-hwf]\n  --help\tDisplay this help screen\n  -h <number>\tSpecify the height (must be a 2^n + 1)\n  -w <number>\tSpecify the width (must be a 2^n + 1)\n  -f <filename>\tThe file to save the map to\n", prog);
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


int** build_map(int **map, int width, int height)
{
    // set the corner seeds
    srand(time(NULL));
    int seed1, seed2, seed3, seed4;
    seed1 = rand() % 1000;
    seed2 = rand() % 1000;
    seed3 = rand() % 1000;
    seed4 = rand() % 1000;

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
                printf("length: %d\n", length);
                diamond(map, width, height, length + (x * 2 * length), length + (y * 2 * length), length);
            }
        }

        /* Do Square Step */
        for(int y = 0; y < height / 2 / length; y++)
        {
            for(int x = 0; x < width / 2 / length; x++)
            {
                if(length > 1)
                {
                    square(map, length + (x * 2 * length), length + (y * 2 * length), length);
                }
            }
        }


        /* Adjust the length left */
        if(length == 1) length = 0;
        length -= length / 2;
    }

    return map;
}

void diamond (int** map, int width, int height, int x, int y, int length)
{
    // top edge
    if(y - length == 0)
    {
        map[y - length][x] = average(3, map[y][x], map[y - length][x - length], map[y - length][x + length]);       
    }
    // bottom edge
    if(y + length == height - 1)
    {
        map[y + length][x] = average(3, map[y][x], map[y + length][x - length], map[y + length][x + length]);   
    }
    //internal y index
    else
    {
        map[y + length][x] = average(4, map[y][x], map[y + length][x - length], map[y + length][x + length], map[y + 2 * length][x]);
    }

    // left edge
    if(x - length == 0)
    {
        map[y][x - length] = average(3, map[y][x], map[y - length][x - length], map[y + length][x - length]);
    }
    // right edge
    if(x + length == width - 1)
    {
        map[y][x + length] = average(3, map[y][x], map[y - length][x + length], map[y + length][x + length]);
    }
    //internal x index
    else
    {
        map[y][x + length] = average(4, map[y][x], map[y - length][x - length], map[y + length][x + length], map[y][x + 2 * length]);
    }

}


void square(int **map, int x, int y, int length)
{
    map[y - length / 2][x - length / 2] = average(4, map[y - length][x - length], map[y - length][x], map[y][x - length], map[y][x]);
    
    map[y - length / 2][x + length / 2] = average(4, map[y - length][x], map[y - length][x + length], map[y][x + length], map[y][x]);
   
    map[y + length / 2][x - length / 2] = average(4, map[y][x - length], map[y + length][x - length], map[y + length][x], map[y][x]);

    map[y + length / 2][x + length / 2] = average(4, map[y][x + length], map[y + length][x], map[y + length][x + length], map[y][x]);
}



int main(int argc, char **argv)
{

    if(argc < 2)
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
    char filename[BUFSIZ];
    while((c = getopt(argc, argv, "h:w:f:")) > 0)
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
        }
    }

    printf("parameters parsed\n");
    printf("map is %dx%d\n", width, height);

    int **map = generate_map(width, height);
    printf("Original:\n");
    print_map(map, width, height);
    printf("Building map...\n");
    build_map(map, width, height);
    print_map(map, width, height);


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

    print_map(map, width, height);

    return EXIT_SUCCESS;
}









