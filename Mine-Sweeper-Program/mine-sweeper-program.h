
#ifndef MINE_SWEEPER_PROGRAM
#define MINE_SWEEPER_PROGRAM

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

#include <string.h>

typedef struct Square
{
	bool visable;
	bool isMine;
	int adjacent;
} Square;

Square** create_square_matrix(int, int);

bool generate_mine_field(Square**, int, int, int);

bool mine_sweeper_game(Square**, int, int);

void unlock_field_mines(Square**, int, int);

void display_mine_field(Square**, int, int);

#endif
