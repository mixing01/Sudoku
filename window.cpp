#include <raylib.h>
#include <cstring>
#include <string>
#include "sudoku.h"
#include "window.h"
#include <iostream>
#include <cstdlib>
void Field::setNumber(int num)
{
	number = num;
}
int Field::getNumber()
{
	return number;
}
bool Field::tryAction()
{
	return 0;
};
FieldEmpty::FieldEmpty(int num)
{
	setNumber(num);
}
bool FieldEmpty::tryAction()
{
	return true;
};

FieldFilled::FieldFilled(int num)
{
	setNumber(num);
}
bool FieldFilled::tryAction()
{
	return false;
};
void FieldFilled::setNum(int num)
{
	setNumber(num);
}

void Timer::showTime(int posX, int posY)
{
	seconds = (int)GetTime() - secSinceClose;
	minutes = seconds / 60;
	seconds = seconds - minutes * 60;
	if (seconds < 10)
	{
		secondsText = "0" + to_string(seconds);
	}
	else
	{
		secondsText = to_string(seconds);
	}
	if (minutes < 10)
	{
		minutesText = "0" + to_string(minutes);
	}
	else
	{
		minutesText = to_string(minutes);
	}
	timeNow = minutesText + ":" + secondsText;
	char showText[6];
	strcpy_s(showText, timeNow.c_str());
	DrawText(showText, posX, posY, 50, BLACK);
}

