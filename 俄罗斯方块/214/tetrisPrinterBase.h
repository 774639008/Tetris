#ifndef _TERISPRINTERBASH_H_
#define _TERISPRINTERBASH_H_
#include "tetrisLogicModel.h"

// ��ʾ��Ϸ�ر߽�
void printPoolBorder();

// ��ʾ��ǰ����
void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control);

// �Ƴ�����
void removeTetris(TetrisManager *manager);

#endif // _TERISPRINTERBASH_H_
