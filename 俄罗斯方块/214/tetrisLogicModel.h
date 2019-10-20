#ifndef _TETRISLOGICMODEL_H_
#define _TETRISLOGICMODEL_H_
#include "public.h"

#define COL_BEGIN 2
#define COL_END 14
#define ROW_BEGIN 4
#define ROW_END 26

// ����ṹ��洢��Ϸ�������
typedef struct TetrisManager
{
    unsigned short pool[28];  // ��Ϸ��
    char x;  // ��ǰ����x���꣬�˴�����Ϊ�������Ͻ�����
    char y;  // ��ǰ����y����
    char type[3];  // ��ǰ����һ��������һ����������
    char orientation[3];  // ��ǰ����һ��������һ��������ת״̬
    char score;  // �÷�
    char erasedCount[4];  // ������
    char erasedTotal;  // ��������
    char tetrisCount[7];  // ��������
    char tetrisTotal;  // ��������
    bool dead;  // ����
}TetrisManager;

// ����ṹ��洢�����������
typedef struct TetrisControl
{
    bool pause;  // ��ͣ
    bool clockwise;  // ��ת����˳ʱ��Ϊtrue
    char direction;  // �ƶ�����0�����ƶ� 1�����ƶ�
}TetrisControl;

#endif // _TETRISLOGICMODEL_H_
