#ifndef _TETRISLOGICPROCESS_H_
#define _TETRISLOGICPROCESS_H_

#include "tetrisLogicModel.h"

// 旋转方块
void rotateTetris(TetrisManager *manager, TetrisControl *control);

// 水平移动方块
void horzMoveTetris(TetrisManager *manager, TetrisControl *control);

// 向下移动方块
void moveDownTetris(TetrisManager *manager, TetrisControl *control);

// 向下移动方块
void dropDownTetris(TetrisManager *manager, TetrisControl *control);

// 键按下
void keydownControl(TetrisManager *manager, TetrisControl *control, int key);

#endif // _TETRISLOGICPROCESS_H_
