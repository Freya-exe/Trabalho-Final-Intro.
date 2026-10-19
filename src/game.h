#include <raylib.h>

#ifndef GAME_H
#define GAME_H
typedef struct player {
	double x;
	double y;
	double width;
	double height;
	Vector2 velocity;
	int can_climb;
} Player;

enum {
	TITLE = 0,
	GAMEPLAY,
	ENDING,
	RANKING,
	QUIT
};

void drawPlayer(Player p);
void drawMenu();
void handlePlayerMovement(Player *p);
void handleScreenSelection(int *current_screen);
Player *makePlayer(double x, double y);
#endif
