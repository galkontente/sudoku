// ID: 207091844 
//Name: Michael Shorki Shragay
//ID: 207002015
//Name: Gal Kontente
#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"

void main()
{
	srand(12345);
	int numOfPlayers, numOfWinners;
	PlayersList* winnerList; 
	PlayersList* playersList;
	Lnode_PlayersList** sortedAPL;
	TREE playersTree;
	printf("******************************\n");
	printf("*Hello and welcome to sudoku!*\n");
	printf("******************************\n");
	printf("(Project by Michael Shorki Shragay & Gal Kontente)\n\n");
	printf("how many players will play the the game?");
	numOfPlayers = amountOfPlayers();//gets the number of people playing
	//asks for the name of each player, fits each player a board and a possabilities array:
	playersList = createInitialPlayersList(numOfPlayers, &sortedAPL);
	mergeSort(sortedAPL, numOfPlayers);
	playersTree = buildTreeFromAPL(sortedAPL, numOfPlayers);//builts a tree of the players list

	winnerList = (PlayersList*)malloc(sizeof(PlayersList));
	checkMemory(winnerList);
	winnerList->head = winnerList->tail = NULL;

	playTreeInOrder(playersTree, playersList, winnerList, &numOfWinners);//the course of the game 


	printWinnersList(winnerList, numOfWinners);

	//free all the stuff
	free(sortedAPL);
	freeTree(playersTree);
	freePlayersList(winnerList);


}




















