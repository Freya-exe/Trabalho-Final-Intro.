#include <stdio.h>
#include <raylib.h>
#include "game.h"

void drawEndingScreen()
{
	DrawText("GAME OVER", (SCREEN_WIDTH/16), (SCREEN_HEIGHT/16), TAM_FONT_BIG, MAROON);
	DrawText("CONTINUAR?", (SCREEN_WIDTH/16), (SCREEN_HEIGHT/16) + 75, TAM_FONT, MAROON);
	DrawText("1. REINICIAR", (SCREEN_WIDTH/16), (SCREEN_HEIGHT/16) + 150, TAM_FONT, MAROON);
	DrawText("2. TELA INICIAL", (SCREEN_WIDTH/16), (SCREEN_HEIGHT/16) + 225, TAM_FONT, MAROON);
	DrawText("3. SAIR", (SCREEN_WIDTH/16), (SCREEN_HEIGHT/16) + 300, TAM_FONT, MAROON);
}

void handleEndingSelection(int *current_screen)
{
	if (IsKeyPressed(KEY_ONE)) *current_screen = GAMEPLAY;
	if (IsKeyPressed(KEY_TWO)) *current_screen = TITLE;
	if (IsKeyPressed(KEY_THREE)) *current_screen = QUIT;
}
