#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "resource_dir.h"
#include "raylib.h"

Vector2 get_map_res(){

    Vector2 map_resolution = {0,1};
    int cols = 0;

    FILE* fptr;
    int character;

    // read txt file

    SearchAndSetResourceDir("resources");

    char map_file[] = "map1.txt";
    
    fptr = fopen(map_file, "r");

    // could not open txt file
    if (fptr == NULL){
        
        fprintf(stderr, "Map file \"../resources/map1.txt\" could not open! Failed with errno: %d (%s)\n", errno, strerror(errno));



        exit(-1);
    }

    while ((character = fgetc(fptr)) != EOF)
    {
        
        if (cols > map_resolution.x){
            map_resolution.x = cols;
        }
        if (character == '\n'){
            map_resolution.y++;
            cols = 0;
        }else{
            cols++;
        }

    }

    fclose(fptr);
    return map_resolution;

}

char** map_read(){

    Vector2 map_res = get_map_res();
    FILE* fptr;
    int character;

    char map_file[] = "map1.txt";

    SearchAndSetResourceDir("resources");

    // memory allocation
    char** map = (char**)malloc(map_res.y * sizeof(char*));

    // failed to allocate memory
    if (map == NULL) return NULL;

    // allocate memory for rows
    for (int i = 0; i < map_res.x; i++){
        map[i] = (char*)malloc(map_res.x * sizeof(char));
    }

    // read txt file
    fptr  = fopen(map_file, "r");

    // could not open txt file
    if (fptr == NULL){

        printf("Map file \"./resources/map1.txt\" could not open!");
        exit(-1);
        
    }

    // iterate through array 
    for (int y = 0; y < map_res.y; y++){
        for (int x = 0; x < map_res.x; x++){

            character = fgetc(fptr);

            while (character == '\n' || character == '\r')
            {
                character = fgetc(fptr);
            }
            
            map[y][x] = character;

        }
    }        

    fclose(fptr);

    return map;

}

Rectangle* create_collisions(char** map, Vector2 tile_size){

    Rectangle* rects;

    int rect_size = 0;
    int rect_count = 0;

    Vector2 map_res = get_map_res();

    // max collision rects based on map size
    const int max_rects = ((int)(map_res.x * map_res.y) % 2) ? map_res.x*map_res.y/2 : (map_res.x*map_res.y)/2 + 1;

    Vector2* positions = (Vector2*)malloc(max_rects * sizeof(Vector2));
    Vector2* sizes = (Vector2*)malloc(max_rects * sizeof(Vector2));

    // calculate quantity of rectangles

    for (int y = 0; y < map_res.y; y++){
        for (int x = 0; x < map_res.x; x++){

            if (map[y][x] == 'z') rect_size++;

            // Se não for vazio e o proximo elemento não for z ou final da linha, completa o rect
            if ( rect_size != 0 && ( (x == map_res.x - 1 && map[y][x] == 'z') || (x < map_res.x - 1 && map[y][x+1] != 'z') ) ){   

                positions[rect_count].x = (x - rect_size + 1);
                positions[rect_count].y = y;
                sizes[rect_count].x = rect_size;
                sizes[rect_count].y = 1;

                rect_count++;
                rect_size = 0;
        }
    }
}

    rects = (Rectangle*)malloc(rect_count * sizeof(Rectangle));

    // create collision rectangles

    for (int i = 0; i < rect_count; i++){
        rects[i] = (Rectangle){
            (float)positions[i].x * tile_size.x,
            (float)positions[i].y * tile_size.y,
            (float)sizes[i].x * tile_size.x,
            (float)sizes[i].y * tile_size.y
        };
    }

    return rects;
}