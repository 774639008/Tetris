#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define KEY_UP 72			//宏定义向上按键为 72
#define KEY_LEFT 75			//宏定义向左按键为 75
#define KEY_DOWN 80			//宏定义向下按键为 80
#define KEY_RIGHT 77		//宏定义向右按键为 77
#define KEY_STOP 27			//宏定义ESC按键为 27

#define MOD 28
#define SIZE_N 19
#define SIZE_M 12

typedef struct block
{
     int x;
     int y;
     int blockType;
     int blockDirect;
}Block;

/*用户结构体*/
typedef struct uses
{
    char name[20];
    char score[20];
}user;

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext);   //输入控制函数

int select_interface(int max);          //选项选择

int gotoxy(int x,int y);                //光标打印函数

char * public_num(char *ch);            //打印数字函数

void public_char(char *acBuf);          //打印字符函数



#endif



