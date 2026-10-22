#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "game.h"

InputBox *makeInputBox(double x, double y, double width, double height, int maxText)
{
	InputBox *inputBox = malloc(sizeof(InputBox));
	inputBox->box = (Rectangle){x,y,width,height};
	inputBox->maxText = maxText;
	inputBox->text = malloc(sizeof(char) * (maxText + 1));
	strcpy(inputBox->text, "\0");
	inputBox->mouseOnText = 0;
	inputBox->letterCount = 0;
	inputBox->done = 0;
	return inputBox;
}

void checkInput(InputBox *inputBox)
{
	if (CheckCollisionPointRec(GetMousePosition(), inputBox->box)) {
		inputBox->mouseOnText = 1;
	} else {
		inputBox->mouseOnText = 0;
	}

	if (inputBox->mouseOnText) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		
		int key = GetCharPressed();
		inputBox->done = 0;

		while (key > 0) {
			if ((key >= 32) && (key <= 125) && (inputBox->letterCount < inputBox->maxText)) {
				inputBox->text[inputBox->letterCount] = (char)key;
				inputBox->text[inputBox->letterCount + 1] = '\0';
				inputBox->letterCount++;
			}
			key = GetCharPressed();
		}
		if (IsKeyPressed(KEY_BACKSPACE)) {
			inputBox->letterCount--;
			if (inputBox->letterCount < 0) {
				inputBox->letterCount = 0;
			}
			inputBox->text[inputBox->letterCount] = '\0';
		}
		if (IsKeyPressed(KEY_ENTER)) {
			inputBox->done = 1;
		}
	} else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void drawInputBox(InputBox *inputBox)
{
	DrawRectangleRec(inputBox->box, LIGHTGRAY);
	if (inputBox->mouseOnText) {
		DrawRectangleLines(inputBox->box.x, inputBox->box.y, inputBox->box.width, inputBox->box.height, RED);
	} else {
		DrawRectangleLines(inputBox->box.x, inputBox->box.y, inputBox->box.width, inputBox->box.height, DARKGRAY);
	}
	DrawText(inputBox->text, inputBox->box.x + 5, inputBox->box.y + 5, TAM_FONT, MAROON);
}
