#ifndef _dataTypes
#define _dataTypes
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SIZE 9
typedef struct playersdeatils
{
	char name[100];
	short sudokuBoard[SIZE][SIZE];
	struct _Array*** possibilities;
} playerDetails;

typedef struct playerslist
{
	struct lnodeplayerslist* head;
	struct lnodeplayerslist* tail;
} PlayersList;

typedef struct lnodeplayerslist
{
	int initialFullCells;
	struct playersdeatils* player;
	struct lnodeplayerslist* next;
	struct lnodeplayerslist* prev;

} Lnode_PlayersList;

typedef struct _Array
{
	short* arr;
	unsigned short size;
} Array;

typedef struct lnode
{
	int x;
	int y;
	struct lnode* next;
	struct lnode* prev;

} LNODE;

typedef struct list
{
	struct lnode* head;
	struct lnode* tail;
} LIST;

typedef struct treenode
{
	Lnode_PlayersList* playerCell;
	struct treenode* left;
	struct treenode* right;
}TREENODE;
typedef struct tree
{
	TREENODE* root;
}TREE;


#define FAIL -1000
#define FILLED -9999
#define NOT_FINISH -2000
#define FINISH_SUCCESS -3000
#define FINISH_FAILURE -3001
#endif // !_dataTypes
