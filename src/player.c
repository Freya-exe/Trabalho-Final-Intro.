#include <raylib.h>
#include <stdlib.h>
#include "game.h"
#include <stdio.h>

#define MOVE_SPEED 150
#define GRAVITY 100

Player *makePlayer(float x, float y, float size) {
	Player *p = malloc(sizeof(Player));

	p->size = size;
	p->x = x * p->size;
	p->y = y * p->size;
	p->velocity = (Vector2){0, 0};
	p->can_climb = 0;
	p->hitbox = (Rectangle){x * p->size, y * p->size, p->size, p->size};
	return p;
}

void drawPlayer(Player p)
{
	DrawRectangleRec(p.hitbox, GREEN);
}

void handlePlayerMovement(Player *player, Map *map, float delta_time)
{

	player->hitbox = (Rectangle){player->x, player->y, player->size, player->size };

	player->velocity.x = 0;

	if (IsKeyDown(KEY_RIGHT)) player->velocity.x = MOVE_SPEED;
	if (IsKeyDown(KEY_DOWN) && player->can_climb) player->velocity.y = MOVE_SPEED;
	if (IsKeyDown(KEY_LEFT)) player->velocity.x = -MOVE_SPEED;
	if (IsKeyDown(KEY_UP) && player->can_climb) player->velocity.y = -MOVE_SPEED;

	if ((player->x >= (GetScreenWidth() - player->size)) && (player->velocity.x > 0)) player->velocity.x = 0;
	if ((player->x <= 0) && (player->velocity.x < 0)) player->velocity.x = 0;

	for (int i = 0; i < map->collisions_quantity; i++){

		if (CheckCollisionRecs(player->hitbox, map->collisions[i])){

			if ((player->y >= map->collisions[i].y - (map->collisions[i].height/10*8)) || (player->y <= map->collisions[i].y - (map->collisions[i].height))){

				if ( (player->velocity.x > 0) && (player->x >= map->collisions[i].x - player->size)){
					printf("3\n");
					player->x = map->collisions[i].x - player->size;
					player->velocity.x = 0;
					
				} else if ( (player->velocity.x < 0) && (player->x <= map->collisions[i].x + map->collisions->width) ){
					printf("4\n");
					player->x = map->collisions[i].x + map->collisions->width;
					player->velocity.x = 0;
					
				}
			}

			if ( (player->velocity.y > 0) && ( player->y >= map->collisions[i].y - player->size) ){
				player->velocity.y = 0;
			} else if ( (player->velocity.y < 0) && (player->y >= map->collisions[i].y) ){
				player->velocity.y = 0;
			}				

			break;
		}

	}

	player->x += player->velocity.x * delta_time;
	player->y += player->velocity.y * delta_time;

	player->velocity.y += GRAVITY * delta_time;

}