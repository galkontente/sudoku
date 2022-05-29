#ifndef _treehead
#define _treehead
#include "DataTypes.h"
#include "ListLib.h"
#include "TreeLib.h"
#include "GeneralLib.h"

TREE buildTreeFromAPL(Lnode_PlayersList** apl, int size);
TREENODE* buildTreeFromAPLHelper(Lnode_PlayersList** apl, int size);
TREENODE* buildTreeNode(Lnode_PlayersList* data, TREENODE* left, TREENODE* right);
void playTreeInOrder(TREE tr, PlayersList* active, PlayersList* winner, int* pNumberOfWinners);
int playTreeInOrderHelper(TREENODE* node, PlayersList* active, PlayersList* winner);
void freeTree(TREE tr);
void freeTreeHelper(TREENODE* root);

#endif // !_treehead
