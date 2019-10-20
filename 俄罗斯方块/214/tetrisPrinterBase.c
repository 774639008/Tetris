#include "tetrisPrinterBase.h"
#include "tetrisLogicModel.h"
#include "public.h"
#include "snakerecord.h"

extern unsigned short gs_uTetrisTable[7][4];
extern unsigned short gs_uInitialTetrisPool[28];

HANDLE g_hConsoleOutput;  // ����̨������

extern char *p;


/*****************************************************************************************************************
* �������ƣ�void gotoxyWithFullwidth(short x, short y)
* ����������
*			 ʵ��  ��ȫ�Ƕ�λ �Ĺ���
* ����˵����
*           x ������ y ������
* ����ֵ��0
******************************************************************************************************************/

void gotoxyWithFullwidth(short x, short y)
{
    static COORD cd;

    cd.X = (short) (x << 1);
    cd.Y = y;
    SetConsoleCursorPosition(g_hConsoleOutput, cd);
}


/*****************************************************************************************************************
* �������ƣ�void printPoolBorder()
* ����������
*			 ʵ��  ��ʾ��Ϸ�ر߽� �Ĺ���
* ����˵����
*
* ����ֵ��0
******************************************************************************************************************/

void printPoolBorder()
{
    char y,x;

 //   char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

     //printf("%s \n",cl);

   // SetConsoleTextAttribute(g_hConsoleOutput, 0xF0);
    for(y = ROW_BEGIN; y < ROW_END; ++y)  // ����ʾ����4�к͵ײ�2��
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
 //   gotoxy(10, y - 3);  // �ײ��߽�
    printf("%s",p);
    }

 //   printf("--------------");
}

// ��λ����Ϸ���еķ���
#define gotoxyInPool(x, y) gotoxyWithFullwidth(x + 9, y - 3)


/*****************************************************************************************************************
* �������ƣ�void printTetrisPool(const TetrisManager *manager, const TetrisControl *control)
* ����������
*			 ʵ��  ��ʾ��Ϸ�� �Ĺ���
* ����˵����
*            TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void printTetrisPool(const TetrisManager *manager, const TetrisControl *control)
{
    char x, y;

 //   char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

    for (y = ROW_BEGIN; y < ROW_END; ++y)  // ����ʾ����4�к͵ײ�2��
    {
        //gotoxy(11, y-3);
        gotoxyInPool(2, y);
        //gotoxyWithFullwidth(11, y-3);
        // ���㵽��Ϸ���еķ���
        for (x = COL_BEGIN; x < COL_END; ++x)  // ����ʾ���ұ߽�
        {
            if ((manager->pool[y] >> x) & 1)  // ��Ϸ�ظ÷����з���
            {
                // ����Ӧ��ɫ����ʾһ��ʵ�ķ���
                SetConsoleTextAttribute(g_hConsoleOutput, 7);
                printf("%s",p);
            }
            else  // û�з��飬��ʾ�հ�
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 0);
                printf("%2s","");
            }
        }
    }
    gotoxy(0,0);
}


/*****************************************************************************************************************
* �������ƣ�void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control)
* ����������
*			 ʵ��  ��ʾ��ǰ���� �Ĺ���
* ����˵����
*            TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void printCurrentTetris(const TetrisManager *manager,const TetrisControl *control)
{
    char x, y;

//    char *p = (char *)malloc(sizeof(char *));
 //   strcpy(p,read_char("data/TetrisCharactor.txt"));

    // ��ʾ��ǰ���������ƶ�����õģ�Ϊ��ȥ�ƶ�ǰ�ķ��飬��Ҫ��չ��ʾ����
    // ���ڲ����������ƶ����ʲ���Ҫ������չ
    y = (manager->y > ROW_BEGIN) ? (manager->y - 1) : ROW_BEGIN;  // ������չһ��
    for (; y < ROW_END && y < manager->y + 4; ++y)
    {
        x = (manager->x > COL_BEGIN) ? (manager->x - 1) : COL_BEGIN;  // ������չһ��
        for (; x < COL_END && x < manager->x + 5; ++x)  // ������չһ��
        {
          //  gotoxy(x+9, y-3);
          gotoxyInPool(x, y);
          // gotoxyWithFullwidth(x+9, y-3);
            // ���㵽��Ϸ���еķ���
            if ((manager->pool[y] >> x) & 1)  // ��Ϸ�ظ÷����з���
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 7);
                printf("%s",p);
            }
            else  // û�з��飬��ʾ�հ�
            {
                SetConsoleTextAttribute(g_hConsoleOutput, 0);
                printf("%2s","");
            }
        }
    }
    gotoxy(0,0);
}


/*****************************************************************************************************************
* �������ƣ�void removeTetris(TetrisManager *manager)
* ����������
*			 ʵ��  �Ƴ����� �Ĺ���
* ����˵����
*            TetrisManager *manager ��Ϸ���ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void removeTetris(TetrisManager *manager)
{
    // ��ǰ����
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

    // ��ǰ����ÿ4λȡ������λȡ����λ�뵽��Ϸ����Ӧλ�ã�������Ƴ�����
    manager->pool[manager->y + 0] &=
            ~(((tetris >> 0x0) & 0x000F) << manager->x);
    manager->pool[manager->y + 1] &=
            ~(((tetris >> 0x4) & 0x000F) << manager->x);
    manager->pool[manager->y + 2] &=
            ~(((tetris >> 0x8) & 0x000F) << manager->x);
    manager->pool[manager->y + 3] &=
            ~(((tetris >> 0xC) & 0x000F) << manager->x);
}

// ��ʾ��һ��������һ������
void printNextTetris(const TetrisManager *manager)
{
    char i;
    unsigned short tetris;

    // �߿�
    SetConsoleTextAttribute(g_hConsoleOutput, 0xF);

    // ��һ��������Ӧ��ɫ��ʾ
    tetris = gs_uTetrisTable[manager->type[1]][manager->orientation[1]];
    SetConsoleTextAttribute(g_hConsoleOutput,7);
    for (i = 0; i < 16; ++i) {
        gotoxyWithFullwidth((i & 3) + 2, (i >> 2) + 10);
        ((tetris >> i) & 1) ? printf("%s",p) : printf("%2s", "");
    }
}
