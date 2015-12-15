#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

void halp(const char *prog)
{

    printf("Usage:  %s [-hwf]\n  --help\tDisplay this help screen\n  -h <number>\tSpecify the height\n  -w <number>\tSpecify the width\n  -f <filename>\tThe file to save the map to\n", prog);

}


int** create_map(int width, int height)
{

    /* Malloc Map */
    int **map;
    map = (int **) malloc (sizeof(int *) * height);

    for(int i = 0; i < height; i++)
    {
        map[i] = (int *) malloc (sizeof(int) * width);
    }


    printf("Map malloc'd\n");

    /* Fill map with 0's */
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }


    /* Pick random spot for trees */
    srand(time(NULL));
    int x = rand();
    int y = rand();

    x %= width;
    y %= height;

    map[y][x] = 1;

    printf("Map initialized\n");
    return map;
}


/**
 * Seed Generation
 * */
int generate_seed()
{
    srand(time(NULL));
    int seed;

    do
    {
        seed = rand();
    }
    while(seed < 1111);

    printf("Seed: %d\n", seed);

    return seed;
}


/**
 *  Salt for roughing up the tile heights
 */
int salt()
{
    srand(time(NULL));
    int salt = rand() % 100;
    printf("Salt: %d\n", salt);
    return salt;
    /*
    int salt =  rand() % 100;
    if(rand() % 2)
        return salt;
    else
        return 0 - salt;
    */
}


/*
* Diamond Terrain Generation
*/
void diamond_step(int **map, int width, int height, int x, int y, int length)
{
    if(y - length == 0)
    {
        map[y - length][x] = (map[y][x]    +    map[y - length][x - length]    +    map[y - length][x + length]) / 3 + salt();
    }
    if(y + length == width - 1)
    {
        map[y+length][x] = (map[y][x]    +   map[y + length][x - length]    +   map[y + length][x + length]) / 3 + salt();
    }
    else
    {
        map[y + length][x] = (map[y][x]    +    map[y + length][x - length]    +    map[y + length][x + length]    +    map[y + 2 * length][x]) / 4 + salt();
    }
    if(x - length == 0)
    {
        map[y][x - length] = (map[y][x]    +   map[y - length][x - length]    +   map[y + length][x - length]) / 3 + salt ();
    }
    if(x + length == height - 1)
    {
        map[y][x + length] = (map[y][x]    +   map[y - length][x + length]    +   map[y + length][x + length]) / 3 + salt();
    }
    else
    {
        map[y][x + length] = (map[y][x]    +    map[y - length][x - length]    +    map[y + length][x + length]    +    map[y][x + 2 * length]) / 4 + salt();
    }
}

/**
 * Square Terrain Generation
 * */
void square_step(int **map, int x, int y, int length)
{
    map[y - length / 2][x - length / 2] = (map[y - length][x - length]    +    map[y - length][x]    +    map[y][x - length]    +    map[x][y]) / 4 + salt();
    map[y - length / 2][x + length / 2] = (map[y - length][x]    +    map[y - length][x + length]    +    map[y][x + length]    +    map[x][y]) / 4 + salt();
    map[y + length / 2][x - length / 2] = (map[y][x - length]    +    map[y + length][x - length]    +    map[y + length][x]    +    map[x][y]) / 4 + salt();
    map[y + length / 2][x + length / 2] = (map[y][x + length]    +    map[y + length][x]    +    map[y + length][x + length]    +    map[x][y]) / 4 + salt();
}


void inter_smooth(int **map, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            map[i][j] %= 100;
        }
    }
}



/**
 * Terrain heightmap generation
 * */
int**  generate_heightmap(int width, int height)
{

    /* Malloc Map */
    int **map;
    map = (int **) malloc (sizeof(int *) * height);

    for(int i = 0; i < height; i++)
    {
        map[i] = (int *) malloc (sizeof(int) * width);
    }


    /* Fill map with 0's */
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }

    /* Generate Seed */
    int seed = generate_seed();

    /* Set the corners */
    map[width - 1][width - 1] = seed % 100;
    map[width - 1][0] = seed / 100 % 100;
    map[0][width - 1] = seed / 10000 % 100;
    map[0][0] = seed / 1000000 % 100;


    printf("Corner Seeds:\n%d\t%d\n%d\t%d\n", map[0][0], map[0][width - 1], map[width - 1][0], map[width - 1][width - 1]);

    /* fill center tile */
    map[(width - 1) / 2][(height - 1) / 2] = (map[0][0] + 
                                              map[0][height - 1] +
                                              map[width - 1][0] + 
                                              map[width - 1][height - 1]) / 4 + salt();


    int length = width / 2;
    while(length > 0)
    {
        /* Do diamond step */
        int i,j;
        for(i = 0; i < width / 2 / length; i++)
        {
            for(j = 0; j < height / 2 / length; j++)
            {
                diamond_step(map, width, height, length + (j * 2 * length), length + (i * 2 * length), length);
            }
        }

        /* Do square step */
        for(i = 0; i < width / 2 / length; i++)
        {
            for(j = 0; j < height / 2 / length; j++)
            {
                if(length > 1)
                {
                    square_step(map, length + (j * 2 * length), length + (i * 2 * length), length);
                }
            }
        }
  
        /* Smooth after each step */
        inter_smooth(map, width, height);

        /* Adjust the length left */
        if(length == 1)length = 0;
        length -= length / 2;
    }

    /* final smoothing */
    //inter_smooth(map, width, height);
    
    printf("Heightmap generated\n");

    return map;
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

    int c, width, height;
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

    printf("Map is %dx%d\n", width,height);


    FILE *file = fopen(filename, "w");

    //int ** map = create_map(width, height);
    int **map = generate_heightmap(width, height);

    printf("map generated\n");
    for(int i = 0; i < height; i++)
    {
        printf("Line %d written to file", i);
        for(int j = 0; j < width; j++)
        {
            fprintf(file, "%d ", map[i][j]);
        }
        fputs("\n", file);
    }

    fclose(file);


    return EXIT_SUCCESS;


}
