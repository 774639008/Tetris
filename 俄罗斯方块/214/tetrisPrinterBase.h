#ifndef _TERISPRINTERBASH_H_
#define _TERISPRINTERBASH_H_
#include "tetrisLogicModel.h"

// 显示游戏池边界
void printPoolBorder();

// 显示当前方块
void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control);

// 移除方块
void removeTetris(TetrisManager *manager);

#endif // _TERISPRINTERBASH_H_
