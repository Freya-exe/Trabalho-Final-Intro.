#include <raylib.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "resource_dir.h"

Map *read_map(char* map_path){

    Map* map = malloc(sizeof(Map));

    SearchAndSetResourceDir("resources");

    FILE* fptr = fopen(map_path, "r");

    char character;
    int cols = 0;
    map->resolution = (Vector2){ 0, 1 };

    while ((character = fgetc(fptr)) != EOF)
    {
        
        if (cols > map->resolution.x){
            map->resolution.x = cols;
        }

        if (character == '\n'){
            map->resolution.y++;
            cols = 0;
        }else{
            cols++;
        }

    }

    fclose(fptr);

    // Map tiles

    map->tiles = (char**)malloc(map->resolution.y * sizeof(char*));

    // failed to allocate memory
    if (map == NULL) return NULL;

    // allocate memory for rows
    for (int i = 0; i < map->resolution.x; i++){
        map->tiles[i] = (char*)malloc(map->resolution.x * sizeof(char));
        if (map == NULL) return NULL;
    }

    fptr = fopen(map_path, "r");

    for (int y = 0; y < map->resolution.y; y++){
        for (int x = 0; x < map->resolution.x; x++){

            character = fgetc(fptr);

            while (character == '\n' || character == '\r')
            {
                character = fgetc(fptr);
            }
            
            if (character == 'p') map->spawn_pos = (Vector2){ x, y };

            if (character == 'f') map->porta_pos = (Vector2){ x, y };

            map->tiles[y][x] = character;

        }
    }     

    fclose(fptr);

    
    int rect_size = 0;
    int rect_count = 0;

    const int max_rects = ((int)(map->resolution.x * map->resolution.y) % 2) ? (map->resolution.x * map->resolution.y) / 2 + 1 : (map->resolution.x * map->resolution.y) / 2;

    Vector2* positions = (Vector2*)malloc(max_rects * sizeof(Vector2));
    Vector2* sizes = (Vector2*)malloc(max_rects * sizeof(Vector2));

    for (int y = 0; y < map->resolution.y; y++){
        for (int x = 0; x < map->resolution.x; x++){

            if (map->tiles[y][x] == 'z') rect_size++;

            // Se não for vazio e o proximo elemento não for z ou final da linha, completa o rect
            if ( rect_size != 0 && ( (x == map->resolution.x - 1 && map->tiles[y][x] == 'z') || (x < map->resolution.x - 1 && map->tiles[y][x+1] != 'z') ) ){   

                positions[rect_count].x = (x - rect_size + 1);
                positions[rect_count].y = y;
                sizes[rect_count].x = rect_size;
                sizes[rect_count].y = 1;

                rect_count++;
                rect_size = 0;

            }

        }
    }

    int screen_width = GetScreenWidth();

    float tile_size = screen_width / map->resolution.x;

    map->collisions_quantity = rect_count;

    map->collisions = (Rectangle*)malloc(map->collisions_quantity * sizeof(Rectangle));

        for (int i = 0; i < map->collisions_quantity; i++){

            map->collisions[i] = (Rectangle){
            (float)positions[i].x * tile_size,
            (float)positions[i].y * tile_size,
            (float)sizes[i].x * tile_size,
            (float)sizes[i].y * tile_size
        };
            
        //printf("props[%d]: { %.2f, %.2f, %.2f, %.2f }\n", i, positions[i].x, positions[i].y, sizes[i].x, sizes[i].y);
        //printf("Rect[%d]: { %.2f, %.2f, %.2f, %.2f }\n", i, map->collisions[i].x, map->collisions[i].y, map->collisions[i].width, map->collisions[i].height);
    
    }



    return map;
}