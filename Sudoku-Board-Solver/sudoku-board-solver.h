
#ifndef SUDOKU_BOARD_SOLVER
#define SUDOKU_BOARD_SOLVER

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

bool solve_sudoku_board(int**);

bool empty_sudoku_diget(int*, int*, int**);

bool sudoku_board_valid(int**);

bool sudoku_horizon_valid(int**, int);

bool sudoku_vertic_valid(int**, int);

bool sudoku_square_valid(int**, int, int);

void display_sudoku_board(int**);

int* create_integer_array(int);

int** create_integer_matrix(int, int);

bool extract_sudoku_board(int**, char[]);

#endif
