#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "game.h"
#include "funcs.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

#define TARGET_FPS 60

#define TAM_FONT 30
#define TAM_FONT_BIG 60

int main()
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "donkey kong");
	int current_screen = TITLE;
	
	TraceLog(LOG_INFO, "%s", "INITIALIZED WINDOW");

	Player *player = makePlayer(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
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


	while (!quit && !WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (current_screen) {
			case TITLE:
				handleScreenSelection(&current_screen);
				drawMenu();
				break;
			case GAMEPLAY:
				if (IsKeyPressed(KEY_SPACE)) {
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
					
				

				} else {
					char pause_msg[] = "GAME PAUSED";
					double pause_msg_size = MeasureText(pause_msg, TAM_FONT_BIG);
					DrawText(pause_msg, (SCREEN_WIDTH - pause_msg_size) / 2.0, (SCREEN_HEIGHT)/2.0 - 100, TAM_FONT_BIG, MAROON);
				}
				break;
			case QUIT:
				quit = 1;
				break;
		}
		EndDrawing();
	}
	free(player);

	CloseWindow();

	return 0;
}
