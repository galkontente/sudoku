#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"

Array*** PossibleDigits(short sudokuBoard[][SIZE]) //1st function
{
	int i, j;
	int sizeOfPoss = 0;
	Array*** res;
	res = (Array***)malloc(sizeof(Array**) * SIZE); // make 9 rowse
	checkMemory(res);
	for (i = 0; i < SIZE; i++)
	{
		res[i] = (Array**)malloc(sizeof(Array*) * SIZE); // make 9 cols
		checkMemory(res);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (sudokuBoard[i][j] != -1)
			{
				res[i][j] = NULL;
			}
			else //if its -1 (means its an empty space)
			{
				res[i][j] = createEfficiantPoss(sudokuBoard, i, j); //i is the rows, j for cols
			}
		}
	}

	return res;
}

Array* createEfficiantPoss(short sudokuBoard[][SIZE], int row, int col)
{
	int i, counter = 0, ind;
	Array* res;
	res = (Array*)malloc(sizeof(Array));
	checkMemory(res);
	int arr[SIZE] = { 0 };					  //every spot for every number, with the number 0.
	checkColPoss(arr, sudokuBoard, col);	  // every value, adds +1 to arr[value]
	checkRowPoss(arr, sudokuBoard, row);	  // every value, adds +1 to arr[value]
	checkBoxPoss(arr, sudokuBoard, row, col); // every value, adds +1 to arr[value]
	for (i = 0; i < SIZE; i++)				  // counts how many numbers we are left with thats still 0 (possible to use)
	{
		if (arr[i] == 0)
			counter++;
	}
	res->arr = (short*)malloc(sizeof(short) * counter);
	checkMemory(res->arr);
	res->size = counter;
	for (i = 0, ind = 0; i < SIZE; i++) // fills the numbers into place
	{
		if (arr[i] == 0)
		{
			res->arr[ind] = (short)(i + 1);
			ind++;
		}
	}

	return res;
}
void checkColPoss(int arr[], short sudokuBoard[][SIZE], int col)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[i][col] != -1)
			arr[sudokuBoard[i][col] - 1]++;
	}
}

void checkRowPoss(int arr[], short sudokuBoard[][SIZE], int row)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (sudokuBoard[row][i] != -1)
			arr[sudokuBoard[row][i] - 1]++;
	}
}
void checkBoxPoss(int arr[], short sudokuBoard[][SIZE], int row, int col)
{
	int startRow = row;
	int startCol = col;
	int i, j;
	while (startRow % 3 != 0) //move to the up side of the Box
		startRow--;
	while (startCol % 3 != 0) //move to the left of the Box
		startCol--;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			sudokuBoard[startRow + i][startCol + j] += sudokuBoard[startRow + i][startCol + j] != -1 ? 1 : 0;
	}
}

void sudokoPrintBoard(short sudokuBoard[][SIZE])
{
	int i, j;
	printf("  |");
	for (j = 0; j < SIZE; j++)
		(j % 3 == 2 && j != 8) ? printf("%2d|", j) : printf("%2d", j);

	printf("\n");
	for (i = 0; i < SIZE; i++)
	{
		if (i % 3 == 0)
			printf("-----------------------\n");
		printf(" %d", i);
		for (j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				printf("|");
			if (sudokuBoard[i][j] != -1)
				printf("%2d", sudokuBoard[i][j]);
			else
				printf("%2c", '-');

		}
		printf("\n");
	}
	printf("-----------------------\n");
}

int FillBoard(short board[][SIZE], Array*** possibilities)
{
	int res, x, y, choice;
	int tempArrSize;
	int i;
	int flagLegitInput = 0;
	res = OneStage(board, possibilities, &x, &y);
	while (res == NOT_FINISH)
	{
		sudokoPrintBoard(board);
		tempArrSize = possibilities[x][y]->size;
		while (flagLegitInput == 0)
		{
			printf("What value do you want to put at (%d,%d)?\n", x, y);
			printf("The options are: ");
			for (i = 0; i < tempArrSize; i++)
				printf("%d ", possibilities[x][y]->arr[i]);
			printf(".\n");
			scanf("%d", &choice);
			for (i = 0; i < tempArrSize; i++)
				if (possibilities[x][y]->arr[i] == choice)
				{
					flagLegitInput = 1;
					break;
				}
			if (flagLegitInput != 1)
				printf("INVALID INPUT.\n");
		}

		board[x][y] = choice;
		free(possibilities[x][y]->arr);
		free(possibilities[x][y]);
		possibilities[x][y] = NULL;					   //now it points on NULL
		updateRow(x, choice, board, possibilities);	   //updates to the current relevant poss in the point's row
		updateCol(y, choice, board, possibilities);	   //updates to the current relevant poss in the point's col
		updateBox(x, y, choice, board, possibilities); //updates to the current relevant poss in the point's box
		res = OneStage(board, possibilities, &x, &y);
		flagLegitInput = 0;
	}
	if (res == FINISH_FAILURE)
		res = FAIL;

	else if (res == FINISH_SUCCESS)
		res = FILLED;

	return res;
}

