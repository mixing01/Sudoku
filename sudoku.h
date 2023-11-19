#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;
class GridS
{
private:
    vector<vector<int>> sudokuExample = {
        {1,2,3,6,7,8,9,4,5},
        {5,8,4,2,3,9,7,6,1},
        {9,6,7,1,4,5,3,2,8},
        {3,7,2,4,6,1,5,8,9},
        {6,9,1,5,8,3,2,7,4},
        {4,5,8,7,9,2,6,1,3},
        {8,3,6,9,2,4,1,5,7},
        {2,1,9,8,5,7,4,3,6},
        {7,4,5,3,1,6,8,9,2},
    };
    vector<vector<int>> finalSudoku = sudokuExample;
    vector<vector<int>> sudokuWithHoles;
    vector<vector<int>> permutationVector = {
        {1,2,3},
        {1,3,2},
        {2,1,3},
        {2,3,1},
        {3,1,2},
        {3,2,1}
    };

public:
    void swapRows(int row1, int row2);
    void swapColumns(int col1, int col2);
    

    void permutations();

    void numberSwap(int times);

    bool isUnbiasedFun(int row, int col);
    
    void deleteRandInt(int times);

    int getNumberSWH(int row, int col);

    int getNumberSC(int row, int col);
    
    vector<vector<int>> getSudokuWithHoles();
    vector<vector<int>> getSudokuComplete();
};