
#include "sudoku-board-solver.h"

/* THIS PROGRAM IS A SUDOKU SOLVER - MADE BY H4PE0N */

int main(int aAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[] = "sudoku-board-example.txt";
	int** sudoku = create_integer_matrix(9, 9);

	if(!extract_sudoku_board(sudoku, filename))
	{
		free(sudoku); return true;
	}

	display_sudoku_board(sudoku); printf("\n");

	if(!solve_sudoku_board(sudoku))
	{
		printf("Not Solved!\n");
	}
	display_sudoku_board(sudoku);

	free(sudoku); return false;
}

bool solve_sudoku_board(int** sudoku)
{
	if(!sudoku_board_valid(sudoku))
	{
		return false;
	}
	int height, width;

	if(!empty_sudoku_diget(&height, &width, sudoku))
	{
		return true;
	}

	for(int diget = 1; diget <= 9; diget = diget + 1)
	{
		*(*(sudoku + height) + width) = diget;
		if(solve_sudoku_board(sudoku))
		{
			return true;
		}
	}
	*(*(sudoku + height) + width) = 0;
	return false;
}

bool extract_sudoku_board(int** sudoku, char filename[])
{
	FILE* fPointer = fopen(filename, "r");

	if(fPointer == NULL)
	{
		return false;
	}
	char buffer[200];
	for(int hIndex = 0; hIndex < 9; hIndex = hIndex + 1)
	{
		if(fgets(buffer, 200, fPointer) == NULL)
		{
			return false;
		}
		for(int wIndex = 0; wIndex < 9; wIndex = wIndex + 1)
		{
			int height = hIndex, width = (wIndex * 2);
			int diget = atoi(buffer + width);
			*(*(sudoku + hIndex) + wIndex) = diget;
		}
	}
	fclose(fPointer);

	return true;
}

bool empty_sudoku_diget(int* height, int* width, int** sudoku)
{
	for(int hIndex = 0; hIndex < 9; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < 9; wIndex = wIndex + 1)
		{
			if(*(*(sudoku + hIndex) + wIndex) == 0)
			{
				*height = hIndex, *width = wIndex;
				return true;
			}
		}
	}
	return false;
}

bool sudoku_board_valid(int** sudoku)
{
	for(int index = 0; index < 9; index = index + 1)
	{
		if(!sudoku_horizon_valid(sudoku, index))
		{
			return false;
		}
		if(!sudoku_vertic_valid(sudoku, index))
		{
			return false;
		}
	}
	for(int hIndex = 0; hIndex < 9; hIndex = hIndex + 3)
	{
		for(int wIndex = 0; wIndex < 9; wIndex = wIndex + 3)
		{
			if(!sudoku_square_valid(sudoku, hIndex, wIndex))
			{
				return false;
			}
		}
	}
	return true;
}

bool sudoku_horizon_valid(int** sudoku, int height)
{
	int* digets = create_integer_array(10);
	for(int width = 0; width < 9; width = width + 1)
	{
		int current = *(*(sudoku + height) + width);
		if(current != 0 && *(digets + current) == 1)
		{
			free(digets);
			return false;
		}
		*(digets + current) = 1;
	}
	free(digets);
	return true;
}

bool sudoku_vertic_valid(int** sudoku, int width)
{
	int* digets = create_integer_array(10);
	for(int height = 0; height < 9; height = height + 1)
	{
		int current = *(*(sudoku + height) + width);
		if(current != 0 && *(digets + current) == 1)
		{
			free(digets);
			return false;
		}
		*(digets + current) = 1;
	}
	free(digets);
	return true;
}

bool sudoku_square_valid(int** sudoku, int height, int width)
{
	int* digets = create_integer_array(10);
	int sHeight = (int) (height / 3) * 3;
	int sWidth = (int) (width / 3) * 3;
	for(int hIndex = sHeight; hIndex < (sHeight + 3); hIndex = hIndex + 1)
	{
		for(int wIndex = sWidth; wIndex < (sWidth + 3); wIndex = wIndex + 1)
		{
			int current = *(*(sudoku + hIndex) + wIndex);
			if(current != 0 && *(digets + current) == 1)
			{
				free(digets);
				return false;
			}
			*(digets + current) = 1;
		}
	}
	free(digets);
	return true;
}

void display_sudoku_board(int** sudoku)
{
	for(int height = 0; height < 9; height = height + 1)
	{
		for(int width = 0; width < 9; width = width + 1)
		{
			printf("%d ", *(*(sudoku + height) + width));
		}
		printf("\n");
	}
}

int* create_integer_array(int length)
{
	int* array = malloc(sizeof(int) * length);
	for(int index = 0; index < length; index = index + 1)
	{
		*(array + index) = 0;
	}
	return array;
}

int** create_integer_matrix(int height, int width)
{
	int** matrix = malloc(sizeof(int*) * height);
	for(int index = 0; index < height; index = index + 1)
	{
		*(matrix + index) = create_integer_array(width);
	}
	return matrix;
}