int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y)
{
	int i, j;
	short data;
	int stop = 0;
	int unfilled;
	int unsolvable = 0;
	int minOptions, minX, minY;
	while (stop == 0)
	{
		minOptions = SIZE;
		stop = 1;
		unfilled = 0;
		for (i = 0; i < SIZE; i++) //rows
		{
			for (j = 0; j < SIZE; j++) //cols
			{
				if (board[i][j] == -1) //empty space
				{
					unfilled++;
					if (possibilities[i][j] == NULL) // empty space and no options !
					{
						unsolvable = 1;
						break;
					}
					else if (possibilities[i][j]->size == 1) // empty space with only 1 option
					{
						data = possibilities[i][j]->arr[0];
						board[i][j] = data;
						//update possibily (free, and box row col)
						free(possibilities[i][j]->arr);
						free(possibilities[i][j]);
						possibilities[i][j] = NULL;
						stop = 0;
						updateRow(i, data, board, possibilities);
						updateCol(j, data, board, possibilities);
						updateBox(i, j, data, board, possibilities);
					}
					else // empty space with nore then 1 option
					{
						if (possibilities[i][j]->size < minOptions)
						{
							minOptions = possibilities[i][j]->size;
							minX = i;
							minY = j;
						}
					}
				}
			}
		}
	}

	if (unsolvable == 1)
		return FINISH_FAILURE;

	else if (unfilled == 0)
		return FINISH_SUCCESS;

	else if (stop == 1 && unfilled > 0)
	{
		*x = minX;
		*y = minY;
		return NOT_FINISH;
	}
	else
		printf("What?");
}

