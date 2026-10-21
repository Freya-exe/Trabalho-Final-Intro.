#include <raylib.h>

#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

#define TARGET_FPS 60

#define TAM_FONT 30
#define TAM_FONT_BIG 60

typedef struct player {
	double x;
	double y;
	double width;
	double height;
	Vector2 velocity;
	int can_climb;
} Player;

typedef struct enemy {
	Vector2 pos;
	Vector2 size;
	double velocity;
} Enemy;

typedef struct ranking_item {
	char name[20];
	double time;
} RankingItem;

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
Enemy *makeEnemy(Vector2 pos, Vector2 size, double velocity);
void walkEnemy(Enemy *e);
void drawEnemy(Enemy *e);
void drawEndingScreen();
void handleEndingSelection(int *current_screen);
RankingItem *makeRanking(int n);
void updateRanking(RankingItem *r, int n, int index, char *name, double time);
void sortRanking(RankingItem *r, int n);
#endif
