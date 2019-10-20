#ifndef _TERISLOGICRULE_H_
#define _TERISLOGICRULE_H_
#include <stdbool.h>
#include "tetrisLogicModel.h"

//������Ϸ
void runGame(TetrisManager *manager, TetrisControl *control,float time);

// ��ʼ����Ϸ
void initGame(TetrisManager *manager, TetrisControl *control);

// ��ײ���
bool checkCollision(const TetrisManager *manager);

// ���뷽��
void insertTetris(TetrisManager *manager);

#endif // _TERISLOGICRULE_H_
