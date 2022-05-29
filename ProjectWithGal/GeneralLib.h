#ifndef _generalsudoku
#define _generalsudoku
#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"
Array*** PossibleDigits(short sudokuBoard[][SIZE]);						   //First Function
int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y); // Second Function
int FillBoard(short board[][SIZE], Array*** possibilities);				   // Third Function

void sudokoPrintBoard(short sudokuBoard[][SIZE]);
Array* createEfficiantPoss(short sudokuBoard[][SIZE], int row, int col);
void checkColPoss(int arr[], short sudokuBoard[][SIZE], int col);
void checkRowPoss(int arr[], short sudokuBoard[][SIZE], int row);
void checkBoxPoss(int arr[], short sudokuBoard[][SIZE], int row, int col);
void updateRow(int row, short num, short board[][SIZE], Array*** possibilities);		  //updates the poss of the cell's row
void updateCol(int col, short num, short board[][SIZE], Array*** possibilities);		  //updates the poss of the cell's coll
void updateBox(int row, int col, short num, short board[][SIZE], Array*** possibilities); //updates the poss of the cell's in the box
void checkMemory(void* check);///////////////////gen
void generateBoard(short board[][SIZE], Array*** possibilities, int* numOfCellsPicked);
int amountOfPlayers();
void initializeBoard(playerDetails* player, int* numOfCellsFirstFilled); 
void freePossibilities(Array*** possibilities);
#endif // !_generalsudoku
