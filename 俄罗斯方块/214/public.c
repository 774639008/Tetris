#include <conio.h>
#include <string.h>
#include "public.h"

/*****************************************************************************************************************
* 函数名称：void load()
* 功能描述：
*			 实现 加载 的功能
* 参数说明：
*
* 返回值：
******************************************************************************************************************/

void load(){
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1;r<=20;r++)
    {
    for(q=0;q<=100000000;q++);//to display the character slowly
    printf("%c",277);
    }
     //getch();
}

/*****************************************************************************************************************
* 函数名称：void exits()
* 功能描述：
*			 实现 退出加载 的功能
* 参数说明：
*
* 返回值：
******************************************************************************************************************/

void exits(){
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("Exit...");
    gotoxy(30,15);
    for(r=1;r<=20;r++)
    {
    for(q=0;q<=100000000;q++);//to display the character slowly
    printf("%c",277);
    }
     //getch();
}

/***************************************************************************************************************************************************************************
* 函数名称：int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
* 功能描述：
*			 实现 控制输入输出 的功能
* 参数说明：
*           char acStr[100] 输入的数组 int iMaxlen 输入最大长度 int iputType 输入的类型0为数字 1为字母 int isPlainttext 输入是否为明密文 0为密文 1为明文
* 返回值：0
****************************************************************************************************************************************************************************/

int glb_putString(char acStr[100], int iMaxlen, int iputType, int isPlainttext)
{
		char ch;				//定义ch来接受getch();
		int iLenth = 0;			//定义一个字符长度来计算输入的个数

		while(1)
		{
				ch = getch();
				if(ch == '\r')		//回车 删除
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\t')
				{
						acStr[iLenth] = '\0';
						break;
				}
				if(ch == '\b')		//删除字符
				{
						if(iLenth > 0)
						{
							printf("\b \b");
							iLenth--;				//回删要减个数
							acStr[iLenth] = '\0';
						}
				}
				if(ch == 27)
				{
					return 27;
				}
				if(iLenth < iMaxlen)				//判断长度是否小于最大长度
				{
						switch(iputType)             //输入的类型1为数字,2为字母,3为数字与字母
						{
						case 1:
							{
									if(ch >= '0' && ch <= '9')			//只能输入数字
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth]= ch;		//输入的字符存进数组acStr[ilenth]
											iLenth++;				//进行计算输入的个数
									}
							}
							break;
						case 2:
							{
									if(ch >= 'a' && ch <= 'z')		//只能输入字母
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth]= ch;		//输入的字符存进数组acStr[ilenth]
											iLenth++;				//进行计算输入的个数
									}
							}
							break;
						case 3:
							{
									if(ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z'|| ch >= 'A' && ch <= 'Z')	//可以输入字母和数字
									{
											if(isPlainttext)
											{
													putchar(ch);	//明文
											}
											else
											{
													putchar('*');	//密文
											}
											acStr[iLenth] = ch;		//输入的字符存进数组acStr[ilenth]
											iLenth++;				//进行计算输入的个数
									}
							}
							break;
						default:
							{
									printf("输入错误\n");
							}
							break;
						}
					}
				else
				{
					continue;
				}
		}
		return 0;
}

/*****************************************************************************************************************
* 函数名称：int gotoxy(int x,int y)
* 功能描述：
*			 实现 光标 的功能
* 参数说明：
*           int x --x坐标   int y  --y坐标
* 返回值：0
******************************************************************************************************************/

int gotoxy(int x,int y)
{
		HANDLE handle;								//设置句柄
		COORD coord;								//设置光标
		coord.X=x;									//定义x坐标
		coord.Y=y;									//定义y坐标
		handle=GetStdHandle(STD_OUTPUT_HANDLE);		//获取标准句柄
		SetConsoleCursorPosition(handle,coord);		//设置光标控制
		return 0;
}