void Timer::resetTimer()
{
	secSinceClose = (int)GetTime();
}
int WindowSudoku::getWindowWidth()
{
	return WindowWidth;
}
int WindowSudoku::getWindowHeight()
{
	return WindowHeight;
}
void WindowSudoku::setNum(int row, int col, int num)
{
	numbers[row][col]->setNumber(num);
}
void WindowSudoku::drawPlane()
{
	for (int i = 0; i < 10; i++)
	{
		if (i % 3 == 0)
		{
			DrawRectangle(topLeftX + i * spaceBetweenLines - 3, topLeftY, 6, lineLength, BLACK);
			DrawRectangle(topLeftX, topLeftY + i * spaceBetweenLines - 3, lineLength, 6, BLACK);
		}
		else
		{
			DrawLine(topLeftX + i * spaceBetweenLines, topLeftY, topLeftX + i * spaceBetweenLines, botLeftY, BLACK);
			DrawLine(topLeftX, topLeftY + i * spaceBetweenLines, topRightX, topLeftY + i * spaceBetweenLines, BLACK);
		}
	}
	DrawRectangle(WindowWidth-250, WindowHeight-190, 200, 100, BLUE);
	DrawText("Check", WindowWidth - 250 + (200-MeasureText("Check",30))/2, WindowHeight - 155, 30, DARKPURPLE);
	DrawRectangle(50, WindowHeight - 190, 200, 100, BLUE);
	DrawText("Main Menu", 50 + (200 - MeasureText("Main Menu", 30)) / 2, WindowHeight - 155, 30, DARKPURPLE);
}
void WindowSudoku::drawNumber(int posX, int posY, string number, int fontSize, Color color)
{
	char numberCA[2];
	strcpy_s(numberCA, number.c_str());
	int textWidth = MeasureText(numberCA, fontSize);
	if (textWidth > spaceBetweenLines)
	{
		cout << "Too wide" << endl;
	}
	else if (stoi(number) != 0)
	{
		DrawText(numberCA, posX + (60 - textWidth) / 2, posY + (60 - fontSize) / 2, fontSize, color);
	}
}
void WindowSudoku::drawNumbers()
{
	int currX = topLeftX;
	int currY = topLeftY;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (numbers[i][j]->tryAction())
			{
				drawNumber(currX, currY, to_string(numbers[i][j]->getNumber()), 50, DARKGREEN);
			}
			else
			{
				drawNumber(currX, currY, to_string(numbers[i][j]->getNumber()), 50, BLUE);
			}
			
			currX += 60;
		}
		currX = topLeftX;
		currY += 60;
	}
}
void WindowSudoku::initFields()
{
	numbers = new Field * *[9];
	for (int i = 0; i < 9; i++)
	{
		numbers[i] = new Field * [9];
	}
	Sudoku1.permutations();
	Sudoku1.numberSwap(3);
	Sudoku1.deleteRandInt(45);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (Sudoku1.getNumberSWH(i, j) == 0)
			{
				numbers[i][j] = new FieldEmpty(NULL);
			}
			else
			{
				numbers[i][j] = new FieldFilled(Sudoku1.getNumberSWH(i, j));
			}
		}
	}
}
void WindowSudoku::displayTime(int posX, int posY)
{
	Timer1.showTime(posX, posY);
}
void WindowSudoku::handleHover()
{
	if (checkBackground)
	{
		checkSudoku();
	}
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	if ((mouseX > topLeftX) && (mouseX < (topLeftX + (spaceBetweenLines * 9))))
	{
		if ((mouseY > topLeftY) && (mouseY < (topLeftY + (spaceBetweenLines * 9))))
		{
			checkBackground = false;
			int col = (mouseX - topLeftX) / spaceBetweenLines;
			int row = (mouseY - topLeftY) / spaceBetweenLines;
			if (numbers[row][col]->tryAction())
			{
				if ((currentClickCol == col) && (currentClickRow == row))
				{
					DrawRectangle(topLeftX + currentClickCol * spaceBetweenLines, topLeftY + currentClickRow * spaceBetweenLines, spaceBetweenLines, spaceBetweenLines, ORANGE);
				}
				else
				{
					DrawRectangle(topLeftX + col * spaceBetweenLines, topLeftY + row * spaceBetweenLines, spaceBetweenLines, spaceBetweenLines, LIGHTGRAY);
				}
				
			}
		}
	}
}
void WindowSudoku::handleButtonHover()
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	if ((mouseX > WindowWidth - 250) && (mouseX < WindowWidth - 50))
	{
		if ((mouseY > WindowHeight - 190) && (mouseY < WindowHeight - 90))
		{
			DrawRectangle(WindowWidth - 250, WindowHeight - 190, 200, 100, LIGHTGRAY);
			DrawText("Check", WindowWidth - 250 + (200 - MeasureText("Check", 30)) / 2, WindowHeight - 155, 30, BLACK);
		}
	}
	if ((mouseX > 50) && (mouseX < 250))
	{
		if ((mouseY > WindowHeight - 190) && (mouseY < WindowHeight - 90))
		{
			DrawRectangle(50, WindowHeight - 190, 200, 100, LIGHTGRAY);
			DrawText("Main Menu", 50 + (200 - MeasureText("Main Menu", 30)) / 2, WindowHeight - 155, 30, BLACK);
		}
	}
}
void WindowSudoku::handleClick()
{
	if (IsMouseButtonPressed(0))
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		if ((mouseX > topLeftX) && (mouseX < (topLeftX + (spaceBetweenLines * 9))))
		{
			if ((mouseY > topLeftY) && (mouseY < (topLeftY + (spaceBetweenLines * 9))))
			{
				int col = (mouseX - topLeftX) / spaceBetweenLines;
				int row = (mouseY - topLeftY) / spaceBetweenLines;
				if (numbers[row][col]->tryAction())
				{
					currentClickCol = col;
					currentClickRow = row;
				}
			}
			else
			{
				currentClickRow = -1;

			}
		}
		else
		{
			currentClickCol = -1;
			if ((mouseX > WindowWidth - 250) && (mouseX < WindowWidth - 50))
			{
				if ((mouseY > WindowHeight - 190) && (mouseY < WindowHeight - 90))
				{
					checkBackground = true;
				}
			}
			if ((mouseX > 50) && (mouseX < 250))
			{
				if ((mouseY > WindowHeight - 190) && (mouseY < WindowHeight - 90))
				{
					mainmenu = true;
				}
			}
		}
	}
	if ((currentClickRow != -1) && (currentClickCol != -1))
	{
		DrawRectangle(topLeftX + currentClickCol * spaceBetweenLines, topLeftY + currentClickRow * spaceBetweenLines, spaceBetweenLines, spaceBetweenLines, MAROON);
	}
	
}
void WindowSudoku::handleEnter()
{
	if ((currentClickRow != -1) && (currentClickCol != -1))
	{
		int keyPressed = GetKeyPressed();
		if (keyPressed >= 49 && keyPressed <= 57)
		{
			setNum(currentClickRow, currentClickCol, keyPressed - 48);
		}
		else if (keyPressed == 259)
		{
			setNum(currentClickRow, currentClickCol, 0);
		}
	}
}
void WindowSudoku::checkSudoku()
{
	vector<vector<int>> sudokuFilled = Sudoku1.getSudokuComplete();
	int col, row;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudokuFilled[i][j] != numbers[i][j]->getNumber())
			{
				DrawRectangle(topLeftX + j * spaceBetweenLines, topLeftY + i * spaceBetweenLines, spaceBetweenLines, spaceBetweenLines, RED);
			}
			else
			{
				DrawRectangle(topLeftX + j * spaceBetweenLines, topLeftY + i * spaceBetweenLines, spaceBetweenLines, spaceBetweenLines, GREEN);
			}
		}
	}
}
bool WindowSudoku::getMenuState()
{
	return mainmenu;
}
bool WindowSudoku::getQuitState()
{
	return quit;
}
void WindowSudoku::drawMenu()
{
	DrawText("Sudoku Masterrace", (WindowWidth - MeasureText("Sudoku Masterrace", 70)) / 2, 100, 70, DARKBLUE);
	DrawRectangle((WindowWidth-300)/2,250,300,150,BLUE);
	DrawText("New Game", (WindowWidth - MeasureText("New Game", 50)) / 2, 300, 50, WHITE);
	DrawRectangle((WindowWidth - 300) / 2, 450, 300, 150, BLUE);
	DrawText("Quit Game", (WindowWidth - MeasureText("Quit Game", 50)) / 2, 500, 50, WHITE);
}
void WindowSudoku::handleMenuHover()
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	if (mouseX > ((WindowWidth - 300) / 2) && mouseX < (((WindowWidth - 300) / 2) + 300))
	{
		if (mouseY > 250 && mouseY < 400)
		{
			DrawRectangle((WindowWidth - 300) / 2, 250, 300, 150, LIGHTGRAY);
			DrawText("New Game", (WindowWidth - MeasureText("New Game", 50)) / 2, 300, 50, BLACK);
		}
		else if (mouseY > 450 && mouseY < 600)
		{
			DrawRectangle((WindowWidth - 300) / 2, 450, 300, 150, LIGHTGRAY);
			DrawText("Quit Game", (WindowWidth - MeasureText("Quit Game", 50)) / 2, 500, 50, BLACK);
		}
	}
}
void WindowSudoku::handleMenuClick()
{
	if (IsMouseButtonPressed(0))
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		if (mouseX > ((WindowWidth - 300) / 2) && mouseX < (((WindowWidth - 300) / 2) + 300))
		{
			if (mouseY > 250 && mouseY < 400)
			{
				initFields();
				Timer1.resetTimer();
				mainmenu = false;
			}
			else if (mouseY > 450 && mouseY < 600)
			{
				quit = true;
			}
		}
	}
	
}
