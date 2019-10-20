#include "tetrisLogicProcess.h"
#include "tetrisLogicModel.h"

/*****************************************************************************************************************
* �������ƣ�void rotateTetris(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ��ת���� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void rotateTetris(TetrisManager *manager, TetrisControl *control)
{
    char ori = manager->orientation[0];  // ��¼ԭ��ת״̬

    removeTetris(manager);  // ���ߵ�ǰ����

    // ˳/��ʱ����ת
    manager->orientation[0] =
            (control->clockwise) ? ((ori + 1) & 3) : ((ori + 3) & 3);

    if (checkCollision(manager))  // ��⵽��ײ
    {
        manager->orientation[0] = ori;  // �ָ�Ϊԭ��ת״̬
        insertTetris(manager);  // ���뵱ǰ���顣����״̬û�ı䣬����Ҫ������ɫ
    }
    else
    {
        insertTetris(manager);  // ���뵱ǰ����
        printCurrentTetris(manager, control);  // ��ʾ��ǰ����
    }
}


/*****************************************************************************************************************
* �������ƣ�void horzMoveTetris(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ˮƽ�ƶ����� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void horzMoveTetris(TetrisManager *manager, TetrisControl *control)
{
    char x = manager->x;  // ��¼ԭ��λ��

    removeTetris(manager);  // ���ߵ�ǰ����
    control->direction == 0 ? (--manager->x) : (++manager->x);  // ��/���ƶ�

    if (checkCollision(manager))  // ��⵽��ײ
    {
        manager->x = x;  // �ָ�Ϊԭ��λ��
        insertTetris(manager);  // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
    }
    else
    {
        insertTetris(manager);  // ���뵱ǰ����
        printCurrentTetris(manager, control);  // ��ʾ��ǰ����
    }
}


/*****************************************************************************************************************
* �������ƣ�void dropDownTetris(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� ����ֱ����� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void dropDownTetris(TetrisManager *manager, TetrisControl *control)
{
    removeTetris(manager);  // ���ߵ�ǰ����
    for (; manager->y < ROW_END; ++manager->y)  // ��������
    {
        if (checkCollision(manager))  // ��⵽��ײ
        {
            break;
        }
    }
    --manager->y;  // ����һ��Ȼû����ײ

    insertTetris(manager);  // ���뵱ǰ����

    checkErasing(manager, control);  // �������
    printTetrisPool(manager, control);  // ��ʾ��Ϸ��
}


/*****************************************************************************************************************
* �������ƣ�void moveDownTetris(TetrisManager *manager, TetrisControl *control)
* ����������
*			 ʵ�� �����ƶ����� �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��
* ����ֵ��0
******************************************************************************************************************/

void moveDownTetris(TetrisManager *manager, TetrisControl *control)
{
    char y = manager->y;  // ��¼ԭ��λ��

    removeTetris(manager);  // ���ߵ�ǰ����
    ++manager->y;  // �����ƶ�

    if (checkCollision(manager))  // ��⵽��ײ
    {
        manager->y = y;  // �ָ�Ϊԭ��λ��
        insertTetris(manager);  // ���뵱ǰ���顣����λ��û�ı䣬����Ҫ������ɫ
        if (checkErasing(manager, control))  // ��⵽����
        {
            printTetrisPool(manager, control);  // ��ʾ��Ϸ��
        }
    }
    else
    {
        insertTetris(manager);  // ���뵱ǰ����
        printCurrentTetris(manager, control);  // ��ʾ��ǰ����
    }
}


/*****************************************************************************************************************
* �������ƣ�void keydownControl(TetrisManager *manager, TetrisControl *control, int key)
* ����������
*			 ʵ�� ������ �Ĺ���
* ����˵����
*           TetrisManager *manager ��Ϸ���ƽṹ�� TetrisControl *control ������ƽṹ��  int key ������ֵ
* ����ֵ��0
******************************************************************************************************************/

void keydownControl(TetrisManager *manager, TetrisControl *control, int key)
{
    if (key == '1')  // ��ͣ/�����ͣ
    {
        control->pause = !control->pause;
    }

    if (control->pause)  // ��ͣ״̬����������
    {
        return;
    }

    switch (key)
    {
    case 72:  // ��
        control->clockwise = true;  // ˳ʱ����ת
        rotateTetris(manager, control);  // ��ת����
        break;
    case 75:  // ��
        control->direction = 0;  // �����ƶ�
        horzMoveTetris(manager, control);  // ˮƽ�ƶ�����
        break;
    case 77:  // ��
        control->direction = 1;  // �����ƶ�
        horzMoveTetris(manager, control);  // ˮƽ�ƶ�����
        break;
    case ' ':  // ��
        moveDownTetris(manager, control);  // �����ƶ�����
        break;
    case 80:  // ֱ�����
        dropDownTetris(manager, control);
        break;
    case '0':  // ��ת
        control->clockwise = false;  // ��ʱ����ת
        rotateTetris(manager, control);  // ��ת����
        break;
    case 27:
        manager->dead = 1;
        break;
    default:
        break;
    }
}
