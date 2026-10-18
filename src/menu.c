#include <stdio.h>
#include <raylib.h>
#include "game.h"

#define TAM_FONT 30
#define MENU_X 20
#define MENU_Y 20

void drawMenu()
{
	DrawText("DONKEY KONG MENU", MENU_X, MENU_Y, TAM_FONT, MAROON);
	DrawText("1. NOVO JOGO", MENU_X, MENU_Y + 100, TAM_FONT, MAROON);
	DrawText("2. RANKING",MENU_X, MENU_Y + 200, TAM_FONT, MAROON);
	DrawText("3. SAIR", MENU_X, MENU_Y + 300, TAM_FONT, MAROON);
}

void handleScreenSelection(int *current_screen)
{
	if (IsKeyDown(KEY_ONE)) *current_screen = GAMEPLAY;
	if (IsKeyDown(KEY_TWO)) *current_screen = RANKING;
	if (IsKeyDown(KEY_THREE)) *current_screen = QUIT;
}
