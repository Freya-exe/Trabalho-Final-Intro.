/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "funcs.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <stdio.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

int main ()
{
	
	char **map;
 
	Vector2 map_res;

	map = map_read();

	map_res = get_map_res();

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	SetTargetFPS(120);

	Vector2 player_pos = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
	const float player_speed = 200;

	RenderTexture2D map_texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	BeginTextureMode(map_texture);
		ClearBackground(BLACK);

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

	Rectangle player = {player_pos.x, player_pos.y, SCREEN_WIDTH/map_res.x, SCREEN_HEIGHT/map_res.y};

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		
		
		float delta_time = GetFrameTime();


		if (IsKeyDown(KEY_RIGHT)) player.x += player_speed * delta_time;
		if (IsKeyDown(KEY_LEFT)) player.x -= player_speed * delta_time;
		if (IsKeyDown(KEY_UP)) player.y -= player_speed * delta_time;
		if (IsKeyDown(KEY_DOWN)) player.y += player_speed * delta_time;

		if (CheckCollisionRecs(player, rects[0])){
			printf("Colisao!!");
		}
		
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		DrawTextureRec(map_texture.texture,  (Rectangle){ 0, 0, (float)map_texture.texture.width, -(float)map_texture.texture.height }, (Vector2){ 0, 0 }, WHITE);	

		DrawRectangleRec(player, PINK);
	
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
