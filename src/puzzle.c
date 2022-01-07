#include "sudoku.h"

Square ***setUpPuzzle(int **puzzle)
{
    Square ***sudoku;
    int i, j, k;
    sudoku = (Square ***)malloc(sizeof(Square **) * 9);
    for (i = 0; i < SIZE_ROWS; i++)
    {
        sudoku[i] = (Square **)malloc(sizeof(Square *) * 9);
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            sudoku[i][j] = (Square *)malloc(sizeof(Square));
            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->possiblityNbr = 9;
            for (k = 0; k < SIZE_COLUMNS; k++)
            {
                sudoku[i][j]->possible[k] = 0;
            }
        }
    }
    // start the puzzle
    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            // if a case has a number -> then make the nbr not available in the row and the column
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->possiblityNbr = 0;
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return sudoku;
}

int updateSudoku(Square ***sudoku, int row, int column)
{
    int i, number = sudoku[row][column]->number;

    for (i = 0; i < SIZE_ROWS; i++)
    {
        // if the number is available in the column, then:
        if (sudoku[i][column]->possible[number - 1] == 0)
        {
            // decrease the possibility number
            sudoku[i][column]->possiblityNbr--;
        }
        // and make it not available
        sudoku[i][column]->possible[number - 1] = 1;
    }
    for (i = 0; i < SIZE_COLUMNS; i++)
    {
        // if the number is available in the row, then:
        if (sudoku[row][i]->possible[number - 1] == 0)
        {
            // decrease the possibility number
            sudoku[row][i]->possiblityNbr--;
        }
        // and make it not available
        sudoku[row][i]->possible[number - 1] = 1;
    }
}

int **createPuzzle()
{
    int **puzzle;
    int i, j;
    int array[9][9] = {0, 1, 9, 8, 0, 2, 0, 0, 0,
                       4, 7, 0, 6, 9, 0, 0, 0, 1,
                       0, 0, 0, 4, 0, 0, 0, 9, 0,
                       8, 9, 4, 5, 0, 7, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 2, 0, 1, 9, 5, 8,
                       0, 5, 0, 7, 0, 6, 0, 0, 0,
                       6, 0, 0, 3, 2, 8, 0, 7, 9,
                       0, 0, 0, 1, 0, 0, 8, 6, 0};

    puzzle = (int **)malloc(sizeof(int *) * 9);

    for (i = 0; i < SIZE_ROWS; i++)
    {
        puzzle[i] = (int *)malloc(sizeof(int) * 9);
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void checkPuzzle(Square ***sudoku)
{
    int i, j, x;
    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->possiblityNbr == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
            }
        }
    }
}

void printPuzzle(Square ***puzzle)
{
    int i, j;
    printf("-----------------\n");
    for (i = 0; i < SIZE_ROWS; i++)
    {

        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            printf("%d ", puzzle[i][j]->number);
            if (j == 2 || j == 5)
            {
                printf("\t");
            }
        }
        printf("\n");
        if (i == 2 || i == 5)
        {
            printf("\n");
        }
    }
    printf("-----------------\n");
}