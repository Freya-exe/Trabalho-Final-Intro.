#include <raylib.h>

#ifndef GAME_H
#define GAME_H
typedef struct player {
	float x;
	float y;
	float size;
	Vector2 velocity;
	int can_climb;
	Rectangle hitbox;
} Player;

typedef struct map {
	int collisions_quantity;
    char** tiles;
    Vector2 resolution;
    Vector2 spawn_pos;
    Vector2 porta_pos;
    Rectangle* collisions;
} Map;

enum {
	TITLE = 0,
	GAMEPLAY,
	ENDING,
	RANKING,
	QUIT
};

void drawPlayer(Player p);
void drawMenu();
void handlePlayerMovement(Player *p, Map *map, float delta_time);
void handleScreenSelection(int *current_screen);

Player *makePlayer(float x, float y, float size);
Map *read_map(char* map_path);

#endif