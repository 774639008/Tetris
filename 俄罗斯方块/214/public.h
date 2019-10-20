#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define KEY_UP 72			//�궨�����ϰ���Ϊ 72
#define KEY_LEFT 75			//�궨�����󰴼�Ϊ 75
#define KEY_DOWN 80			//�궨�����°���Ϊ 80
#define KEY_RIGHT 77		//�궨�����Ұ���Ϊ 77
#define KEY_STOP 27			//�궨��ESC����Ϊ 27

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

/*�û��ṹ��*/
typedef struct uses
{
    char name[20];
    char score[20];
}user;

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext);   //������ƺ���

int select_interface(int max);          //ѡ��ѡ��

int gotoxy(int x,int y);                //����ӡ����

char * public_num(char *ch);            //��ӡ���ֺ���

void public_char(char *acBuf);          //��ӡ�ַ�����



#endif



