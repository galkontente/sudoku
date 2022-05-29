#ifndef _listhead
#define _listhead
#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"


void deleteFromPlayersList(PlayersList* list, Lnode_PlayersList* node);
void deleteNodeFromDCoordlist(LIST* lst, LNODE* node);								  //lists
void makeEmptyList(LIST* lst);													  //lists
LNODE* getListNode(LIST* lst, int i);											  //lists
void insertNodeToEndDList(PlayersList* lst, Lnode_PlayersList* tail); //lists
int isEmptyList(PlayersList* lst);										  //lists
void makeEmptyPlayerList(PlayersList* lst);//lists
void printWinnersList(PlayersList* winnerList, int numOfWinners);
void mergeSort(Lnode_PlayersList** activePlayersArray, int size);
Lnode_PlayersList** merge(Lnode_PlayersList** activePlayersArray1, int size1, Lnode_PlayersList** activePlayersArray2, int size2);
PlayersList* createInitialPlayersList(int numOfPlayers, Lnode_PlayersList*** resPlayerArray);
LIST buildListOfCord(int* size);
Lnode_PlayersList* createNewDPlayersListNode(char name[], Lnode_PlayersList* next, Lnode_PlayersList* prev);
void freeCoordList(LIST* lst);
void freePlayersList(PlayersList* lst);


#endif // !_listhead
