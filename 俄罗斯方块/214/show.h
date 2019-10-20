#ifndef _SHOW_H_
#define _SHOW_H_
#include "tetrisLogicModel.h"

void main_menu(); //主菜单显示

void sub_menu();  //次菜单显示

void Finish(TetrisManager *manager);   //游戏结束显示

void GoRank(TetrisManager *manager);   //游戏上榜显示

void printScore(const TetrisManager *manager); //打印分数

void user_show(char select); //用户排名分数显示

#endif // _SHOW_H_
