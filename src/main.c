#include <raylib.h>
#include "resource_dir.h"
#include "game.h"
#include <stdio.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

#define TAM_FONT 30
#define TAM_FONT_BIG 60

int main ()
{

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Donkey Kong");

	TraceLog(LOG_INFO, "%s", "INITIALIZED WINDOW");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	SetTargetFPS(120);

	int current_screen = TITLE;
	int quit = 0;
	int pause = 0;

	Map* map = read_map("map1.txt");

	int tile_size = SCREEN_WIDTH / map->resolution.x;

	Player *player = makePlayer(map->spawn_pos.x, map->spawn_pos.y, tile_size);

	RenderTexture2D map_texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	BeginTextureMode(map_texture);

		ClearBackground(BLACK);

		for (int y = 0; y < map->resolution.y; y++){
					for (int x = 0; x < map->resolution.x; x++){

						char tile = map->tiles[y][x];

						switch (tile)
						{
						case 'z':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), BLUE);
							break;

						case 'e':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), RED);
							break;

						case 's':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), ORANGE);
							break;

						case 'h':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), YELLOW);
							break;
						
						case 'd':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), ORANGE);
							break;

						case 'f':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), BROWN);
							break;
						
						case 'p':
							DrawRectangle(x * tile_size, y * (SCREEN_HEIGHT / map->resolution.y), tile_size, (SCREEN_HEIGHT / map->resolution.y), PINK);
							break;

						default:
							break;
						}

					}
		}

	EndTextureMode();

	// game loop
	while (!quit && !WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		
		float delta_time = GetFrameTime();

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

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
					
					handlePlayerMovement(player, map, delta_time);

					drawPlayer(*player);				

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
	
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
