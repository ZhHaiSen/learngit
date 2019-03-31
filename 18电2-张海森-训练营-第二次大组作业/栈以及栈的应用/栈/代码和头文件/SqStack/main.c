#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SqStack.h"

int LOOP = 0;   //判断有无创建过栈
SqStack stack;   //开辟一个新节点
SqStack *S = &stack;       //开辟一个指向栈的指针
int sizes;   //栈的初始化大小
ElemType StackTop, *e = &StackTop;   //获得栈顶元素
int StackLength;   //检测栈长度
ElemType data = 0, Edata = 0;
ElemType *edata = &Edata;   //出入栈的数字
int i;   //用于计数和表示栈中数字

int main()
{
	void choose();
	void menu();
	void print();
	menu();   //打印菜单
	print();   //打印提示
	choose();   //选择菜单选项
	return 0;
}

void choose()
{
	void menu();   //声明菜单函数
	void print();   //声明提示函数
	char c = getchar();   //输入菜单选项
	while (c != 'x')   //输入x退出
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)
				printf("已经创建过一个空栈\n");
			if (LOOP == 0)
			{
				printf("你想要创建一个多大的顺序栈:");
				scanf_s("%d", &sizes);   //设置size
				if (sizes <= 0)
					printf("无法为你创建这样的栈\n");
				else
				{
					initStack(S, sizes);   //初始化栈
					LOOP = 1;
				}
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				isEmptyStack(S);   //判空
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				getTopStack(S, e);   //得到栈顶元素
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				clearStack(S);   //清空栈
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //已销毁
				printf("当前没有栈\n");
			if (LOOP == 1)
			{
				destroyStack(S);   //销毁栈
				LOOP = 0;
			}
		case 'f':
		case 'F':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				stackLength(S, StackLength);   //检测栈长度
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
			{
				printf("请输入你想要压入栈中的数字:");   //输入栈的数字
				scanf_s("%d", &data);
				pushStack(S, data);   //入栈
				printf("当前栈中元素:");
				for (i = 0; i <= S->top; i++)   //输出所有栈中元素
					printf("%d->", S->elem[i]);
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
			{
				popStack(S, edata);   //出栈
				printf("当前栈中元素:");
				for (i = 0; i <= S->top; i++)   //输出所有栈中元素
					printf("%d->", S->elem[i]);
				if (S->top == -1)   //所有元素都出栈
					printf("当前为空栈");
				printf("\n");
			}
			break;
		case 'x':
		case 'X':
			break;   //退出程序
		case 'y':
		case 'Y':
			menu();   //显示菜单
			break;
		default:printf("请输入正确的菜单选项！\n");
		}
		char d = getchar();
		print();
		c = getchar();
	}
}

void print()   //打印相关的提示
{
	printf("请输入相应菜单选项前字母并按回车:");
}

void menu()   //菜单选项的打印函数
{
	printf("\t\t\t___________________________________\n");
	printf("\t\t\t|                                 |\n");
	printf("\t\t\t|  a.初始化栈                     |\n");
	printf("\t\t\t|  b.判断栈是否为空               |\n");
	printf("\t\t\t|  c.得到栈顶元素                 |\n");
	printf("\t\t\t|  d.清空栈                       |\n");
	printf("\t\t\t|  e.销毁栈                       |\n");
	printf("\t\t\t|  f.检测栈                       |\n");
	printf("\t\t\t|  g.入栈                         |\n");
	printf("\t\t\t|  h.出栈                         |\n");
	printf("\t\t\t|  x.退出程序运行                 |\n");
	printf("\t\t\t|  y.查看菜单选项                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}