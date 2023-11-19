#include <raylib.h>
#include <cstring>
#include <string>
#include "sudoku.h"
#include <iostream>
#include <cstdlib>
#include "window.h"
using namespace std;
int main()
{
	WindowSudoku Window1;
	InitWindow(Window1.getWindowWidth(), Window1.getWindowHeight(), "SudokuMasterrace");
	SetTargetFPS(60);
	Window1.initFields();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if (Window1.getQuitState())
		{
			break;
		}
		if (Window1.getMenuState())
		{
			Window1.drawMenu();
			Window1.handleMenuHover();
			Window1.handleMenuClick();
		}
		else
		{
			Window1.handleClick();
			Window1.handleHover();
			Window1.handleEnter();
			Window1.drawPlane();
			Window1.handleButtonHover();
			Window1.drawNumbers();
			Window1.displayTime(100, 100);
		}

		EndDrawing();
	}
}