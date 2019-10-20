#include "show.h"
#include "public.h"
#include "file.h"
#include "list.h"
#include "tetrisLogicModel.h"

extern HANDLE g_hConsoleOutput;
extern pNode *phead;
extern FILE *pfp;
extern FILE *dfp;
extern FILE *bfp;


extern char ptype;
extern char btype;
extern char dtype;

/*****************************************************************************************************************
* 函数名称：void main_menu()
* 功能描述：
*			 实现 主菜单显示 的功能
* 参数说明：
*
* 返回值：
******************************************************************************************************************/

void main_menu()
{
    printf("1.Game start\n");
    printf("2.Score show\n");
}


/*****************************************************************************************************************
* 函数名称：void sub_menu()
* 功能描述：
*			 实现 次菜单显示 的功能
* 参数说明：
*
* 返回值：
******************************************************************************************************************/

void sub_menu()
{
    printf("1.Beginer\n");
    printf("2.Player\n");
    printf("3.Darker\n");
    printf("4.Back\n");
}

/*****************************************************************************************************************
* 函数名称：void Finish()
* 功能描述：
*			 实现 未进入排行榜的结束打印界面 的功能
* 参数说明：
*
*
* 返回值：
******************************************************************************************************************/

void Finish(TetrisManager *manager)
{
    system("cls");
    gotoxy(15, 10);
    printf("/**********************************************/");
    gotoxy(15, 20);
    printf("/**********************************************/");
    gotoxy(18, 14);
    printf("GAME   OVER");
    gotoxy(20, 16);
    printf("Your Score is %d",manager->score);
    gotoxy(0, 27);
    system("pause");
}



/*****************************************************************************************************************
* 函数名称：void GoRank()
* 功能描述：
*			 实现 进入排行榜的结束打印界面 的功能
* 参数说明：
*
*
* 返回值：
******************************************************************************************************************/

void GoRank(TetrisManager *manager)
{
    system("cls");
    gotoxy(15, 10);
    printf("/**********************************************/");
    gotoxy(15, 20);
    printf("/**********************************************/");
    gotoxy(18, 14);
    printf("Get on the list ");
    gotoxy(20, 16);
    printf("Your Score is %d",manager->score);
    gotoxy(0, 27);
    system("pause");
}

// 显示得分信息
void printScore(const TetrisManager *manager)
{
    static const char *tetrisName = "ITLJZSO";
    char i;

    SetConsoleTextAttribute(g_hConsoleOutput, 7);

    gotoxyWithFullwidth(2, 2);
    printf("得分：%u", manager->score);

 //   gotoxyWithFullwidth(1, 6);
 //   printf("■消行总数：%u", manager->erasedTotal);
 //   for (i = 0; i < 4; ++i) {
  //      gotoxyWithFullwidth(2, 8 + i);
  //      printf("□消%d：%u", i + 1, manager->erasedCount[i]);
  //  }

  //  gotoxyWithFullwidth(1, 15);
  //  printf("■方块总数：%u", manager->tetrisTotal);

  //  for (i = 0; i < 7; ++i) {
  //      gotoxyWithFullwidth(2, 17 + i);
  //      printf("□%c形：%u", tetrisName[i], manager->tetrisCount[i]);
  //  }
}

/*****************************************************************************************************************
* 函数名称：int user_show(int select)
* 功能描述：
*			 实现 用户分数显示 的功能
* 参数说明：
*           select参数为难度系数
*
* 返回值：0
******************************************************************************************************************/

void user_show(char select)
{
    char i = 0;
    char j = 0;
    char k = 0;
    char count = 0;
    char t = 0;
    user *a = NULL;
    user *b = NULL;
    pNode* temp = NULL;
    pNode* p = NULL;
    pNode *thead = NULL;
    user *l = NULL;
    user *g = NULL;
    char a_num =0;
    char b_num = 0;

    char *name  = NULL;
    char *salary = NULL;
    char *s = {0};

    a=(user *)malloc(sizeof(user));
    b=(user *)malloc(sizeof(user));

    thead = (pNode *)malloc(sizeof(pNode *));

    thead = LIST_Init(NULL);
     //开辟结构体空间
    s = (char *)malloc(sizeof(char *));
    g = (user *)malloc(sizeof(user));
    l = (user *)malloc(sizeof(user));

    name = (char *)malloc(sizeof(char *));

    if(select == 1)
    {
        printf("--------beginer-----------\n");
        bfp = FILE_open("data/beginer.txt");
        thead=FILE_read(bfp,sizeof(user));
    }
    else if(select == 2)
    {
        printf("--------player------------\n");
        pfp = FILE_open("data/player.txt");
        thead=FILE_read(pfp,sizeof(user));
    }
    else
    {
        printf("--------darker------------\n");
        dfp = FILE_open("data/darker.txt");
        thead=FILE_read(dfp,sizeof(user));
    }

    count = LIST_GetCount(thead);

    for (temp = thead; temp->next != NULL; temp = temp->next)
    {
        for (p = thead; p->next != NULL; p = p->next)
        {
            if(p->pData != NULL)
            {
                a = (user *)(p->pData);

                b = (user *)(p->next->pData);

                a_num = atoi(a->score);
                b_num = atoi(b->score);
                memset(s,0,sizeof(char *));

                memset(l,0,sizeof(user *));
                memset(name,0,sizeof(char *));
                if (a_num < b_num)
                {
                    strcpy(s,a->score);
                    strcpy(name,a->name);

                    strcpy(a->score,b->score);
                    strcpy(a->name,b->name);

                    strcpy(b->score,s);
                    strcpy(b->name,name);
                }
            }
        }
    }
    printf("NO       Name        Score\n");
    if(count > 10)
    {
        count =10;
    }
    for(i = 1; i <= count; i++)
    {
        g = (user *)LIST_GetNode(i,thead);
        printf("%d    %8s  %10s\n",i,g->name,g->score);
    }
    printf("\n\n");
    return 0;
}
