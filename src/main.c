#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "funcs.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#define ENEMIES 2
#define TAM_RANKING 10

int main()
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "donkey kong");
	int current_screen = TITLE;
	
	TraceLog(LOG_INFO, "%s", "INITIALIZED WINDOW");

	Vector2 playerSpawn = {SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0};
	Player *player = makePlayer(playerSpawn.x, playerSpawn.y);
	player->can_climb = 1;
	int quit = 0;
	int pause = 0;

	char **map;
 
	Vector2 map_res;

	map = map_read();

	map_res = get_map_res();

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	SetTargetFPS(TARGET_FPS);

	Vector2 player_pos = { player->x, player->y};

	RenderTexture2D map_texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	BeginTextureMode(map_texture);
		ClearBackground(RAYWHITE);

		for (int y = 0; y < map_res.y; y++){
					for (int x = 0; x < map_res.x; x++){

						char tile = map[y][x];

						switch (tile)
						{
						case 'z':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), BLUE);
							break;

						case 'e':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), RED);
							break;

						case 's':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), ORANGE);
							break;

						case 'h':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), YELLOW);
							break;
						
						case 'd':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), ORANGE);
							break;

						case 'f':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), BROWN);
							break;
						
						case 'p':
							DrawRectangle(x * (SCREEN_WIDTH / map_res.x), y * (SCREEN_HEIGHT / map_res.y), (SCREEN_WIDTH / map_res.x), (SCREEN_HEIGHT / map_res.y), PINK);
							break;

						default:
							break;
						}

					}
		}

	EndTextureMode();

	Rectangle* rects = create_collisions(map, (Vector2){SCREEN_WIDTH / map_res.x, SCREEN_HEIGHT/map_res.y});

	Rectangle playerRect = {player_pos.x, player_pos.y, SCREEN_WIDTH/map_res.x, SCREEN_HEIGHT/map_res.y};


	Vector2 enemiesSpawn[ENEMIES] = {(Vector2){30,30}, (Vector2){130,270}};
	Enemy *enemies[ENEMIES];
	enemies[0] = makeEnemy(enemiesSpawn[0], (Vector2){20, 20}, 0.2);
	enemies[1] = makeEnemy(enemiesSpawn[1], (Vector2){20, 20}, 0.2);

	RankingItem* ranking = makeRanking(TAM_RANKING);
	/*
	updateRanking(ranking, TAM_RANKING, 0, "jonatas", 2.3);
	updateRanking(ranking, TAM_RANKING, 1, "mateus", 6.1);
	updateRanking(ranking, TAM_RANKING, 2, "amanda", 6.2);
	updateRanking(ranking, TAM_RANKING, 3, "bruno", 4.3);
	updateRanking(ranking, TAM_RANKING, 4, "otavio", 12.7);
	updateRanking(ranking, TAM_RANKING, 5, "lucas", 8.7);
	updateRanking(ranking, TAM_RANKING, 6, "ronaldo", 1.7);
	updateRanking(ranking, TAM_RANKING, 7, "viviane", 0.7);
	updateRanking(ranking, TAM_RANKING, 8, "fernanda", 4.2);
	updateRanking(ranking, TAM_RANKING, 9, "joane", 1.8);
	sortRanking(ranking, TAM_RANKING);
	writeRanking(ranking, TAM_RANKING);
	*/
	readRanking(ranking, TAM_RANKING);

	while (!quit && !WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (current_screen) {
			case TITLE:
				handleScreenSelection(&current_screen);
				drawMenu();
				break;
			case GAMEPLAY:
				if (IsKeyPressed(KEY_TAB)) {
					pause = !pause;
				}
				if (!pause) {
					DrawTextureRec(map_texture.texture,  (Rectangle){ 0, 0, (float)map_texture.texture.width, -(float)map_texture.texture.height }, (Vector2){ 0, 0 }, WHITE);	
					handlePlayerMovement(player);
					if (player->x >= (GetScreenWidth() - player->width)) player->x -= 0.02;
					if (player->y >= (GetScreenHeight() - player->height)) player->y -= 0.02;
					if (player->x <= player->width) player->x += 0.02;
					if (player->y <= player->height) player->y += 0.02;
					drawPlayer(*player);

					if (CheckCollisionRecs(playerRect, rects[0])){
						printf("Colisao!!");
					}

					for (int i = 0; i < ENEMIES; i++) {
						drawEnemy(enemies[i]);
						walkEnemy(enemies[i]);
						Rectangle _playerRect = {player->x, player->y, player->width, player->height};
						Rectangle enemyRect = {enemies[i]->pos.x, enemies[i]->pos.y, enemies[i]->size.x, enemies[i]->size.y};
						if (CheckCollisionRecs(_playerRect, enemyRect)) {
							current_screen = ENDING;
						}
					}
					
				} else {
					char pause_msg[] = "JOGO PAUSADO";
					double pause_msg_size = MeasureText(pause_msg, TAM_FONT_BIG);
					DrawText(pause_msg, (SCREEN_WIDTH - pause_msg_size) / 2.0, (SCREEN_HEIGHT)/2.0 - 100, TAM_FONT_BIG, MAROON);
				}
				break;
			case ENDING:
				player->x = playerSpawn.x;
				player->y = playerSpawn.y;
				for (int i = 0; i < ENEMIES; i++) {
					enemies[i]->pos.x = enemiesSpawn[i].x;
					enemies[i]->pos.y = enemiesSpawn[i].y;
				}

				drawEndingScreen();
				handleEndingSelection(&current_screen);

				break;
			case RANKING:
				for (int i = 0; i < TAM_RANKING; i++) {
					char msg[100];
					sprintf(msg, "%s:\t\t%.2fs", ranking[i].name, ranking[i].time);
					DrawText(msg, 20, i * 30, TAM_FONT, MAROON);
				}
				char *voltar_msg = "APERTE ESPACO PARA VOLTAR";
				DrawText(voltar_msg, (SCREEN_WIDTH - MeasureText(voltar_msg, TAM_FONT))/2, SCREEN_HEIGHT - 50, TAM_FONT, MAROON);
				if (IsKeyPressed(KEY_SPACE)) current_screen = TITLE;
				break;
			case QUIT:
				quit = 1;
				break;
		}
		EndDrawing();
	}
	free(player);
	for (int i = 0; i < ENEMIES; i++) {
		free(enemies[i]);
	}

	CloseWindow();

	return 0;
}
