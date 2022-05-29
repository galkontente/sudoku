#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"

//it does not free the node!
void deleteFromPlayersList(PlayersList* list, Lnode_PlayersList* node) //it does not free the node!
{

	if (list->head == node && list->tail == node) // if the list has only 1 node
		list->head = list->tail = NULL;

	else if (list->head == node) // if he is the first
	{
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	else if (list->tail == node) // if he is the last
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

}

void deleteNodeFromDCoordlist(LIST* lst, LNODE* node)
{
	LNODE* saver;
	saver = lst->head;

	if (lst->head == NULL) // == node)
		lst->head = lst->tail = NULL;

	else if (lst->head == node)
	{
		lst->head = lst->head->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == node) // or node->next == NULL
	{
		lst->tail = lst->tail->prev;
		lst->tail->next = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	//because the list is dynamic (allocated with malloc) we have to free the node
	free(node);
}

void makeEmptyList(LIST* lst)
{
	lst->head = lst->tail = NULL;
}

LNODE* getListNode(LIST* lst, int i)
{
	LNODE* curr;
	curr = lst->head;
	while (curr != NULL && i > 0)
	{
		i--;
		curr = curr->next;
	}

	return curr;
}

void insertNodeToEndDList(PlayersList* lst, Lnode_PlayersList* tail)
{
	if (isEmptyList(lst) == 1)
	{
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;
	}
	else
	{
		tail->prev = lst->tail;
		tail->next = NULL;
		lst->tail->next = tail;
		lst->tail = tail;
	}
}

int isEmptyList(PlayersList* lst)
{
	if (lst->head == NULL)
		return 1;
	else
		return 0;
}

void makeEmptyPlayerList(PlayersList* lst)
{
	lst->head = lst->tail = NULL;
}

void printWinnersList(PlayersList* winnerList, int numOfWinners)
{
	int i;
	Lnode_PlayersList* currWinner;
	currWinner = winnerList->head;
	if (numOfWinners == 0)
	{
		printf("No one won this time.\n");
		return;
	}

	printf("We have %d winners! \nPress Enter to show them.\n\n", numOfWinners);
	getchar();
	getchar();
	for (i = 0; i < numOfWinners; i++)
	{
		printf("%s\nWith the board:\n", currWinner->player->name);
		sudokoPrintBoard(currWinner->player->sudokuBoard);
		printf("\n");
		currWinner = currWinner->next;
	}
}

void mergeSort(Lnode_PlayersList** activePlayersArray, int size)
{
	int i = 0;
	Lnode_PlayersList** temp;
	if (size > 1)
	{
		mergeSort(activePlayersArray, size / 2);
		mergeSort(activePlayersArray + (size / 2), size - (size / 2));
		temp = merge(activePlayersArray, size / 2, activePlayersArray + (size / 2), size - (size / 2));
		for (i = 0; i < size; i++)
		{
			activePlayersArray[i] = temp[i];
		}
		free(temp);
	}
}

Lnode_PlayersList** merge(Lnode_PlayersList** activePlayersArray1, int size1, Lnode_PlayersList** activePlayersArray2, int size2)
{
	int i = 0, j = 0, k = 0;
	Lnode_PlayersList** temp = (Lnode_PlayersList**)malloc((size1 + size2) * sizeof(Lnode_PlayersList*));
	checkMemory(temp);
	while ((i < size1) && (j < size2))
	{
		if (activePlayersArray1[i]->initialFullCells < activePlayersArray2[j]->initialFullCells) // means the second has more filled cells at the beginning
		{
			temp[k] = activePlayersArray1[i];
			i++;
		}
		else if (activePlayersArray1[i]->initialFullCells == activePlayersArray2[j]->initialFullCells)
		{
			if (strcmp(activePlayersArray1[i]->player->name, activePlayersArray2[j]->player->name) < 0) //means the first one will appear first in a dictionary
			{
				temp[k] = activePlayersArray1[i];
				i++;
			}
			else
			{
				temp[k] = activePlayersArray2[j];
				j++;
			}
		}
		else
		{
			temp[k] = activePlayersArray2[j];
			j++;
		}
		k++;
	}

	while (i < size1)
	{
		temp[k] = activePlayersArray1[i];
		i++;
		k++;
	}
	while (j < size2)
	{
		temp[k] = activePlayersArray2[j];
		j++;
		k++;
	}

	return temp;
}

PlayersList* createInitialPlayersList(int numOfPlayers, Lnode_PlayersList*** resPlayerArray)
{
	PlayersList* plst;
	Lnode_PlayersList* currPlayersDetails;
	Lnode_PlayersList** activePlayersArray;
	int i = 0, numOfCellsPicked;
	char tempName[100];
	char c;

	plst = (PlayersList*)malloc(sizeof(PlayersList));
	checkMemory(plst);
	makeEmptyPlayerList(plst);

	activePlayersArray = (Lnode_PlayersList**)malloc(sizeof(Lnode_PlayersList*) * numOfPlayers);
	checkMemory(activePlayersArray);
	scanf("%c", &c);
	for (i = 0; i < numOfPlayers; i++)
	{
		printf("Please enter the name of player number %d:", i + 1);
		gets(tempName);

		currPlayersDetails = createNewDPlayersListNode(tempName, NULL, NULL);

		initializeBoard(currPlayersDetails->player, &numOfCellsPicked);
		currPlayersDetails->initialFullCells = numOfCellsPicked; //the amount of initially full cells
		activePlayersArray[i] = currPlayersDetails;//puts the player in the active player array;
		insertNodeToEndDList(plst, currPlayersDetails);

		if (i == numOfPlayers - 1)
			currPlayersDetails->next = NULL;
	}
	*resPlayerArray = activePlayersArray;
	return plst;
}

LIST buildListOfCord(int* size)
{
	LIST lst;
	makeEmptyList(&lst);
	int i, j, sizeCounter = 0;
	LNODE* curr;
	lst.head = (LNODE*)malloc(sizeof(LNODE));
	checkMemory(lst.head);
	curr = lst.head;
	curr->prev = NULL;

	//the list will be coordinates of the board
	//the order- by the row (first the coordinates of the first row)
	//total size of the list - 81
	//head is: x = 0, y = 0
	//tail is: x = 8, y= 8;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (i != 8 || j != 8) //the last one points at NULL
			{
				(curr)->x = i;
				(curr)->y = j;
				(curr)->next = (LNODE*)malloc(sizeof(LNODE));
				checkMemory((lst.head)->next);
				curr->next->prev = curr;
				curr = (curr)->next;
			}

			else
			{
				(curr)->x = i;
				(curr)->y = j;
				curr->next = NULL;
				lst.tail = curr;
			}
			sizeCounter++;
		}
	}
	*size = sizeCounter;
	curr = lst.head;
	return lst;
}

Lnode_PlayersList* createNewDPlayersListNode(char name[], Lnode_PlayersList* next, Lnode_PlayersList* prev)
{
	Lnode_PlayersList* res = (Lnode_PlayersList*)malloc(sizeof(Lnode_PlayersList));
	checkMemory(res); // check mem
	res->player = (playerDetails*)malloc(sizeof(playerDetails)); //maloc for the ->player
	checkMemory(res->player);//check mem
	sprintf(res->player->name, "%s", name);
	res->next = next;
	res->prev = prev;
	return res;
}

void freeCoordList(LIST* lst)
{
	LNODE* curr = lst->head;
	while (curr != NULL)
	{
		lst->head = lst->head->next;
		free(curr);
		curr = lst->head;
	}
}

void freePlayersList(PlayersList* lst)
{
	Lnode_PlayersList* curr = lst->head;
	while (curr != NULL)
	{
		lst->head = lst->head->next;
		freePossibilities(curr->player->possibilities);
		free(curr);
		curr = lst->head;
	}
}