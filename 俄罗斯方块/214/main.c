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


FILE *bfp = NULL;  //��
FILE *pfp = NULL;  //��ͨ
FILE *dfp = NULL;  //����

char btype = 0;    //��
char ptype = 0;    //��ͨ
char dtype = 0;    //����
char *p = NULL;

int main()
{
    TetrisManager tetrisManager;
    TetrisControl tetrisControl;
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ
    g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ����̨������
    SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // ���ù������
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
        case ONE:      //��Ϸ��ʼ����
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
                    case ONE:    //�����Ѷ�
                        {
                            system("cls");
                            bfp = FILE_open("data/beginer.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // ��ʼ����Ϸ
                            do
                            {
                               //   printScore(&tetrisManager);   //��ӡ����
                                  printPoolBorder();  // ��ʾ��Ϸ�ر߽�
                                  runGame(&tetrisManager, &tetrisControl,0.45F);  // ������Ϸ
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // ����
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
                    case TWO:    //�м��Ѷ�
                        {
                            system("cls");
                            bfp = FILE_open("data/player.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // ��ʼ����Ϸ
                            do
                            {
                               //   printScore(&tetrisManager);   //��ӡ����
                                  printPoolBorder();  // ��ʾ��Ϸ�ر߽�
                                  runGame(&tetrisManager, &tetrisControl,0.30F);  // ������Ϸ
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // ����
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
                    case THREE:  //�߼��Ѷ�
                        {
                            system("cls");
                            bfp = FILE_open("data/darker.txt");
                            btype = 1;
                            initGame(&tetrisManager, &tetrisControl);  // ��ʼ����Ϸ
                            do
                            {
                               //   printScore(&tetrisManager);   //��ӡ����
                                  printPoolBorder();  // ��ʾ��Ϸ�ر߽�
                                  runGame(&tetrisManager, &tetrisControl,0.25F);  // ������Ϸ
                                  SetConsoleTextAttribute(g_hConsoleOutput, 0x7);
                                  system("cls");  // ����
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
        case TWO:     //��Ϸ��������
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
