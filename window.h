#pragma once
#include <raylib.h>
#include <cstring>
#include <string>
#include "sudoku.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class Field
{
private:
	int number;
public:
	virtual bool tryAction();
	void setNumber(int num);
	int getNumber();
};
class FieldEmpty : public Field
{
public:
	FieldEmpty(int num);
	bool tryAction();

};
class FieldFilled : public Field
{
public:
	FieldFilled(int num);
	bool tryAction();
	void setNum(int num);
};
class Timer
{
private:
	int seconds;
	int minutes;
	string minutesText;
	string secondsText;
	string timeNow;
	int textLength;
	int secSinceClose = 0;
	int minSinceClose = 0;
public:
	void showTime(int posX, int posY);
	void resetTimer();
};
class WindowSudoku
{
private:
	Timer Timer1;
	Field*** numbers;
	GridS Sudoku1;
	const int WindowWidth = 1280;
	const int WindowHeight = 720;
	int spaceBetweenLines = 60;
	int lineLength = 60 * 9;
	int topLeftX = (WindowWidth - lineLength) / 2;
	int topRightX = topLeftX + lineLength;
	int topLeftY = (WindowHeight - lineLength) / 2;
	int botLeftY = topLeftY + lineLength;
	int currentClickRow = -1;
	int currentClickCol = -1;
	bool checkBackground = false;
	bool mainmenu = true;
	bool quit = false;

public:
	int getWindowWidth();
	int getWindowHeight();
	void drawPlane();
	void drawNumber(int posX, int posY, string number, int fontSize, Color color);
	void drawNumbers();
	void initFields();
	void displayTime(int posX, int posY);
	void handleHover();
	void handleButtonHover();
	void handleClick();
	void handleEnter();
	void setNum(int row, int col, int num);
	void checkSudoku();
	bool getMenuState();
	bool getQuitState();
	void drawMenu();
	void handleMenuHover();
	void handleMenuClick();

};