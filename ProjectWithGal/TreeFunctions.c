#include "TreeLib.h"


TREE buildTreeFromAPL(Lnode_PlayersList** apl, int size)
{
	TREE res;
	int i;
	int newSize = size;
	if (!(log2f(size + 1) == ceil(log2f(size + 1)))) //if its not the perfect size
	{
		newSize = (int)pow(2, ceil(log2f(size + 1))) - 1; //round the number up
		//realloc
		apl = (Lnode_PlayersList**)realloc(apl, newSize * sizeof(Lnode_PlayersList*));
		checkMemory(apl);
		//makes the empty spaces null
		for (i = size; i < newSize; i++)
		{
			apl[i] = NULL;
		}

	}
	res.root = buildTreeFromAPLHelper(apl, newSize); //call the func to make it a tree
	return res;
}

TREENODE* buildTreeFromAPLHelper(Lnode_PlayersList** apl, int size)
{
	if (size == 0)
		return NULL;
	TREENODE* node = buildTreeNode(apl[size / 2], NULL, NULL);
	//send the rest, without the middle one.
	node->right = buildTreeFromAPLHelper(apl + ((size / 2) + 1), size / 2);
	node->left = buildTreeFromAPLHelper(apl, size / 2);
	return node;
}

TREENODE* buildTreeNode(Lnode_PlayersList* data, TREENODE* left, TREENODE* right)
{
	TREENODE* res = (TREENODE*)malloc(sizeof(TREENODE));
	checkMemory(res);
	res->playerCell = data; // points at the cell of the player
	res->left = left;
	res->right = right;
	return res;
}

void playTreeInOrder(TREE tr, PlayersList* active, PlayersList* winner, int* pNumberOfWinners)
{
	*pNumberOfWinners = playTreeInOrderHelper(tr.root, active, winner);
}

int playTreeInOrderHelper(TREENODE* node, PlayersList* active, PlayersList* winner)
{
	if (node == NULL)
		return 0;
	int res;
	int winnerCount = 0;
	winnerCount += playTreeInOrderHelper(node->left, active, winner);//left
	//mid
	if (node->playerCell != NULL)
	{
		printf("\n%s, its your turn to play!\n", node->playerCell->player->name);
		printf("\nPress Enter to start the game...\n");
		getchar();
		getchar();
		res = FillBoard(node->playerCell->player->sudokuBoard, node->playerCell->player->possibilities);
		//use res
		if (res == FAIL)//del player from active player list, place NULL in tree for him
		{
			printf("\nSorry %s, you lost the game.\n", node->playerCell->player->name);
			//deleteFromActivePlayerList
			deleteFromPlayersList(active, node->playerCell);
			freePossibilities(node->playerCell->player->possibilities);
			free(node->playerCell);
			//place null
			node->playerCell = NULL;
		}

		else if (res == FILLED)//move to Winning list, place NULL in tree for him
		{
			printf("\nCongratulations %s! you won the game!\nYou have been added to the winners list!\n", node->playerCell->player->name);
			printf("\nThis is your winning board:\n");
			sudokoPrintBoard(node->playerCell->player->sudokuBoard);
			//deleteFromActivePlayerList
			deleteFromPlayersList(active, node->playerCell);
			//addNodeToEndListOfWinners
			insertNodeToEndDList(winner, node->playerCell);
			//place null
			node->playerCell = NULL;
			winnerCount++;
		}
	}


	winnerCount += playTreeInOrderHelper(node->right, active, winner);//right

	return winnerCount;
}

void freeTree(TREE tr)
{
	freeTreeHelper(tr.root);
	tr.root = NULL;
}

void freeTreeHelper(TREENODE* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root);
	}
}