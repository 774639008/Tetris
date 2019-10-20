#include "tetrisLogicProcess.h"
#include "tetrisLogicModel.h"

/*****************************************************************************************************************
* 函数名称：void rotateTetris(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 旋转方块 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void rotateTetris(TetrisManager *manager, TetrisControl *control)
{
    char ori = manager->orientation[0];  // 记录原旋转状态

    removeTetris(manager);  // 移走当前方块

    // 顺/逆时针旋转
    manager->orientation[0] =
            (control->clockwise) ? ((ori + 1) & 3) : ((ori + 3) & 3);

    if (checkCollision(manager))  // 检测到碰撞
    {
        manager->orientation[0] = ori;  // 恢复为原旋转状态
        insertTetris(manager);  // 放入当前方块。由于状态没改变，不需要设置颜色
    }
    else
    {
        insertTetris(manager);  // 放入当前方块
        printCurrentTetris(manager, control);  // 显示当前方块
    }
}


/*****************************************************************************************************************
* 函数名称：void horzMoveTetris(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 水平移动方块 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void horzMoveTetris(TetrisManager *manager, TetrisControl *control)
{
    char x = manager->x;  // 记录原列位置

    removeTetris(manager);  // 移走当前方块
    control->direction == 0 ? (--manager->x) : (++manager->x);  // 左/右移动

    if (checkCollision(manager))  // 检测到碰撞
    {
        manager->x = x;  // 恢复为原列位置
        insertTetris(manager);  // 放入当前方块。由于位置没改变，不需要设置颜色
    }
    else
    {
        insertTetris(manager);  // 放入当前方块
        printCurrentTetris(manager, control);  // 显示当前方块
    }
}


/*****************************************************************************************************************
* 函数名称：void dropDownTetris(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 方块直接落地 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void dropDownTetris(TetrisManager *manager, TetrisControl *control)
{
    removeTetris(manager);  // 移走当前方块
    for (; manager->y < ROW_END; ++manager->y)  // 从上往下
    {
        if (checkCollision(manager))  // 检测到碰撞
        {
            break;
        }
    }
    --manager->y;  // 上移一格当然没有碰撞

    insertTetris(manager);  // 放入当前方块

    checkErasing(manager, control);  // 检测消行
    printTetrisPool(manager, control);  // 显示游戏池
}


/*****************************************************************************************************************
* 函数名称：void moveDownTetris(TetrisManager *manager, TetrisControl *control)
* 功能描述：
*			 实现 向下移动方块 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体
* 返回值：0
******************************************************************************************************************/

void moveDownTetris(TetrisManager *manager, TetrisControl *control)
{
    char y = manager->y;  // 记录原行位置

    removeTetris(manager);  // 移走当前方块
    ++manager->y;  // 向下移动

    if (checkCollision(manager))  // 检测到碰撞
    {
        manager->y = y;  // 恢复为原行位置
        insertTetris(manager);  // 放入当前方块。由于位置没改变，不需要设置颜色
        if (checkErasing(manager, control))  // 检测到消行
        {
            printTetrisPool(manager, control);  // 显示游戏池
        }
    }
    else
    {
        insertTetris(manager);  // 放入当前方块
        printCurrentTetris(manager, control);  // 显示当前方块
    }
}


/*****************************************************************************************************************
* 函数名称：void keydownControl(TetrisManager *manager, TetrisControl *control, int key)
* 功能描述：
*			 实现 键按下 的功能
* 参数说明：
*           TetrisManager *manager 游戏控制结构体 TetrisControl *control 方块控制结构体  int key 按键的值
* 返回值：0
******************************************************************************************************************/

void keydownControl(TetrisManager *manager, TetrisControl *control, int key)
{
    if (key == '1')  // 暂停/解除暂停
    {
        control->pause = !control->pause;
    }

    if (control->pause)  // 暂停状态，不作处理
    {
        return;
    }

    switch (key)
    {
    case 72:  // 上
        control->clockwise = true;  // 顺时针旋转
        rotateTetris(manager, control);  // 旋转方块
        break;
    case 75:  // 左
        control->direction = 0;  // 向左移动
        horzMoveTetris(manager, control);  // 水平移动方块
        break;
    case 77:  // 右
        control->direction = 1;  // 向右移动
        horzMoveTetris(manager, control);  // 水平移动方块
        break;
    case ' ':  // 下
        moveDownTetris(manager, control);  // 向下移动方块
        break;
    case 80:  // 直接落地
        dropDownTetris(manager, control);
        break;
    case '0':  // 反转
        control->clockwise = false;  // 逆时针旋转
        rotateTetris(manager, control);  // 旋转方块
        break;
    case 27:
        manager->dead = 1;
        break;
    default:
        break;
    }
}
