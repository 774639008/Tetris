#ifndef _TETRISLOGICMODEL_H_
#define _TETRISLOGICMODEL_H_
#include "public.h"

#define COL_BEGIN 2
#define COL_END 14
#define ROW_BEGIN 4
#define ROW_END 26

// 这个结构体存储游戏相关数据
typedef struct TetrisManager
{
    unsigned short pool[28];  // 游戏池
    char x;  // 当前方块x坐标，此处坐标为方块左上角坐标
    char y;  // 当前方块y坐标
    char type[3];  // 当前、下一个和下下一个方块类型
    char orientation[3];  // 当前、下一个和下下一个方块旋转状态
    char score;  // 得分
    char erasedCount[4];  // 消行数
    char erasedTotal;  // 消行总数
    char tetrisCount[7];  // 各方块数
    char tetrisTotal;  // 方块总数
    bool dead;  // 死亡
}TetrisManager;

// 这个结构体存储控制相关数据
typedef struct TetrisControl
{
    bool pause;  // 暂停
    bool clockwise;  // 旋转方向：顺时针为true
    char direction;  // 移动方向：0向左移动 1向右移动
}TetrisControl;

#endif // _TETRISLOGICMODEL_H_
