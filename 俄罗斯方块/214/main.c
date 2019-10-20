#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "list.h"
#include "file.h"
#include "public.h"
#include "show.h"
#include "tetrisLogicModel.h"
#include "tetrisPrinterBase.h"
#include "tetrisLogicRule.h"

#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define RET -3

pNode *phead = NULL;

extern HANDLE g_hConsoleOutput;


FILE *bfp = NULL;  //简单
FILE *pfp = NULL;  //普通
FILE *dfp = NULL;  //困难

char btype = 0;    //简单
char ptype = 0;    //普通
char dtype = 0;    //困难
char *p = NULL;

int main()
{
    TetrisManager tetrisManager;
    TetrisControl tetrisControl;
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // 光标信息
    g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取控制台输出句柄
    SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // 设置光标隐藏
    phead = LIST_Init(NULL);
    p = (char *)malloc(sizeof(char *));
    strcpy(p,read_char("data/TetrisCharactor.txt"));
    char flag = 0;
    while(1)
    {
        system("cls");
        main_menu();
        gotoxy(15,0);
        printf("<-");
        gotoxy(0,0);
        switch(select_interface(2))
        {
        case ONE:      //游戏开始界面
            {
                while(1)
                {
                    system("cls");
                    sub_menu();
                    gotoxy(15,0);
                    printf("<-");
                    gotoxy(0,0);
                    switch(select_interface(4))
                    {
                    case ONE:    //初级难度
                        {
                            system("cls");
                            bfp = FILE_open("data/beginer.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // 初始化游戏
                            do
                            {
                               //   printScore(&tetrisManager);   //打印分数
                                  printPoolBorder();  // 显示游戏池边界
                                  runGame(&tetrisManager, &tetrisControl,0.45F);  // 运行游戏
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // 清屏
                                  if(data_to_file(&tetrisManager) == 1)
                                  {
                                      break;
                                  }
                                  else
                                  {
                                      break;
                                  }
                            }
                            while(1);
                        }
                        break;
                    case TWO:    //中级难度
                        {
                            system("cls");
                            bfp = FILE_open("data/player.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // 初始化游戏
                            do
                            {
                               //   printScore(&tetrisManager);   //打印分数
                                  printPoolBorder();  // 显示游戏池边界
                                  runGame(&tetrisManager, &tetrisControl,0.30F);  // 运行游戏
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // 清屏
                                  if(data_to_file(&tetrisManager) == 1)
                                  {
                                      break;
                                  }
                                  else
                                  {
                                      break;
                                  }
                            }
                            while(1);
                        }
                        break;
                    case THREE:  //高级难度
                        {
                            system("cls");
                            bfp = FILE_open("data/darker.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // 初始化游戏
                            do
                            {
                               //   printScore(&tetrisManager);   //打印分数
                                  printPoolBorder();  // 显示游戏池边界
                                  runGame(&tetrisManager, &tetrisControl,0.25F);  // 运行游戏
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // 清屏
                                  if(data_to_file(&tetrisManager) == 1)
                                  {
                                      break;
                                  }
                                  else
                                  {
                                      break;
                                  }
                            }
                            while(1);
                        }
                        break;
                    case FOUR:
                        {
                            flag = 1;
                        }
                        break;
                    default:
                        {

                        }
                        break;
                    }
                    if(flag == 1)
                    {
                        break;
                    }
                }
            }
            break;
        case TWO:     //游戏分数界面
            {
                system("cls");
                user_show(1);
                user_show(2);
                user_show(3);
                getch();
            }
            break;
        default:
            {
                printf("error\n");
            }
            break;
        }
    }
    return 1;
}
