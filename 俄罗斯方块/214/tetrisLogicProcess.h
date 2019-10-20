#ifndef _TETRISLOGICPROCESS_H_
#define _TETRISLOGICPROCESS_H_

#include "tetrisLogicModel.h"

// ��ת����
void rotateTetris(TetrisManager *manager, TetrisControl *control);

// ˮƽ�ƶ�����
void horzMoveTetris(TetrisManager *manager, TetrisControl *control);

// �����ƶ�����
void moveDownTetris(TetrisManager *manager, TetrisControl *control);

// �����ƶ�����
void dropDownTetris(TetrisManager *manager, TetrisControl *control);

// ������
void keydownControl(TetrisManager *manager, TetrisControl *control, int key);

#endif // _TETRISLOGICPROCESS_H_
