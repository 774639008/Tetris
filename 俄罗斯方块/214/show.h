#ifndef _SHOW_H_
#define _SHOW_H_
#include "tetrisLogicModel.h"

void main_menu(); //���˵���ʾ

void sub_menu();  //�β˵���ʾ

void Finish(TetrisManager *manager);   //��Ϸ������ʾ

void GoRank(TetrisManager *manager);   //��Ϸ�ϰ���ʾ

void printScore(const TetrisManager *manager); //��ӡ����

void user_show(char select); //�û�����������ʾ

#endif // _SHOW_H_
