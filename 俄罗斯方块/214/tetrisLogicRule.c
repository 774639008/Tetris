#include "tetrisLogicRule.h"
#include "tetrisLogicModel.h"

extern unsigned short gs_uTetrisTable[7][4];
extern unsigned short gs_uInitialTetrisPool[28];

extern  HANDLE g_hConsoleOutput;


/*****************************************************************************************************************
* �������ƣ�void initGame(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ��ʼ����Ϸ �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void initGame(TetrisManager *manager, TetrisControl *control)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ

    g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ����̨������
    SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // ���ù������
    SetConsoleTitleA("����˹����");
    restartGame(manager, control);
}


/*****************************************************************************************************************
* �������ƣ�void runGame(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ������Ϸ �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void runGame(TetrisManager *manager, TetrisControl *control,float time)
{
    clock_t clockLast, clockNow;

    clockLast = clock();  // ��ʱ
    printTetrisPool(manager, control);  // ��ʾ��Ϸ��

    while (!manager->dead)  // û��
    {
        while (_kbhit())  // �м�����
        {
            keydownControl(manager, control, _getch());  // ������
        }

        if (!control->pause)  // δ��ͣ
        {
            clockNow = clock();  // ��ʱ
            // ���μ�ʱ�ļ������0.45��
            if (clockNow - clockLast > time * CLOCKS_PER_SEC )
            {
                clockLast = clockNow;
                keydownControl(manager, control, ' ');  // ����������
            }
        }
    }
}


/*****************************************************************************************************************
* �������ƣ�void restartGame(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ���¿�ʼ��Ϸ �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void restartGame(TetrisManager *manager, TetrisControl *control)
{
    memset(manager, 0, sizeof(TetrisManager));  // ȫ����0

    // ��ʼ����Ϸ��
    memcpy(manager->pool,gs_uInitialTetrisPool, sizeof(unsigned short[28]));
    srand((unsigned) time(NULL ));  // �����������

    manager->type[1] = rand() % 7;  // ��һ��
    manager->orientation[1] = rand() & 3;

    manager->type[2] = rand() % 7;  // ����һ��
    manager->orientation[2] = rand() & 3;

    memset(control, 0, sizeof(TetrisControl));  // ȫ����0

    giveTetris(manager);  // ����һ������
}


/*****************************************************************************************************************
* �������ƣ�void giveTetris(TetrisManager *manager)
* ����������
*			 ʵ�� ��һ������ �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void giveTetris(TetrisManager *manager)
{
    unsigned short tetris;

    manager->type[0] = manager->type[1];  // ��һ��������Ϊ��ǰ
    manager->orientation[0] = manager->orientation[1];

    manager->type[1] = manager->type[2];  // ����һ���÷���Ϊ��һ��
    manager->orientation[1] = manager->orientation[2];

    manager->type[2] = rand() % 7;  // �����������һ������
    manager->orientation[2] = rand() & 3;

    tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]]; // ��ǰ����

    // ���õ�ǰ����y���꣬��֤�ո���ʱֻ��ʾ����������һ��
    // ����ʵ��ʹ����ҿ����Ժܿ���ٶȽ��������ڲ���ʾ�����Ķ���4����
    if (tetris & 0xF000)
    {
        manager->y = 0;
    }
    else
    {
        manager->y = (tetris & 0xFF00) ? 1 : 2;
    }
    manager->x = 6;  // ���õ�ǰ����x����

    if (checkCollision(manager))  // ��⵽��ײ
    {
        manager->dead = true;  // �����Ϸ����
    }
    else  // δ��⵽��ײ
    {
        insertTetris(manager);  // ����ǰ���������Ϸ��
    }

    ++manager->tetrisTotal;  // ��������
    ++manager->tetrisCount[manager->type[0]];  // ��Ӧ������

    printNextTetris(manager);  // ��ʾ��һ������
    printScore(manager);  // ��ʾ�÷���Ϣ
}


/*****************************************************************************************************************
* �������ƣ�bool checkCollision(const TetrisManager *manager)
* ����������
*			 ʵ�� ��ײ��� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

bool checkCollision(const TetrisManager *manager)
{
    // ��ǰ����
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];
    unsigned short dest = 0;

    // ��ȡ��ǰ��������Ϸ���е�����
    // ��Ϸ������x y��С������Ϣ�����͵��ߴ����16λ�޷�������
    dest |= (((manager->pool[manager->y + 0] >> manager->x) << 0x0) & 0x000F);
    dest |= (((manager->pool[manager->y + 1] >> manager->x) << 0x4) & 0x00F0);
    dest |= (((manager->pool[manager->y + 2] >> manager->x) << 0x8) & 0x0F00);
    dest |= (((manager->pool[manager->y + 3] >> manager->x) << 0xC) & 0xF000);

    // ����ǰ������Ŀ����������ص�����ײ������λ��Ľ����Ϊ0
    return ((dest & tetris) != 0);
}


/*****************************************************************************************************************
* �������ƣ�void insertTetris(TetrisManager *manager)
* ����������
*			 ʵ�� ���뷽�� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void insertTetris(TetrisManager *manager)
{
    // ��ǰ����
    unsigned short tetris = gs_uTetrisTable[manager->type[0]][manager->orientation[0]];

    // ��ǰ����ÿ4λȡ����λ����Ϸ����Ӧλ�ã�����ɲ��뷽��
    manager->pool[manager->y + 0] |= (((tetris >> 0x0) & 0x000F) << manager->x);
    manager->pool[manager->y + 1] |= (((tetris >> 0x4) & 0x000F) << manager->x);
    manager->pool[manager->y + 2] |= (((tetris >> 0x8) & 0x000F) << manager->x);
    manager->pool[manager->y + 3] |= (((tetris >> 0xC) & 0x000F) << manager->x);
}


/*****************************************************************************************************************
* �������ƣ�bool checkErasing(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ��  ���м�� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

bool checkErasing(TetrisManager *manager, TetrisControl *control)
{
  //  static const unsigned scores[5] = { 10, 10, 10, 10, 10 };  // ���е÷�
    char count = 0;
    char k = 0, y = manager->y + 3;  // �������ϼ��

    do {
        if (y < ROW_END && manager->pool[y] == 0xFFFFU)  // ��Ч��������һ��������
        {
            ++count;
            // ����һ�з���

            memmove(manager->pool + 1, manager->pool, sizeof(unsigned short) * y);
        }
        else
        {
            --y;
            ++k;
        }
    } while (y >= manager->y && k < 4);

    manager->erasedTotal += count;  // ��������
    //manager->score += scores[count];  // �÷�
   // manager->score += 10;  // �÷�
    manager->score += (1*count);
    if (count > 0)
    {
        ++manager->erasedCount[count - 1];  // ����
    }

    giveTetris(manager);  // ����һ������

    return (count > 0);
}

