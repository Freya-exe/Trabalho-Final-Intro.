#include <raylib.h>
#include <stdlib.h>
#include "game.h"

Enemy *makeEnemy(Vector2 pos, Vector2 size, double velocity)
{
	Enemy *enemy = malloc(sizeof(Enemy));
	enemy->pos = pos;
	enemy->size = size;
	enemy->velocity = velocity;
	return enemy;	
}

void walkEnemy(Enemy *e)
{
	if (e->pos.x >= (SCREEN_WIDTH - e->size.x) || e->pos.x <= e->size.x) {
		e->velocity *= -1;
	}
	e->pos.x += e->velocity;
}

void drawEnemy(Enemy *e)
{
	DrawRectangle(e->pos.x, e->pos.y, e->size.x, e->size.y, MAROON);
}
