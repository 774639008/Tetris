#include "tetrisPrinterBase.h"
#include "tetrisLogicModel.h"
#include "public.h"
#include "snakerecord.h"

extern unsigned short gs_uTetrisTable[7][4];
extern unsigned short gs_uInitialTetrisPool[28];

HANDLE g_hConsoleOutput;  // 控制台输出句柄

extern char *p;


/*****************************************************************************************************************
* 函数名称：void gotoxyWithFullwidth(short x, short y)
* 功能描述：
*			 实现  以全角定位 的功能
* 参数说明：
*           x 横坐标 y 纵坐标
* 返回值：0
******************************************************************************************************************/

void gotoxyWithFullwidth(short x, short y)
{
    static COORD cd;

    cd.X = (short) (x << 1);
    cd.Y = y;
    SetConsoleCursorPosition(g_hConsoleOutput, cd);
}


/*****************************************************************************************************************
* 函数名称：void printPoolBorder()
* 功能描述：
*			 实现  显示游戏池边界 的功能
* 参数说明：
*
* 返回值：0
******************************************************************************************************************/

void printPoolBorder()
{
    char y,x;

 //   char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

     //printf("%s \n",cl);

   // SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
    for(y = ROW_BEGIN; y < ROW_END; ++y)  // 不显示顶部4行和底部2行
    {
     //   gotoxy(10, y - 3);
        gotoxyWithFullwidth(10, y - 3);
        printf("%s",p);
   //     printf("|");
     //   gotoxy(23, y - 3);
        gotoxyWithFullwidth(23, y - 3);
        printf("%s",p);
    //    printf("|");
    }
    for(x = 0;x<14;x++)
    {
    gotoxyWithFullwidth(10+x, y - 3);
 //   gotoxy(10, y - 3);  // 底部边界
    printf("%s",p);
    }

 //   printf("--------------");
}

// 定位到游戏池中的方格
#define gotoxyInPool(x, y) gotoxyWithFullwidth(x + 9, y - 3)


/*****************************************************************************************************************
* 函数名称：void printTetrisPool(const TetrisManager *manager, const TetrisControl *control)
* 功能描述：
*			 实现  显示游戏池 的功能
* 参数说明：
*            TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void printTetrisPool(const TetrisManager *manager, const TetrisControl *control)
{
    char x, y;

 //   char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

    for (y = ROW_BEGIN; y < ROW_END; ++y)  // 不显示顶部4行和底部2行
    {
        //gotoxy(11, y-3);
        gotoxyInPool(2, y);
        //gotoxyWithFullwidth(11, y-3);
        // 定点到游戏池中的方格
        for (x = COL_BEGIN; x < COL_END; ++x)  // 不显示左右边界
        {
            if ((manager->pool[y] >> x) & 1)  // 游戏池该方格有方块
            {
                // 用相应颜色，显示一个实心方块
                SetConsoleTextAttribute(g_hConsoleOutput, 7);
                printf("%s",p);
            }
            else  // 没有方块，显示空白
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 0);
                printf("%2s","");
            }
        }
    }
    gotoxy(0,0);
}


/*****************************************************************************************************************
* 函数名称：void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control)
* 功能描述：
*			 实现  显示当前方块 的功能
* 参数说明：
*            TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control)
{
    char x, y;

//    char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

    // 显示当前方块是在移动后调用的，为擦去移动前的方块，需要扩展显示区域
    // 由于不可能向上移动，故不需要向下扩展
    y = (manager->y > ROW_BEGIN) ? (manager->y - 1) : ROW_BEGIN;  // 向上扩展一格
    for (; y < ROW_END && y < manager->y + 4; ++y)
    {
        x = (manager->x > COL_BEGIN) ? (manager->x - 1) : COL_BEGIN;  // 向左扩展一格
        for (; x < COL_END && x < manager->x + 5; ++x)  // 向右扩展一格
        {
          //  gotoxy(x+9, y-3);
          gotoxyInPool(x, y);
          // gotoxyWithFullwidth(x+9, y-3);
            // 定点到游戏池中的方格
            if ((manager->pool[y] >> x) & 1)  // 游戏池该方格有方块
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 7);
                printf("%s",p);
            }
            else  // 没有方块，显示空白
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 0);
                printf("%2s","");
            }
        }
    }
    gotoxy(0,0);
}


/*****************************************************************************************************************
* 函数名称：void removeTetris(TetrisManager *manager)
* 功能描述：
*			 实现  移除方块 的功能
* 参数说明：
*            TetrisManager *manager 游戏控制结构体
* 返回值：0
******************************************************************************************************************/

void removeTetris(TetrisManager *manager)
{
    // 当前方块
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

    // 当前方块每4位取出，按位取反后位与到游戏池相应位置，即完成移除方块
    manager->pool[manager->y + 0] &=
            ~(((tetris >> 0x0) & 0x000F) << manager->x);
    manager->pool[manager->y + 1] &=
            ~(((tetris >> 0x4) & 0x000F) << manager->x);
    manager->pool[manager->y + 2] &=
            ~(((tetris >> 0x8) & 0x000F) << manager->x);
    manager->pool[manager->y + 3] &=
            ~(((tetris >> 0xC) & 0x000F) << manager->x);
}

// 显示下一个和下下一个方块
void printNextTetris(const TetrisManager *manager)
{
    char i;
    unsigned short tetris;

    // 边框
    SetConsoleTextAttribute(g_hConsoleOutput, 0xF);

    // 下一个，用相应颜色显示
    tetris = gs_uTetrisTable[manager->type[1]][manager->orientation[1]];
    SetConsoleTextAttribute(g_hConsoleOutput,7);
    for (i = 0; i < 16; ++i) {
        gotoxyWithFullwidth((i & 3) + 2, (i >> 2) + 10);
        ((tetris >> i) & 1) ? printf("%s",p) : printf("%2s", "");
    }
}