void updateRow(int row, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's row
{
	int i, arrInd, removeInd;
	unsigned short size;
	for (i = 0; i < SIZE; i++)
	{
		if (possibilities[row][i] != NULL)
		{
			size = possibilities[row][i]->size;
			if (num < possibilities[row][i]->arr[0] || num > possibilities[row][i]->arr[size - 1])
				continue;
			else if (size == 1 && possibilities[row][i]->arr[0] == num)
			{
				free(possibilities[row][i]->arr);
				free(possibilities[row][i]);
				possibilities[row][i] = NULL;
			}
			else
			{
				for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
				{
					if (num == possibilities[row][i]->arr[arrInd]) //when we find him
					{
						for (removeInd = arrInd; removeInd < size - 1; removeInd++)
							possibilities[row][i]->arr[removeInd] = possibilities[row][i]->arr[removeInd + 1];

						possibilities[row][i]->arr = (short*)realloc(possibilities[row][i]->arr, sizeof(short) * (size - 1));
						checkMemory(possibilities[row][i]->arr);
						possibilities[row][i]->size = size - 1;
						break;
					}
				}
			}
		}
	}
}

void updateCol(int col, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's coll
{
	int i, arrInd, removeInd;
	unsigned short size;
	for (i = 0; i < SIZE; i++)
	{
		if (possibilities[i][col] != NULL)
		{
			size = possibilities[i][col]->size;
			if (num < possibilities[i][col]->arr[0] || num > possibilities[i][col]->arr[size - 1])
				continue;
			else if (size == 1 && possibilities[i][col]->arr[0] == num)
			{
				free(possibilities[i][col]->arr);
				free(possibilities[i][col]);
				possibilities[i][col] = NULL;
			}
			else
			{
				for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
				{
					if (num == possibilities[i][col]->arr[arrInd]) //when we find him
					{
						for (removeInd = arrInd; removeInd < size - 1; removeInd++)
						{
							possibilities[i][col]->arr[removeInd] = possibilities[i][col]->arr[removeInd + 1];
						}
						possibilities[i][col]->arr = (short*)realloc(possibilities[i][col]->arr, sizeof(short) * (size - 1));
						checkMemory(possibilities[i][col]->arr);
						possibilities[i][col]->size = size - 1;
						break;
					}
				}
			}
		}
	}
}

void updateBox(int row, int col, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's in the box
{
	int i, j, arrInd, removeInd;
	unsigned short size;
	int startRow = row, startCol = col;
	while (startRow % 3 != 0)
		startRow--;
	while (startCol % 3 != 0)
		startCol--;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (possibilities[startRow + i][startCol + j] != NULL)
			{
				size = possibilities[startRow + i][startCol + j]->size;
				if (num < possibilities[startRow + i][startCol + j]->arr[0] || num > possibilities[startRow + i][startCol + j]->arr[size - 1])
					continue;
				else if (size == 1 && possibilities[startRow + i][startCol + j]->arr[0] == num)
				{
					free(possibilities[startRow + i][startCol + j]->arr);
					free(possibilities[startRow + i][startCol + j]);
					possibilities[startRow + i][startCol + j] = NULL;
				}
				else
				{
					for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
					{
						if (num == possibilities[startRow + i][startCol + j]->arr[arrInd]) //when we find him
						{
							for (removeInd = arrInd; removeInd < size - 1; removeInd++)
							{
								possibilities[startRow + i][startCol + j]->arr[removeInd] = possibilities[startRow + i][startCol + j]->arr[removeInd + 1];
							}
							possibilities[startRow + i][startCol + j]->arr = (short*)realloc(possibilities[startRow + i][startCol + j]->arr, sizeof(short) * (size - 1));
							checkMemory(possibilities[startRow + i][startCol + j]->arr);
							possibilities[startRow + i][startCol + j]->size = size - 1;
							break;
						}
					}
				}
			}
		}
	}
}

void checkMemory(void* check) //checks succes of memeory allocation
{
	if (check == NULL)
		exit(1);
}

void initializeBoard(playerDetails* player, int* numOfCellsFirstFilled)
{
	Array*** tempPossibilities;
	int i, j, numOfCellsPicked;

	for (i = 0; i < SIZE; i++) //resets the board by putting -1 in every cell
	{
		for (j = 0; j < SIZE; j++)
		{
			player->sudokuBoard[i][j] = -1;
		}

	}

	tempPossibilities = PossibleDigits(player->sudokuBoard); //resets the possibilities of each cell
	player->possibilities = tempPossibilities;
	generateBoard(player->sudokuBoard, player->possibilities, &numOfCellsPicked); //generates a board for this player
	*numOfCellsFirstFilled = numOfCellsPicked;									  //returns the ampont of filled cells in the initial board
}

void generateBoard(short board[][SIZE], Array*** possibilities, int* numOfCellsPicked)
{
	int i = 0, numOfCells = 0, lottoryNumForList, lottoryNumForBoard;
	int x, y, data;
	LIST lst;
	LNODE* cellPtrToBeRemoved;
	makeEmptyList(&lst);
	int size;
	lst = buildListOfCord(&size);

	//in order to get different nums in the call for random functionn
	numOfCells = (rand() % 20) + 1; //randomly picks a num from 1 to 20 and it will be the num of cells first filld

	for (i = 0; i < numOfCells; i++)
	{
		lottoryNumForList = rand() % (size); //randomly picks a num between 0 and the size of the list
		//go to this cell in the list

		cellPtrToBeRemoved = getListNode(&lst, lottoryNumForList);//return the address of the wanted cell and the values of x and y in it
		x = cellPtrToBeRemoved->x;
		y = cellPtrToBeRemoved->y;
		deleteNodeFromDCoordlist(&lst, cellPtrToBeRemoved);//delets this part from the list
		size--;
		lottoryNumForBoard = rand() % (possibilities[x][y]->size); //randomly picks a num from 0 to the size of the cordinate
		//the number picked is the ind in possibilities[x][y]->arr
		//the value in this index will be the value we put in the board

		/*numberToAddToBoard*/
		data = possibilities[x][y]->arr[lottoryNumForBoard];

		board[x][y] = data;

		//after putting the vlaue in the board we will update the possinilities arr in the coordinate's row, col, and box
		updateRow(x, data, board, possibilities);
		updateCol(y, data, board, possibilities);
		updateBox(x, y, data, board, possibilities);
	}

	freeCoordList(&lst);
	

	*numOfCellsPicked = numOfCells;
}

int amountOfPlayers()
{
	int amountOfPlayers = 0;
	while (amountOfPlayers < 1)
	{
		scanf("%d", &amountOfPlayers);
		if (amountOfPlayers < 1)
			printf("Invallid input, please try again");
		return amountOfPlayers;
	}
}

void freePossibilities(Array*** possibilities)
{
	int i;
	int j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				if (possibilities[i][j]->arr != NULL)
					free(possibilities[i][j]->arr);
				free(possibilities[i][j]);
			}
		}
		free(possibilities[i]);
	}
	free(possibilities);
}

