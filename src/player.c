#include <raylib.h>
#include <stdlib.h>
#include "game.h"

Player *makePlayer(double x, double y) {
	Player *p = malloc(sizeof(Player));
	p->x = x;
	p->y = y;
	p->width = 20.0;
	p->height = 20.0;
	p->can_climb = 0;
	return p;
}

void drawPlayer(Player p)
{
	DrawRectangle(p.x, p.y, p.width, p.height, BLUE);
}

void handlePlayerMovement(Player *p)
{
	if (IsKeyDown(KEY_RIGHT)) p->x += 0.02;
	if (IsKeyDown(KEY_DOWN) && p->can_climb) p->y += 0.02;
	if (IsKeyDown(KEY_LEFT)) p->x -= 0.02;
	if (IsKeyDown(KEY_UP) && p->can_climb) p->y -= 0.02;
}

