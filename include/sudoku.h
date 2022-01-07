#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED;
extern int SIZE_ROWS, SIZE_COLUMNS;

typedef struct Box
{
    struct Box *next;
} Box;

typedef struct Square
{
    int number;
    int possible[9];
    int possiblityNbr;
    Box *box;
    int row;
    int column;
} Square;

int **createPuzzle();
void printPuzzle(Square ***puzzle);
int solveSquare(Square *square);
Square ***setUpPuzzle(int **puzzle);
void checkPuzzle(Square ***sudoku);
int updateSudoku(Square ***sudoku, int row, int column);

#endif