#include "tetrisLogicRule.h"
#include "tetrisLogicModel.h"

extern unsigned short gs_uTetrisTable[7][4];
extern unsigned short gs_uInitialTetrisPool[28];

extern  HANDLE g_hConsoleOutput;


/*****************************************************************************************************************
* 函数名称：void initGame(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 初始化游戏 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void initGame(TetrisManager *manager, TetrisControl *control)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // 光标信息

    g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取控制台输出句柄
    SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // 设置光标隐藏
    SetConsoleTitleA("俄罗斯方块");
    restartGame(manager, control);
}


/*****************************************************************************************************************
* 函数名称：void runGame(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 运行游戏 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void runGame(TetrisManager *manager, TetrisControl *control,float time)
{
    clock_t clockLast, clockNow;

    clockLast = clock();  // 计时
    printTetrisPool(manager, control);  // 显示游戏池

    while (!manager->dead)  // 没挂
    {
        while (_kbhit())  // 有键按下
        {
            keydownControl(manager, control, _getch());  // 处理按键
        }

        if (!control->pause)  // 未暂停
        {
            clockNow = clock();  // 计时
            // 两次记时的间隔超过0.45秒
            if (clockNow - clockLast > time * CLOCKS_PER_SEC )
            {
                clockLast = clockNow;
                keydownControl(manager, control, ' ');  // 方块往下移
            }
        }
    }
}


/*****************************************************************************************************************
* 函数名称：void restartGame(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 重新开始游戏 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void restartGame(TetrisManager *manager, TetrisControl *control)
{
    memset(manager, 0, sizeof(TetrisManager));  // 全部置0

    // 初始化游戏池
    memcpy(manager->pool,gs_uInitialTetrisPool, sizeof(unsigned short[28]));
    srand((unsigned) time(NULL ));  // 设置随机种子

    manager->type[1] = rand() % 7;  // 下一个
    manager->orientation[1] = rand() & 3;

    manager->type[2] = rand() % 7;  // 下下一个
    manager->orientation[2] = rand() & 3;

    memset(control, 0, sizeof(TetrisControl));  // 全部置0

    giveTetris(manager);  // 给下一个方块
}


/*****************************************************************************************************************
* 函数名称：void giveTetris(TetrisManager *manager)
* 功能描述：
*			 实现 给一个方块 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体
* 返回值：0
******************************************************************************************************************/

void giveTetris(TetrisManager *manager)
{
    unsigned short tetris;

    manager->type[0] = manager->type[1];  // 下一个方块置为当前
    manager->orientation[0] = manager->orientation[1];

    manager->type[1] = manager->type[2];  // 下下一个置方块为下一个
    manager->orientation[1] = manager->orientation[2];

    manager->type[2] = rand() % 7;  // 随机生成下下一个方块
    manager->orientation[2] = rand() & 3;

    tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // 当前方块

    // 设置当前方块y坐标，保证刚给出时只显示方块最下面一行
    // 这种实现使得玩家可以以很快的速度将方块落在不显示出来的顶部4行内
    if (tetris & 0xF000)
    {
        manager->y = 0;
    }
    else
    {
        manager->y = (tetris & 0xFF00) ? 1 : 2;
    }
    manager->x = 6;  // 设置当前方块x坐标

    if (checkCollision(manager))  // 检测到碰撞
    {
        manager->dead = true;  // 标记游戏结束
    }
    else  // 未检测到碰撞
    {
        insertTetris(manager);  // 将当前方块加入游戏池
    }

    ++manager->tetrisTotal;  // 方块总数
    ++manager->tetrisCount[manager->type[0]];  // 相应方块数

    printNextTetris(manager);  // 显示下一个方块
    printScore(manager);  // 显示得分信息
}


/*****************************************************************************************************************
* 函数名称：bool checkCollision(const TetrisManager *manager)
* 功能描述：
*			 实现 碰撞检测 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体
* 返回值：0
******************************************************************************************************************/

bool checkCollision(const TetrisManager *manager)
{
    // 当前方块
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];
    unsigned short dest = 0;

    // 获取当前方块在游戏池中的区域：
    // 游戏池坐标x y处小方格信息，按低到高存放在16位无符号数中
    dest |= (((manager->pool[manager->y + 0] >> manager->x) << 0x0) & 0x000F);
    dest |= (((manager->pool[manager->y + 1] >> manager->x) << 0x4) & 0x00F0);
    dest |= (((manager->pool[manager->y + 2] >> manager->x) << 0x8) & 0x0F00);
    dest |= (((manager->pool[manager->y + 3] >> manager->x) << 0xC) & 0xF000);

    // 若当前方块与目标区域存在重叠（碰撞），则位与的结果不为0
    return ((dest & tetris) != 0);
}


/*****************************************************************************************************************
* 函数名称：void insertTetris(TetrisManager *manager)
* 功能描述：
*			 实现 插入方块 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体
* 返回值：0
******************************************************************************************************************/

void insertTetris(TetrisManager *manager)
{
    // 当前方块
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

    // 当前方块每4位取出，位或到游戏池相应位置，即完成插入方块
    manager->pool[manager->y + 0] |= (((tetris >> 0x0) & 0x000F) << manager->x);
    manager->pool[manager->y + 1] |= (((tetris >> 0x4) & 0x000F) << manager->x);
    manager->pool[manager->y + 2] |= (((tetris >> 0x8) & 0x000F) << manager->x);
    manager->pool[manager->y + 3] |= (((tetris >> 0xC) & 0x000F) << manager->x);
}


/*****************************************************************************************************************
* 函数名称：bool checkErasing(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现  消行检测 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

bool checkErasing(TetrisManager *manager, TetrisControl *control)
{
  //  static const unsigned scores[5] = { 10, 10, 10, 10, 10 };  // 消行得分
    char count = 0;
    char k = 0, y = manager->y + 3;  // 从下往上检测

    do {
        if (y < ROW_END && manager->pool[y] == 0xFFFFU)  // 有效区域内且一行已填满
        {
            ++count;
            // 消除一行方块

            memmove(manager->pool + 1, manager->pool, sizeof(unsigned short) * y);
        }
        else
        {
            --y;
            ++k;
        }
    } while (y >= manager->y && k < 4);

    manager->erasedTotal += count;  // 消行总数
    //manager->score += scores[count];  // 得分
   // manager->score += 10;  // 得分
    manager->score += (1*count);
    if (count > 0)
    {
        ++manager->erasedCount[count - 1];  // 消行
    }

    giveTetris(manager);  // 给下一个方块

    return (count > 0);
}

