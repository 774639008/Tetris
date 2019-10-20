#ifndef _TERISLOGICRULE_H_
#define _TERISLOGICRULE_H_
#include <stdbool.h>
#include "tetrisLogicModel.h"

//运行游戏
void runGame(TetrisManager *manager, TetrisControl *control,float time);

// 初始化游戏
void initGame(TetrisManager *manager, TetrisControl *control);

// 碰撞检测
bool checkCollision(const TetrisManager *manager);

// 插入方块
void insertTetris(TetrisManager *manager);

#endif // _TERISLOGICRULE_H_
