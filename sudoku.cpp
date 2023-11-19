#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "sudoku.h"

using namespace std;
void GridS::swapRows(int row1, int row2)
{
    int temp;
    for (int i = 0; i < 9; i++)
    {
        temp = finalSudoku[row1][i];
        finalSudoku[row1][i] = finalSudoku[row2][i];
        finalSudoku[row2][i] = temp;
    }
}

    void GridS::swapColumns(int col1, int col2)
    {
        int temp;
        for (int i = 0; i < 9; i++)
        {
            temp = finalSudoku[i][col1];
            finalSudoku[i][col1] = finalSudoku[i][col2];
            finalSudoku[i][col2] = temp;
        }
    }

    void GridS::permutations()
    {
        srand(time(NULL));
        for (int i = 0; i < 3; i++)
        {
            vector<int> tempRows = { 1,2,3 };
            vector<int> tempColumns = { 1,2,3 };
            int permModeRows = rand() % 5 + 1;
            int permModeColumns = rand() % 5 + 1;
            vector<int> finishRows = permutationVector[permModeRows];
            vector<int> finishColumns = permutationVector[permModeColumns];
            for (int j = 0; j < 3; j++)
            {
                if (tempRows[j] != finishRows[j])
                {
                    swapRows((finishRows[0] - 1) + i * 3, (tempRows[0] - 1) + i * 3);
                    tempRows[j] = finishRows[j];
                }
            }
            for (int j = 0; j < 3; j++)
            {
                if (tempColumns[j] != finishColumns[j])
                {
                    swapColumns((finishColumns[0] - 1) + i * 3, (tempColumns[0] - 1) + i * 3);
                    tempColumns[j] = finishColumns[j];
                }
            }

        }
    }

    void GridS::numberSwap(int times)
    {
        srand(time(NULL));
        int num1, num2;
        for (int i = 0; i < times; i++)
        {
            num1 = rand() % 9 + 1;
            num2 = rand() % 9 + 1;
            while (num2 == num1)
            {
                num2 = rand() % 9 + 1;
            }
            for (int rows = 0; rows < 9; rows++)
            {
                for (int cols = 0; cols < 9; cols++)
                {
                    if (finalSudoku[rows][cols] == num1)
                    {
                        finalSudoku[rows][cols] = num2;
                    }
                    else if (finalSudoku[rows][cols] == num2)
                    {
                        finalSudoku[rows][cols] = num1;
                    }

                }
            }
        }
        sudokuWithHoles = finalSudoku;
    }


    bool GridS::isUnbiasedFun(int row, int col)
    {
        vector<int> numbersRow = { 1,2,3,4,5,6,7,8,9 };
        vector<int> numbersCol = { 1,2,3,4,5,6,7,8,9 };
        vector<int> numbersSquare = { 1,2,3,4,5,6,7,8,9 };
        int count = 0;
        for (int i = 0; i < 9; i++)
        {
            if (i != row)
            {
                for (int counter = 0; counter < 9; counter++)
                {
                    if (finalSudoku[row][i] == numbersRow[counter])
                    {
                        count++;
                        break;
                    }
                }
            }
        }

        if (count == 8)
        {
            return true;
        }
        count = 0;
        for (int i = 0; i < 9; i++)
        {
            if (i != col)
            {
                for (int counter = 0; counter < 9; counter++)
                {
                    if (finalSudoku[i][col] == numbersCol[counter])
                    {
                        count++;
                        break;
                    }
                }
            }
        }
        if (count == 0)
        {
            return true;
        }
        count = 0;
        int squareRow = row / 3, squareCol = col / 3;
        for (int i = squareCol; i < squareCol + 3; i++)
        {
            for (int j = squareRow; j < squareRow + 3; j++)
            {
                if (i != col && j != row)
                {
                    for (int counter = 0; counter < 9; counter++)
                    {
                        if (finalSudoku[i][j] == numbersSquare[counter])
                        {
                            count++;
                            break;
                        }
                    }
                }
            }
        }
        if (count == 8)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    void GridS::deleteRandInt(int times)
    {
        srand(time(NULL));
        int row, col;
        bool isUnbiased;
        for (int i = 0; i < times; i++)
        {
            do
            {
                row = rand() % 9;
                col = rand() % 9;
                if (sudokuWithHoles[row][col] == 0)
                {
                    isUnbiased = false;
                }
                else
                {
                    isUnbiased = isUnbiasedFun(row, col);
                }
            } while (!isUnbiased);
            sudokuWithHoles[row][col] = 0;
        }
    }

    vector<vector<int>> GridS::getSudokuWithHoles()
    {
        return sudokuWithHoles;
    }
    vector<vector<int>> GridS::getSudokuComplete()
    {
        return finalSudoku;
    }
    int GridS::getNumberSWH(int row, int col)
    {
        return sudokuWithHoles[row][col];
    }

    int GridS::getNumberSC(int row, int col)
    {
        return finalSudoku[row][col];
    }
