#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int LOOP = 0;   //判断有没有创建过栈
LinkStack *S;    //新的栈信息节点
ElemType StackTop, *e = &StackTop;   //获得栈顶元素
int StackLength,*length=&StackLength;   //检测栈长度
ElemType data = 0, Edata = 0;
ElemType *edata = &Edata;   //出入栈的数字
LinkStack scurrent;   //栈信息节点的拷贝

int main()
{
	void choose();
	void menu();
	void print();
	menu();   //打印菜单
	print();   //打印提示
	S = (LinkStack *)malloc(sizeof(LinkStack));   //为栈信息的节点分配空间
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
				initLStack(S);   //初始化栈
				LOOP = 1;
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				isEmptyLStack(S);   //判空
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				getTopLStack(S, e);   //得到栈顶元素
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				clearLStack(S);   //清空栈
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)
				printf("当前没有栈\n");
			if (LOOP == 1)
			{
				destroyLStack(S);  //销毁栈
				LOOP = 0;
			}
		case 'f':
		case 'F':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
				LStackLength(S, length);   //检测栈的长度
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
			{
				printf("请输入你想要压入栈中的数字:");
				scanf_s("%d", &data);   //输入入栈数字
				pushLStack(S, data);   //入栈
				printf("当前栈中元素:");
				for (scurrent = *S; scurrent.top->next != NULL; scurrent.top = scurrent.top->next)   //输出栈中当前元素
					printf("%d->", scurrent.top->data);
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)
				printf("还没有创建空栈\n");
			if (LOOP == 1)
			{
				popLStack(S, edata);   //出栈
				printf("当前栈中元素:");
				for (scurrent = *S; scurrent.top->next != NULL; scurrent.top = scurrent.top->next)   //输出栈中当前元素
					printf("%d->", scurrent.top->data);
				printf("\n");
				if (S->count==0)   //空栈
					printf("当前为空栈");
				printf("\n");
			}
			break;
		case 'x':
		case 'X':
			break;   //退出程序
		case 'y':
		case 'Y':
			menu();   //菜单选项
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
	printf("\t\t\t|  f.检测栈长度                   |\n");
	printf("\t\t\t|  g.入栈                         |\n");
	printf("\t\t\t|  h.出栈                         |\n");
	printf("\t\t\t|  x.退出程序运行                 |\n");
	printf("\t\t\t|  y.查看菜单选项                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}