
#include "mine-sweeper-program.h"

int main(int aAmount, char* arguments[])
{
	srand(time(NULL));

	int height = 10, width = 10, mines = 20;
	Square** mineField = create_square_matrix(height, width);

	if(!generate_mine_field(mineField, height, width, mines))
	{
		free(mineField); return false;
	}

	if(mine_sweeper_game(mineField, height, width))
	{
		printf("Congratulations!\n");
	}

	unlock_field_mines(mineField, height, width);

	display_mine_field(mineField, height, width);

	free(mineField); return false;
}

Square** create_square_matrix(int height, int width)
{
	Square** mineField = malloc(sizeof(Square*) * height);
	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		*(mineField + hIndex) = malloc(sizeof(Square) * width);
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			Square current = {false, false, 0};
			*(*(mineField + hIndex) + wIndex) = current;
		}
	}
	return mineField;
}

int create_random_integer(int minimum, int maximum)
{
	return (rand() % (maximum - minimum) + minimum);
}

int** every_matrix_indexes(int height, int width)
{
	int total = (height * width);
	int** indexes = malloc(sizeof(int*) * total);
	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			int index = (hIndex * width) + wIndex;

			*(indexes + index) = malloc(sizeof(int) * 2);
			*(*(indexes + index) + 0) = hIndex;
			*(*(indexes + index) + 1) = wIndex;
		}
	}
	return indexes;
}

bool delete_matrix_array(int** matrix, int length, int start)
{
	if(start < 0 || start >= length) return false;

	for(int index = start; index < (length - 1); index = index + 1)
	{
		*(matrix + index) = *(matrix + index + 1);
	}

	return true;
}

bool generate_field_mines(Square** mineField, int height, int width, int mines)
{
	int total = (height * width);
	if(mines > total) return false;

	int** indexes = every_matrix_indexes(height, width);

	for(int index = 0; index < mines; index = index + 1)
	{
		int random = create_random_integer(0, total);
		int hIndex = *(*(indexes + random) + 0);
		int wIndex = *(*(indexes + random) + 1);

		mineField[hIndex][wIndex].isMine = true;

		if(!delete_matrix_array(indexes, total, random))
		{
			free(indexes); return false;
		}

		total = (total - 1);
	}

	free(indexes); return true;
}

int adjacent_field_mines(Square** mineField, int position[], int tHeight, int tWidth)
{
	int adjacent = 0;
	int height = *(position + 0), width = *(position + 1);

	for(int hIndex = (height - 1); hIndex <= (height + 1); hIndex = hIndex + 1)
	{
		for(int wIndex = (width - 1); wIndex <= (width + 1); wIndex = wIndex + 1)
		{
			if((hIndex < 0 || hIndex >= tHeight) || (wIndex < 0 || wIndex >= tWidth))
			{
				continue;
			}

			if(mineField[hIndex][wIndex].isMine)
			{
				adjacent = (adjacent + 1);
			}
		}
	}
	return adjacent;
}

bool generate_mine_field(Square** mineField, int height, int width, int mines)
{
	if(!generate_field_mines(mineField, height, width, mines))
	{
		return false;
	}

	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].isMine)
			{
				continue;
			}
			int position[] = {hIndex, wIndex};
			int adjacent = adjacent_field_mines(mineField, position, height, width);
			mineField[hIndex][wIndex].adjacent = adjacent;
		}
	}
	return true;
}

bool mine_field_cleared(Square** mineField, int height, int width)
{
	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].isMine) continue;

			if(mineField[hIndex][wIndex].visable == false)
			{
				return false;
			}
		}
	}
	return true;
}

void show_number_square(int adjacent)
{
	if(adjacent >= 8) printf("\033[%dm8 \033[0m", 31);
	printf("\033[%dm%d \033[0m", adjacent + 30, adjacent);
}

void display_mine_field(Square** mineField, int height, int width)
{
	printf("  ");
	for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
	{
		char string[10]; sprintf(string, "%d", wIndex);
		printf("%c ", string[strlen(string) - 1]);
	}
	printf("\n");

	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		char string[10]; sprintf(string, "%d", hIndex);
		printf("%c ", string[strlen(string) - 1]);

		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].visable == false)
			{
				printf("+ ");
			}
			else if(mineField[hIndex][wIndex].isMine)
			{
				printf("@ ");
			}
			else if(mineField[hIndex][wIndex].adjacent == 0)
			{
				printf(". ");
			}
			else
			{
				show_number_square(mineField[hIndex][wIndex].adjacent);
			}
		}
		printf("\n");
	}
}

bool unlock_field_square(Square** mineField, int position[], int tHeight, int tWidth)
{
	int height = *(position + 0), width = *(position + 1);

	mineField[height][width].visable = true;

	if(mineField[height][width].isMine)
	{
		return false;
	}

	if(mineField[height][width].adjacent == 0)
	{
		for(int hIndex = (height - 1); hIndex <= (height + 1); hIndex = hIndex + 1)
		{
			for(int wIndex = (width - 1); wIndex <= (width + 1); wIndex = wIndex + 1)
			{
				if((hIndex < 0 || hIndex >= tHeight) || (wIndex < 0 || wIndex >= tWidth))
				{
					continue;
				}

				if(mineField[hIndex][wIndex].visable == true) continue;

				int newPos[] = {hIndex, wIndex};

				if(!unlock_field_square(mineField, newPos, tHeight, tWidth))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool mine_sweeper_game(Square** mineField, int height, int width)
{
	while(!mine_field_cleared(mineField, height, width))
	{
		display_mine_field(mineField, height, width);

		int position[] = {-1, -1};
		printf("Input Position: ");
		if(scanf("%d %d", &position[0], &position[1]) != 2) continue;

		int hIndex = *(position + 0), wIndex = *(position + 1);

		if((hIndex < 0 || hIndex >= height) || (wIndex < 0 || wIndex >= width))
		{
			continue;
		}

		if(!unlock_field_square(mineField, position, height, width))
		{
			return false;
		}
	}
	return true;
}

void unlock_field_mines(Square** mineField, int height, int width)
{
	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].isMine)
			{
				mineField[hIndex][wIndex].visable = true;
			}
		}
	}
}