/*****************************************************************************************************************
* 函数名称：int select_interface(int max)
* 功能描述：
*			 实现 光标选择 的功能
* 参数说明：
*
* 返回值：0
******************************************************************************************************************/
int select_interface(int max)			//（光标跳转以及界面选择）
{
	int quit=0;
	int s=1;
	while(1)
	{
		switch(getch())		//输入
		{
		case 72:			//上
		case 75:			//左
			if(s==1) s=max;
			else s--;
			break;

		case 80:			//下
		case 77:			//右
			if(s==max) s=1;
			else s++;
			break;

		case '\r':			//确认
			quit = 1;
			break;

		case 'q':			//退出
		case 'Q':
			exit(0);

		case 27:			//返回
			return -3;
			break;

		default :
			break;
		}

		switch(s)			//光标跳转
		{
		case 1:
		    gotoxy(15,1);
		    printf("   ");
		    gotoxy(15,2);
		    printf("   ");
		    gotoxy(15,3);
		    printf("   ");
			gotoxy(15,0);
			printf("<-");
			break;
		case 2:
		    gotoxy(15,0);
		    printf("   ");
		    gotoxy(15,2);
		    printf("   ");
		    gotoxy(15,3);
		    printf("   ");
			gotoxy(15,1);
			printf("<-");
			break;
		case 3:
		    gotoxy(15,0);
		    printf("   ");
		    gotoxy(15,1);
		    printf("   ");
		    gotoxy(15,3);
		    printf("   ");
			gotoxy(15,2);
			printf("<-");
			break;
		case 4:
		    gotoxy(15,0);
		    printf("   ");
		    gotoxy(15,1);
		    printf("   ");
		    gotoxy(15,2);
		    printf("   ");
			gotoxy(15,3);
			printf("<-");
			break;
		case 5:
		    printf("<-");
			gotoxy(0,4);
			break;
		case 6:
			gotoxy(0,5);
			break;
		default :
			break;
		}
		if(quit==1) break;
	}
	return s;
}
/*
void public_num(char *pcBuf)
{
	*pcBuf = getch();
	return *pcBuf;
}
*/
//封装只输入一个数字
char *public_num(char *acBuf)
{
	char ch = 0,ch1 = 0;
	int i = 0;
	int lenth = 10;
    while (1)
	{
		ch = getch();
		if(ch == '\r')
		{
			*acBuf = 0;
			break;
		}
		else if (ch >= '0' && ch <= '9')
		{
		  if(i < lenth)
		  {
			putchar(ch);
			*acBuf = 0;
			*acBuf++ = ch;
			i++;
		  }
		}
		else if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)
		{
			ch1 = getch();
			printf("%c%c",ch,ch1);
			*acBuf++ = ch;
			*acBuf++ = ch1;
		}
		else if (ch == '\b')
		{
			if (i>0)
			{
				if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)
				{
					printf("\b \b\b \b");
					*acBuf-- = 0;
					*acBuf = 0;

				}
				else
				{
					printf("\b \b");
					*acBuf--;
					*acBuf = 0;
				}
				i--;
			}
		}
		else
		{
			continue;
		}
		return acBuf;
	}
	return 0;
}

/*
void public_num(char *pcBuf)
{
	*pcBuf = getch();
	return *pcBuf;
}
*/
//封装只输入一个数字
void public_char(char *acBuf)
{
	char ch = 0,ch1 = 0;
	int i = 0;
	int lenth = 10;
    while (1)
	{
		ch = getch();
		if(ch == '\r')
		{
			*acBuf = 0;
			break;
		}
		else if (ch >= '0' && ch <= '9')
		{
		  if(i < lenth)
		  {
			putchar(ch);
			*acBuf = 0;
			*acBuf++ = ch;
			i++;
		  }
		}
		else if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)
		{
			ch1 = getch();
			printf("%c%c",ch,ch1);
			*acBuf++ = ch;
			*acBuf++ = ch1;
		}
		else if (ch == '\b')
		{
			if (i>0)
			{
				if((unsigned char)ch>=0xa1 && (unsigned char)ch<=0xfe)
				{
					printf("\b \b\b \b");
					*acBuf-- = 0;
					*acBuf = 0;

				}
				else
				{
					printf("\b \b");
					*acBuf--;
					*acBuf = 0;
				}
				i--;
			}
		}
		else
		{
			continue;
		}
	}
}
