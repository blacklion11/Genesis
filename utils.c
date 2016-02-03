
#include "genesis.h"


int load_game(struct Game* game)
{
    LOG("Loading save file\n");
    FILE *file = fopen("save.txt", "r");
    
    if(file == NULL)
    {
        NDEBUG("Save file doesn't exist");
        LOG("Save file not found");
        return 1;
    }

    char buff[BUFSIZ];
    int linenum = 0;

    while(fgets(buff, BUFSIZ, file) != NULL)
    {
        buff[strlen(buff) - 1] = '\0';

        // load in the width and height of the map so we can malloc it
        if(linenum == 0)
        {
            game->world->width = atoi(buff);   
            LOG("Width set\n");
            linenum++;
            //NDEBUG("width = %d", game->world->width);
            LOG("World width parsed: %d\n", game->world->width);
            continue;
        }
        if(linenum == 1)
        {
            game->world->height = atoi(buff);
            linenum++;
            //NDEBUG("height = %d", game->world->height);
            //NDEBUG("%s", buff);
            LOG("World height parsed: %d\n", game->world->height);
            continue;
        }
        if(linenum > 1)break;
    
    }
    fclose(file);

    //malloc the map
    malloc_map(game);

    //load in the actual map
    load_world(game->world);

    LOG("Save file loaded\n");
}

int load_world(struct World* world)
{
    FILE *file = fopen("save.txt", "r");
    
    char buff[BUFSIZ];
    // bypass the first two lines (which contain the width and height)
    fgets(buff, BUFSIZ, file);
    fgets(buff, BUFSIZ, file);

    int row = 2;
    while(fgets(buff, BUFSIZ, file) != NULL)
    {
        buff[strlen(buff) - 1] = '\0';

        LOG("string read in from file: %s\n", buff);

        // tokenize the map 
        char *token;
        token = strtok(buff, " ");

        int col = 0;
        while(token != NULL)
        {
            LOG("num cols = %d, token: %s\n", col, token);
            //LOG("token is %s\n", token);
            world->map->blocks[row][col]->id = atoi(token);
            col++;
            token = strtok(NULL, " ");
        }
        
        row++;
    }
    fclose(file);
}

int save_game(struct Game* game)
{
    FILE *file = fopen("save.txt", "w");
    
    fprintf(file, "%d\n", game->world->width);
    fprintf(file, "%d\n", game->world->height);

    for(int y = 0; y < game->world->height; y++)
    {
        for(int x = 0; x < game->world->width; x++)
        {
            fprintf(file, "%d ", game->world->map->blocks[y][x]->id);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


int malloc_player(struct Game* game)
{
    if(game == NULL)
    {
        LOG("Cannot malloc player, Game struct is null");
        return 1;
    }
    game->player = (struct Player*) malloc(sizeof(struct Player));

    game->player->xpos = 0;
    game->player->ypos = 0;
    game->player->xblock = 0;
    game->player->yblock = 0;
    game->player->token = '@';

    return 0;
}

struct Game * malloc_game()
{
    return (struct Game*) malloc(sizeof(struct Game));
}


int malloc_world(struct Game* game)
{
    if(game == NULL)
    {
        LOG("Can't malloc world, Game struct null\n");
        return 1;
    }

    game->world = (struct World*) malloc(sizeof(struct World));
    
}


int malloc_map(struct Game* game)
{

    if(game == NULL)
    {
        LOG("Can't malloc world, Game struct null\n");
        return 1;
    }

    game->world->map = (struct Map*) malloc(sizeof(struct Map));

    struct Map* map = game->world->map;

    map->blocks = (struct Block***) malloc(game->world->height * sizeof(struct Block**));

    for(int i = 0; i < game->world->height; i++)
    {
        map->blocks[i] = (struct Block**) malloc(game->world->width * sizeof(struct Block*));
    }

    for(int y = 0; y < game->world->height; y++)
    {
        for(int x = 0; x < game->world->width; x++)
        {
            map->blocks[y][x] = (struct Block*) malloc(sizeof(struct Block));
        }
    }
}





















