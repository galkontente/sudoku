// ID: 207091844 
//Name: Michael Shorki Shragay
//ID: 207002015
//Name: Gal Kontante
//
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <math.h>
//
//#define SIZE 9
//typedef struct playersdeatils
//{
//	char name[100];
//	short sudokuBoard[SIZE][SIZE];
//	struct _Array*** possibilities;
//} playerDetails;
//
//typedef struct playerslist
//{
//	struct lnodeplayerslist* head;
//	struct lnodeplayerslist* tail;
//} PlayersList;
//
//typedef struct lnodeplayerslist
//{
//	int initialFullCells;
//	struct playersdeatils* player;
//	struct lnodeplayerslist* next;
//	struct lnodeplayerslist* prev;
//
//} Lnode_PlayersList;
//
//typedef struct _Array
//{
//	short* arr;
//	unsigned short size;
//} Array;
//
//typedef struct lnode
//{
//	int x;
//	int y;
//	struct lnode* next;
//	struct lnode* prev;
//
//} LNODE;
//
//typedef struct list
//{
//	struct lnode* head;
//	struct lnode* tail;
//} LIST;
//
//typedef struct treenode
//{
//	Lnode_PlayersList* playerCell;
//	struct treenode* left;
//	struct treenode* right;
//}TREENODE;
//typedef struct tree
//{
//	TREENODE* root;
//}TREE;
//
//
//#define FAIL -1000
//#define FILLED -9999
//#define NOT_FINISH -2000
//#define FINISH_SUCCESS -3000
//#define FINISH_FAILURE -3001
//
//Array*** PossibleDigits(short sudokuBoard[][SIZE]);						   //First Function
//int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y); // Second Function
//int FillBoard(short board[][SIZE], Array*** possibilities);				   // Third Function
//
//Mic added
//Lnode_PlayersList* createNewDPlayersListNode(char name[], Lnode_PlayersList* next, Lnode_PlayersList* prev);
//void sudokoPrintBoard(short sudokuBoard[][SIZE]);
//Array* createEfficiantPoss(short sudokuBoard[][SIZE], int row, int col);
//void checkColPoss(int arr[], short sudokuBoard[][SIZE], int col);
//void checkRowPoss(int arr[], short sudokuBoard[][SIZE], int row);
//void checkBoxPoss(int arr[], short sudokuBoard[][SIZE], int row, int col);
//Gal added
//int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y); // Second Function
//void updateRow(int row, short num, short board[][SIZE], Array*** possibilities);		  //updates the poss of the cell's row
//void updateCol(int col, short num, short board[][SIZE], Array*** possibilities);		  //updates the poss of the cell's coll
//void updateBox(int row, int col, short num, short board[][SIZE], Array*** possibilities); //updates the poss of the cell's in the box
//void checkMemory(void* check);
//LIST buildListOfCord(int* size);
//void generateBoard(short board[][SIZE], Array*** possibilities, int* numOfCellsPicked);
//PlayersList* createInitialPlayersList(int numOfPlayers, Lnode_PlayersList*** resPlayerArray);
//playerDetails* activePlayersArray(PlayersList plst);
//int amountOfPlayers();
//void printWinnersList(PlayersList* winnerList, int numOfWinners);
//void mergeSort(Lnode_PlayersList** activePlayersArray, int size);
//Lnode_PlayersList** merge(Lnode_PlayersList** activePlayersArray1, int size1, Lnode_PlayersList** activePlayersArray2, int size2);
//void initializeBoard(playerDetails* player, int* numOfCellsFirstFilled);
//void deleteNodeFromDCoordlist(LIST* lst, LNODE* node);								  //lists
//void makeEmptyList(LIST* lst);													  //lists
//LNODE* getListNode(LIST* lst, int i);											  //lists
//void insertNodeToEndDList(PlayersList* lst, Lnode_PlayersList* tail); //lists
//int isEmptyList(PlayersList* lst);										  //lists
//void makeEmptyPlayerList(PlayersList* lst);//lists
//Tree functions
//TREE buildTreeFromAPL(Lnode_PlayersList** apl, int size);
//TREENODE* buildTreeFromAPLHelper(Lnode_PlayersList** apl, int size);
//TREENODE* buildTreeNode(Lnode_PlayersList* data, TREENODE* left, TREENODE* right);
//void playTreeInOrder(TREE tr, PlayersList* active, PlayersList* winner, int* pNumberOfWinners);
//int playTreeInOrderHelper(TREENODE* node, PlayersList* active, PlayersList* winner);
//void deleteFromPlayersList(PlayersList* list, Lnode_PlayersList* node);
//
//void main()
//{
//	srand(12345);
//	int i;
//	int numOfPlayers, numOfWinners;
//	PlayersList* winnerList;
//	PlayersList* playersList;
//	Lnode_PlayersList* currPlayer;
//	Lnode_PlayersList** sortedAPL;
//	TREE playersTree;
//	printf("******************************\n");
//	printf("*hello and welcome to sudoku!*\n");
//	printf("******************************\n");
//	printf("how many players will play in the game?");
//	numOfPlayers = amountOfPlayers();//gets the number of people playing
//	asks for the name of each player, fits each player a board and a possabilities array:
//	playersList = createInitialPlayersList(numOfPlayers, &sortedAPL);
//	mergeSort(sortedAPL, numOfPlayers);
//	playersTree = buildTreeFromAPL(sortedAPL, numOfPlayers);//builts a tree of the players list
//
//	winnerList = (PlayersList*)malloc(sizeof(PlayersList));
//	checkMemory(winnerList);
//	winnerList->head = winnerList->tail = NULL;
//	playTreeInOrder(playersTree, playersList, winnerList, &numOfWinners);//the course of the game 
//	winnerList = (PlayersList*)realloc(sizeof(PlayersList) * numOfPlayers, winnerList);////$$$$$needs a counter for the amount of winners
//	checkMemory(winnerList);
//	WINNER LIST
//
//	printWinnersList(winnerList, numOfWinners);//$$ CHANGE numOfPlayers TO numOfWinners AFTER WE FIX IT
//	WHY IS THIS IN THE MAIN?$$$
//
//	if (FillBoard(board, possible_solutions) == FAIL)
//
//		printf("User's selections led to duplications\n");
//
//	else
//	{
//		sudokoPrintBoard(board);
//
//		printf("Board filled successfully\n");
//	}
//
//	 Don't forget to free memory!
//}
//
//Array*** PossibleDigits(short sudokuBoard[][SIZE]) //1st function
//{
//	int i, j;
//	int sizeOfPoss = 0;
//	Array*** res;
//	res = (Array***)malloc(sizeof(Array**) * SIZE); // make 9 rowse
//	checkMemory(res);
//	for (i = 0; i < SIZE; i++)
//	{
//		res[i] = (Array**)malloc(sizeof(Array*) * SIZE); // make 9 cols
//		checkMemory(res);
//	}
//
//	for (i = 0; i < SIZE; i++)
//	{
//		for (j = 0; j < SIZE; j++)
//		{
//			if (sudokuBoard[i][j] != -1)
//			{
//				res[i][j] = NULL;
//			}
//			else //if its -1 (means its an empty space)
//			{
//				res[i][j] = createEfficiantPoss(sudokuBoard, i, j); //i is the rows, j for cols
//			}
//		}
//	}
//
//	return res;
//}
//
//Array* createEfficiantPoss(short sudokuBoard[][SIZE], int row, int col)
//{
//	int i, counter = 0, ind;
//	Array* res;
//	res = (Array*)malloc(sizeof(Array));
//	checkMemory(res);
//	int arr[SIZE] = { 0 };					  //every spot for every number, with the number 0.
//	checkColPoss(arr, sudokuBoard, col);	  // every value, adds +1 to arr[value]
//	checkRowPoss(arr, sudokuBoard, row);	  // every value, adds +1 to arr[value]
//	checkBoxPoss(arr, sudokuBoard, row, col); // every value, adds +1 to arr[value]
//	for (i = 0; i < SIZE; i++)				  // counts how many numbers we are left with thats still 0 (possible to use)
//	{
//		if (arr[i] == 0)
//			counter++;
//	}
//	res->arr = (short*)malloc(sizeof(short) * counter);
//	checkMemory(res->arr);
//	res->size = counter;
//	for (i = 0, ind = 0; i < SIZE; i++) // fills the numbers into place
//	{
//		if (arr[i] == 0)
//		{
//			res->arr[ind] = (short)(i + 1);
//			ind++;
//		}
//	}
//
//	return res;
//}
//void checkColPoss(int arr[], short sudokuBoard[][SIZE], int col)
//{
//	int i;
//	for (i = 0; i < 9; i++)
//	{
//		if (sudokuBoard[i][col] != -1)
//			arr[sudokuBoard[i][col] - 1]++;
//	}
//	/*for (i = 0; i < SIZE; i++)
//		arr[sudokuBoard[i][col] - 1] += sudokuBoard[i][col] != -1 ? 1 : 0;*/
//}
//
//void checkRowPoss(int arr[], short sudokuBoard[][SIZE], int row)
//{
//	int i;
//	for (i = 0; i < SIZE; i++)
//	{
//		if (sudokuBoard[row][i] != -1)
//			arr[sudokuBoard[row][i] - 1]++;
//	}
//}
//void checkBoxPoss(int arr[], short sudokuBoard[][SIZE], int row, int col)
//{
//	int startRow = row;
//	int startCol = col;
//	int i, j;
//	while (startRow % 3 != 0) //move to the up side of the Box
//		startRow--;
//	while (startCol % 3 != 0) //move to the left of the Box
//		startCol--;
//	for (i = 0; i < 3; i++)
//	{
//		for (j = 0; j < 3; j++)
//			sudokuBoard[startRow + i][startCol + j] += sudokuBoard[startRow + i][startCol + j] != -1 ? 1 : 0;
//	}
//}
//
//void sudokoPrintBoard(short sudokuBoard[][SIZE])
//{
//	int i, j;
//	printf("  |");
//	for (j = 0; j < SIZE; j++)
//		(j % 3 == 2 && j != 8) ? printf("%2d|", j) : printf("%2d", j);
//
//	printf("\n");
//	for (i = 0; i < SIZE; i++)
//	{
//		if (i % 3 == 0)
//			printf("-----------------------\n");
//		printf(" %d", i);
//		for (j = 0; j < 9; j++)
//		{
//			if (j % 3 == 0)
//				printf("|");
//			if (sudokuBoard[i][j] != -1)
//				printf("%2d", sudokuBoard[i][j]);
//			else
//				printf("%2c", '-');
//
//		}
//		printf("\n");
//	}
//	printf("-----------------------\n");
//}
//
//int FillBoard(short board[][SIZE], Array*** possibilities)
//{
//	int res, x, y, choice;
//	int tempArrSize;
//	int i;
//	int flagLegitInput = 0;
//	res = OneStage(board, possibilities, &x, &y);
//	while (res == NOT_FINISH)
//	{
//		sudokoPrintBoard(board);
//		tempArrSize = possibilities[x][y]->size;
//		while (flagLegitInput == 0)
//		{
//			printf("What value do you want to put at (%d,%d)?\n", x, y);
//			printf("The options are: ");
//			for (i = 0; i < tempArrSize; i++)
//				printf("%d ", possibilities[x][y]->arr[i]);
//			printf(".\n");
//			scanf("%d", &choice);
//			for (i = 0; i < tempArrSize; i++)
//				if (possibilities[x][y]->arr[i] == choice)
//				{
//					flagLegitInput = 1;
//					break;
//				}
//			if (flagLegitInput != 1)
//				printf("INVALID INPUT.\n");
//		}
//
//		board[x][y] = choice;
//		free(possibilities[x][y]->arr);
//		free(possibilities[x][y]);
//		possibilities[x][y] = NULL;					   //now it points on NULL
//		updateRow(x, choice, board, possibilities);	   //updates to the current relevant poss in the point's row
//		updateCol(y, choice, board, possibilities);	   //updates to the current relevant poss in the point's col
//		updateBox(x, y, choice, board, possibilities); //updates to the current relevant poss in the point's box
//		res = OneStage(board, possibilities, &x, &y);
//		flagLegitInput = 0;
//	}
//	if (res == FINISH_FAILURE)
//		res = FAIL;
//
//	else if (res == FINISH_SUCCESS)
//		res = FILLED;
//
//	return res;
//}
//
//int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y)
//{
//	int i, j;
//	short data;
//	int stop = 0;
//	int unfilled;
//	int unsolvable = 0;
//	int minOptions, minX, minY;
//	while (stop == 0)
//	{
//		minOptions = SIZE;
//		stop = 1;
//		unfilled = 0;
//		for (i = 0; i < SIZE; i++) //rows
//		{
//			for (j = 0; j < SIZE; j++) //cols
//			{
//				if (board[i][j] == -1) //empty space
//				{
//					unfilled++;
//					if (possibilities[i][j] == NULL) // empty space and no options !
//					{
//						unsolvable = 1;
//						break;
//					}
//					else if (possibilities[i][j]->size == 1) // empty space with only 1 option
//					{
//						data = possibilities[i][j]->arr[0];
//						board[i][j] = data;
//						update possibily (free, and box row col)
//						free(possibilities[i][j]->arr);
//						free(possibilities[i][j]);
//						possibilities[i][j] = NULL;
//						stop = 0;
//						updateRow(i, data, board, possibilities);
//						updateCol(j, data, board, possibilities);
//						updateBox(i, j, data, board, possibilities);
//					}
//					else // empty space with nore then 1 option
//					{
//						if (possibilities[i][j]->size < minOptions)
//						{
//							minOptions = possibilities[i][j]->size;
//							minX = i;
//							minY = j;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	printf("DEBUG: \nunsolvable:%d\nunfilled:%d\nmin options:%d (%d,%d) \n", unsolvable, unfilled, minOptions, minX, minY);
//	if (unsolvable == 1)
//		return FINISH_FAILURE;
//
//	else if (unfilled == 0)
//		return FINISH_SUCCESS;
//
//	else if (stop == 1 && unfilled > 0)
//	{
//		*x = minX;
//		*y = minY;
//		return NOT_FINISH;
//	}
//	else
//		printf("What?");
//}
//
//void updateRow(int row, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's row
//{
//	int i, arrInd, removeInd;
//	unsigned short size;
//	for (i = 0; i < SIZE; i++)
//	{
//		if (possibilities[row][i] != NULL)
//		{
//			size = possibilities[row][i]->size;
//			if (num < possibilities[row][i]->arr[0] || num > possibilities[row][i]->arr[size - 1])
//				continue;
//			else if (size == 1 && possibilities[row][i]->arr[0] == num)
//			{
//				free(possibilities[row][i]->arr);
//				free(possibilities[row][i]);
//				possibilities[row][i] = NULL;
//			}
//			else
//			{
//				for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
//				{
//					if (num == possibilities[row][i]->arr[arrInd]) //when we find him
//					{
//						for (removeInd = arrInd; removeInd < size - 1; removeInd++)
//							possibilities[row][i]->arr[removeInd] = possibilities[row][i]->arr[removeInd + 1];
//
//						possibilities[row][i]->arr = (short*)realloc(possibilities[row][i]->arr, sizeof(short) * (size - 1));
//						checkMemory(possibilities[row][i]->arr);
//						possibilities[row][i]->size = size - 1;
//						break;
//					}
//				}
//			}
//		}
//	}
//}
//
//void updateCol(int col, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's coll
//{
//	int i, arrInd, removeInd;
//	unsigned short size;
//	for (i = 0; i < SIZE; i++)
//	{
//		if (possibilities[i][col] != NULL)
//		{
//			size = possibilities[i][col]->size;
//			if (num < possibilities[i][col]->arr[0] || num > possibilities[i][col]->arr[size - 1])
//				continue;
//			else if (size == 1 && possibilities[i][col]->arr[0] == num)
//			{
//				free(possibilities[i][col]->arr);
//				free(possibilities[i][col]);
//				possibilities[i][col] = NULL;
//			}
//			else
//			{
//				for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
//				{
//					if (num == possibilities[i][col]->arr[arrInd]) //when we find him
//					{
//						for (removeInd = arrInd; removeInd < size - 1; removeInd++)
//						{
//							possibilities[i][col]->arr[removeInd] = possibilities[i][col]->arr[removeInd + 1];
//						}
//						possibilities[i][col]->arr = (short*)realloc(possibilities[i][col]->arr, sizeof(short) * (size - 1));
//						checkMemory(possibilities[i][col]->arr);
//						possibilities[i][col]->size = size - 1;
//						break;
//					}
//				}
//			}
//		}
//	}
//}
//
//void updateBox(int row, int col, short num, short board[][SIZE], Array*** possibilities) //updates the poss of the cell's in the box
//{
//	int i, j, arrInd, removeInd;
//	unsigned short size;
//	int startRow = row, startCol = col;
//	while (startRow % 3 != 0)
//		startRow--;
//	while (startCol % 3 != 0)
//		startCol--;
//	for (i = 0; i < 3; i++)
//	{
//		for (j = 0; j < 3; j++)
//		{
//			if (possibilities[startRow + i][startCol + j] != NULL)
//			{
//				size = possibilities[startRow + i][startCol + j]->size;
//				if (num < possibilities[startRow + i][startCol + j]->arr[0] || num > possibilities[startRow + i][startCol + j]->arr[size - 1])
//					continue;
//				else if (size == 1 && possibilities[startRow + i][startCol + j]->arr[0] == num)
//				{
//					free(possibilities[startRow + i][startCol + j]->arr);
//					free(possibilities[startRow + i][startCol + j]);
//					possibilities[startRow + i][startCol + j] = NULL;
//				}
//				else
//				{
//					for (arrInd = 0; arrInd < size; arrInd++) //Look for the number we want to remove
//					{
//						if (num == possibilities[startRow + i][startCol + j]->arr[arrInd]) //when we find him
//						{
//							for (removeInd = arrInd; removeInd < size - 1; removeInd++)
//							{
//								possibilities[startRow + i][startCol + j]->arr[removeInd] = possibilities[startRow + i][startCol + j]->arr[removeInd + 1];
//							}
//							possibilities[startRow + i][startCol + j]->arr = (short*)realloc(possibilities[startRow + i][startCol + j]->arr, sizeof(short) * (size - 1));
//							checkMemory(possibilities[startRow + i][startCol + j]->arr);
//							possibilities[startRow + i][startCol + j]->size = size - 1;
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//void checkMemory(void* check) //checks succes of memeory allocation
//{
//	if (check == NULL)
//		exit(1);
//}
//
//void initializeBoard(playerDetails* player, int* numOfCellsFirstFilled)
//{
//	Array*** tempPossibilities;
//	int i, j, numOfCellsPicked;
//
//	for (i = 0; i < SIZE; i++) //resets the board by putting -1 in every cell
//	{
//		for (j = 0; j < SIZE; j++)
//		{
//			player->sudokuBoard[i][j] = -1;
//		}
//
//	}
//
//	tempPossibilities = PossibleDigits(player->sudokuBoard); //resets the possibilities of each cell
//	player->possibilities = tempPossibilities;
//	generateBoard(player->sudokuBoard, player->possibilities, &numOfCellsPicked); //generates a board for this player
//	*numOfCellsFirstFilled = numOfCellsPicked;									  //returns the ampont of filled cells in the initial board
//}
//
//void generateBoard(short board[][SIZE], Array*** possibilities, int* numOfCellsPicked)
//{
//	int i = 0, numOfCells = 0, lottoryNumForList, lottoryNumForBoard;
//	int x, y, data;
//	LIST lst;
//	LNODE* cellPtrToBeRemoved;
//	makeEmptyList(&lst);
//	int size;
//	?
//	lst = buildListOfCord(&size);
//
//	in order to get different nums in the call for random functionn$$ MAY NEED TO MOVE TO MAIN
//	numOfCells = (rand() % 20) + 1; //randomly picks a num from 1 to 20 and it will be the num of cells first filld
//
//	for (i = 0; i < numOfCells; i++)
//	{
//		lottoryNumForList = rand() % (size); //randomly picks a num between 0 and the size of the list
//		go to this cell in the list
//
//		cellPtrToBeRemoved = getListNode(&lst, lottoryNumForList);//return the address of the wanted cell and the values of x and y in it
//		x = cellPtrToBeRemoved->x; //$$$$$$$$$$$$
//		y = cellPtrToBeRemoved->y;
//		deleteNodeFromDCoordlist(&lst, cellPtrToBeRemoved);//delets this part from the list
//		size--;
//		lottoryNumForBoard = rand() % (possibilities[x][y]->size); //randomly picks a num from 0 to the size of the cordinate
//		the number picked is the ind in possibilities[x][y]->arr
//		the value in this index will be the value we put in the board
//
//		/*numberToAddToBoard*/
//		data = possibilities[x][y]->arr[lottoryNumForBoard];
//
//		board[x][y] = data;
//
//		after putting the vlaue in the board we will update the possinilities arr in the coordinate's row, col, and box
//		updateRow(x, data, board, possibilities);
//		updateCol(y, data, board, possibilities);
//		updateBox(x, y, data, board, possibilities);
//	}
//
//	*numOfCellsPicked = numOfCells;
//}
//
//LIST buildListOfCord(int* size)
//{
//	LIST lst;
//	makeEmptyList(&lst);
//	int i, j, sizeCounter = 0;
//	LNODE* curr;
//	lst.head = (LNODE*)malloc(sizeof(LNODE));
//	checkMemory(lst.head);
//	curr = lst.head;
//	curr->prev = NULL;
//
//	the list will be coordinates of the board
//	the order- by the row (first the coordinates of the first row)
//	total size of the list - 81
//	head is: x = 0, y = 0
//	tail is: x = 8, y= 8;
//	for (i = 0; i < SIZE; i++)
//	{
//		for (j = 0; j < SIZE; j++)
//		{
//			if (i != 8 || j != 8) //the last one points at NULL
//			{
//				(curr)->x = i;
//				(curr)->y = j;
//				(curr)->next = (LNODE*)malloc(sizeof(LNODE));
//				checkMemory((lst.head)->next);
//				curr->next->prev = curr;
//				curr = (curr)->next;
//			}
//
//			else
//			{
//				(curr)->x = i;
//				(curr)->y = j;
//				curr->next = NULL;
//				lst.tail = curr;
//			}
//			sizeCounter++;
//		}
//	}
//	*size = sizeCounter;
//	curr = lst.head;
//	FOR DEBUGGING ONLY:
//	while (curr != NULL)
//	{
//		printf("[%d,%d]\n", curr->x, curr->y);
//		curr = curr->next;
//	}
//
//
//
//
//	return lst;
//}
//
//////lists functions
//
//void makeEmptyList(LIST* lst)
//{
//	lst->head = lst->tail = NULL;
//}
//
//void makeEmptyPlayerList(PlayersList* lst)
//{
//	lst->head = lst->tail = NULL;
//}
//
//int isEmptyList(PlayersList* lst)
//{
//	if (lst->head == NULL)
//		return 1;
//	else
//		return 0;
//}
//
//void insertNodeToEndDList(PlayersList* lst, Lnode_PlayersList* tail)
//{
//	if (isEmptyList(lst) == 1)
//	{
//		tail->next = tail->prev = NULL;
//		lst->head = lst->tail = tail;
//	}
//	else
//	{
//		tail->prev = lst->tail;
//		tail->next = NULL;
//		lst->tail->next = tail;
//		lst->tail = tail;
//	}
//}
//
//LNODE* getListNode(LIST* lst, int i)
//{
//	LNODE* curr;
//	curr = (LNODE*)malloc(sizeof(LNODE));
//	checkMemory(curr);
//	curr = lst->head;
//	while (curr != NULL && i > 0)
//	{
//		i--;
//		curr = curr->next;
//	}
//
//	return curr;
//}
//
//
//void deleteNodeFromDCoordlist(LIST* lst, LNODE* node)
//{
//	LNODE* saver;
//	saver = lst->head;
//
//	if (lst->head == NULL) // == node)
//		lst->head = lst->tail = NULL;
//
//	else if (lst->head == node)
//	{
//		lst->head = lst->head->next;
//		lst->head->prev = NULL;
//	}
//	else if (lst->tail == node) // or node->next == NULL
//	{
//		lst->tail = lst->tail->prev;
//		lst->tail->next = NULL;
//	}
//	else
//	{
//		node->prev->next = node->next;
//		node->next->prev = node->prev;
//	}
//
//
//
//	if the list is dynamic (allocated with malloc) we have to free the node
//	free(node);
//}
//
//PlayersList* createInitialPlayersList(int numOfPlayers, Lnode_PlayersList*** resPlayerArray) //needs to be modular
//{
//	PlayersList* plst;
//	Lnode_PlayersList* currPlayersDetails;
//	Lnode_PlayersList** activePlayersArray;
//	int i = 0, numOfCellsPicked;
//	char tempName[100];
//
//	plst = (PlayersList*)malloc(sizeof(PlayersList));
//	checkMemory(plst);
//	makeEmptyPlayerList(plst);
//
//	activePlayersArray = (Lnode_PlayersList**)malloc(sizeof(Lnode_PlayersList*) * numOfPlayers);
//	checkMemory(activePlayersArray);
//
//	for (i = 0; i < numOfPlayers; i++)
//	{
//		printf("Please enter the name of player number %d:", i + 1);
//		scanf("%s", tempName);
//
//		currPlayersDetails = createNewDPlayersListNode(tempName, NULL, NULL);
//
//		initializeBoard(currPlayersDetails->player, &numOfCellsPicked);
//		currPlayersDetails->initialFullCells = numOfCellsPicked; //the amount of initially full cells
//		activePlayersArray[i] = currPlayersDetails;//puts the player in the active player array;
//		insertNodeToEndDList(plst, currPlayersDetails);
//
//		if (i == numOfPlayers - 1)
//			currPlayersDetails->next = NULL;
//	}
//	*resPlayerArray = activePlayersArray;
//	return plst;
//}
//
//Lnode_PlayersList* createNewDPlayersListNode(char name[], Lnode_PlayersList* next, Lnode_PlayersList* prev)
//{
//	Lnode_PlayersList* res = (Lnode_PlayersList*)malloc(sizeof(Lnode_PlayersList));
//	checkMemory(res); // check mem
//	res->player = (playerDetails*)malloc(sizeof(playerDetails)); //maloc for the ->player
//	checkMemory(res->player);//check mem
//	sprintf(res->player->name, "%s", name);
//	res->next = next;
//	res->prev = prev;
//	return res;
//}
//
//int amountOfPlayers()
//{
//	int amountOfPlayers = 0;
//	while (amountOfPlayers < 1)
//	{
//		scanf("%d", &amountOfPlayers);
//		if (amountOfPlayers < 1)
//			printf("Invallid input, please try again");
//		return amountOfPlayers;
//	}
//}
//
//void initGame ( List *activePlayers, node** ptrToNodeElemnt )?????
//
///*flow of main :
//ask how many players ==> number
//
//for each player : (number)
//	get his/her name
//	initBoard
//	add referance to their node to the ptr array
//
//sort players by there their - bad name!! -with the ptr array
//
//*/
//
//playerDetails* activePlayersArray(Lnode_PlayersList** activePlayersArray,int numOfPlayers)//$$can be deleted??
//{
//	mergeSort(activePlayersArray, numOfPlayers);
//}
//
//void mergeSort(Lnode_PlayersList** activePlayersArray, int size)
//{
//	int i = 0;
//	Lnode_PlayersList** temp;
//	if (size > 1)
//	{
//		mergeSort(activePlayersArray, size / 2);
//		mergeSort(activePlayersArray + (size / 2), size - (size / 2));
//		temp = (Lnode_PlayersList**)malloc(size * sizeof(Lnode_PlayersList*));
//		checkMemory(temp);
//		temp = merge(activePlayersArray, size / 2, activePlayersArray + (size / 2), size - (size / 2));
//		for (i = 0; i < size; i++)
//		{
//			activePlayersArray[i] = temp[i];
//		}
//		free(temp);
//	}
//}
//
//Lnode_PlayersList** merge(Lnode_PlayersList** activePlayersArray1, int size1, Lnode_PlayersList** activePlayersArray2, int size2)
//{
//	int i = 0, j = 0, k = 0;
//	Lnode_PlayersList** temp = (Lnode_PlayersList**)malloc((size1 + size2) * sizeof(Lnode_PlayersList*));
//	checkMemory(temp);
//	while ((i < size1) && (j < size2))
//	{
//		if (activePlayersArray1[i]->initialFullCells < activePlayersArray2[j]->initialFullCells) // means the second has more filled cells at the beginning
//		{
//			temp[k] = activePlayersArray1[i];
//			i++;
//		}
//		else if (activePlayersArray1[i]->initialFullCells == activePlayersArray2[j]->initialFullCells)
//		{
//			if (strcmp(activePlayersArray1[i]->player->name, activePlayersArray2[j]->player->name) < 0) //means the first one will appear first in a dictionary
//			{
//				temp[k] = activePlayersArray1[i];
//				i++;
//			}
//			else
//			{
//				temp[k] = activePlayersArray2[j];
//				j++;
//			}
//		}
//		else
//		{
//			temp[k] = activePlayersArray2[j];
//			j++;
//		}
//		k++;
//	}
//
//	while (i < size1)
//	{
//		temp[k] = activePlayersArray1[i];
//		i++;
//		k++;
//	}
//	while (j < size2)
//	{
//		temp[k] = activePlayersArray2[j];
//		j++;
//		k++;
//	}
//
//	return temp;
//}
//
//
//TREE buildTreeFromAPL(Lnode_PlayersList** apl, int size)
//{
//	TREE res;
//	int i;
//	int newSize = size;
//	if (!(log2f(size + 1) == ceil(log2f(size + 1)))) //if its not the perfect size
//	{
//		newSize = (int)pow(2, ceil(log2f(size + 1))) - 1; //round the number up
//		realloc
//		apl = (Lnode_PlayersList**)realloc(apl, newSize * sizeof(Lnode_PlayersList*));
//		checkMemory(apl);
//		makes the empty spaces null
//		for (i = size; i < newSize; i++)
//		{
//			apl[i] = NULL;
//		}
//
//	}
//	res.root = buildTreeFromAPLHelper(apl, newSize); //call the func to make it a tree
//	return res;
//}
//
//
//TREENODE* buildTreeFromAPLHelper(Lnode_PlayersList** apl, int size)
//{
//	if (size == 0)
//		return NULL;
//	TREENODE* node = buildTreeNode(apl[size / 2], NULL, NULL);
//	send the rest, without the middle one.
//	node->right = buildTreeFromAPLHelper(apl + ((size / 2) + 1), size / 2);
//	node->left = buildTreeFromAPLHelper(apl, size / 2);
//	return node;
//}
//TREENODE* buildTreeNode(Lnode_PlayersList* data, TREENODE* left, TREENODE* right)
//{
//	TREENODE* res = (TREENODE*)malloc(sizeof(TREENODE));
//	checkMemory(res);
//	res->playerCell = data; // points at the cell of the player
//	res->left = left;
//	res->right = right;
//	return res;
//}
//void playTreeInOrder(TREE tr, PlayersList* active, PlayersList* winner, int* pNumberOfWinners)
//{
//	*pNumberOfWinners = playTreeInOrderHelper(tr.root, active, winner);
//}
//int playTreeInOrderHelper(TREENODE* node, PlayersList* active, PlayersList* winner)
//{
//	if (node == NULL)
//		return 0;
//	int res;
//	int winnerCount = 0;
//	winnerCount += playTreeInOrderHelper(node->left, active, winner);//left
//	mid
//	if (node->playerCell != NULL)
//	{
//		printf("\n%s, its your turn to play!\n", node->playerCell->player->name);
//		printf("\nPress Enter to start the game...\n");
//		getchar();
//		getchar();
//		res = FillBoard(node->playerCell->player->sudokuBoard, node->playerCell->player->possibilities);
//		use res
//		if (res == FAIL)//del player from active player list, place NULL in tree for him
//		{
//			printf("\nSorry %s, you lost the game.\n", node->playerCell->player->name);
//			deleteFromActivePlayerList
//			deleteFromPlayersList(active, node->playerCell);
//			free(node->playerCell);
//			place null
//			node->playerCell = NULL;
//		}
//
//		else if (res == FILLED)//move to Winning list, place NULL in tree for him
//		{
//			printf("\nCongratulations %s! you won the game!\nYou have been added to the winners list!\n", node->playerCell->player->name);
//			printf("\nThis is your winning board:\n");
//			sudokoPrintBoard(node->playerCell->player->sudokuBoard);
//			deleteFromActivePlayerList
//			deleteFromPlayersList(active, node->playerCell);
//			addNodeToEndListOfWinners
//			insertNodeToEndDList(winner, node->playerCell);
//			place null
//			node->playerCell = NULL;
//			winnerCount++;
//		}
//	}
//
//
//	winnerCount += playTreeInOrderHelper(node->right, active, winner);//right
//
//	return winnerCount;
//}
//
//mic list functions
//
//it does not free the node!
//void deleteFromPlayersList(PlayersList* list, Lnode_PlayersList* node) //it does not free the node!
//{
//
//	if (list->head == node && list->tail == node) // if the list has only 1 node
//		list->head = list->tail = NULL;
//
//	else if (list->head == node) // if he is the first
//	{
//		list->head = list->head->next;
//		list->head->prev = NULL;
//	}
//	else if (list->tail == node) // if he is the last
//	{
//		list->tail = list->tail->prev;
//		list->tail->next = NULL;
//	}
//	else
//	{
//		node->prev->next = node->next;
//		node->next->prev = node->prev;
//	}
//
//}
//
//
//void printWinnersList(PlayersList* winnerList, int numOfWinners)
//{
//	int i;
//	Lnode_PlayersList* currWinner;
//	currWinner = winnerList->head;
//	if (numOfWinners == 0)
//	{
//		printf("No one won this time.\n");
//		return;
//	}
//
//	printf("We have %d winners! \nPress Enter to show them.\n\n", numOfWinners);
//	getchar();
//	getchar();
//	for (i = 0; i < numOfWinners; i++)
//	{
//		printf("%s\nWith the board:\n", currWinner->player->name);
//		sudokoPrintBoard(currWinner->player->sudokuBoard);
//		printf("\n");
//		currWinner = currWinner->next;
//	}
//}