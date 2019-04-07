#include <stdio.h>
#include <stdlib.h>
#include ".archivetempLQueue.h"

int LOOP = 0;   //记录当前有无初始化队列
LQueue *Q;   //包含队列的头指针、尾指针和长度
int E; 
void *e = &E;   //查看队头元素
int queuelength;   //查看队列长度
void *data;   //入队元素
Node *p;
int *P;   //用来遍历队列输出
void(*foo)(void *q);   //遍历函数
void *q;   //操作函数

int main()
{
	void choose();
	void menu();
	void print();
	Q = (LQueue *)malloc(sizeof(LQueue));   //为存储队列信息的节点分配空间
	menu();    //菜单
	print();    //提示
	choose();   //选择
	return 0;
}

void choose()
{
	void menu(); 
	void print();  
	char c = getchar();  
	while (c != 'x')
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)   //已经初始化过队列
				printf("已经初始化过一个队列\n");
			if (LOOP == 0)   //还没有初始化过队列
			{
				InitLQueue(Q);   //初始化
				LOOP = 1;   //初始化过队列
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				DestoryLQueue(Q);   //销毁
				LOOP = 0;   //已销毁队列
			}
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				IsEmptyLQueue(Q);   //判空
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				GetHeadLQueue(Q, e);   //得到队头元素
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				queuelength = LengthLQueue(Q);   //测长度
			break;
		case 'f':
		case 'F':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				int *joindata;
				joindata = (int *)malloc(sizeof(int));   //与*data建立联系
				printf("请输入你想要入队的数字:");
				scanf_s("%d", joindata);   //输入想要的值
				EnLQueue(Q, joindata);   //入队
				for (p = Q->front->next; p != NULL; p = p->next)   //遍历输出队列全部元素
				{
					P = p->data;
					printf("%d->", *P);
				}
				printf("\n");
			}
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				DeLQueue(Q);   //出队
				if (Q->length > 0)
				{
					for (p = Q->front->next; p != NULL; p = p->next)   //遍历输出队列全部元素
					{
						P = p->data;
						printf("%d->", *P);
					}
					printf("\n");
				}
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				ClearLQueue(Q);   //清空
			break;
		case 'i':
		case 'I':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)   //初始化过队列
				TraverseLQueue(Q, foo);   //遍历函数
			break;
		case 'j':
		case 'J':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)   //初始化过队列
				LPrint(q);   //操作函数
			break;
		case 'x':
		case 'X':
			break;   
		case 'y':
		case 'Y':
			menu(); 
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
	printf("\t\t\t|  a.初始化队列                   |\n");
	printf("\t\t\t|  b.销毁队列                     |\n");
	printf("\t\t\t|  c.判空                         |\n");
	printf("\t\t\t|  d.查看队头元素                 |\n");
	printf("\t\t\t|  e.查看队列长度                 |\n");
	printf("\t\t\t|  f.入队                         |\n");
	printf("\t\t\t|  g.出队                         |\n");
	printf("\t\t\t|  h.清空队列                     |\n");
	printf("\t\t\t|  i.遍历队列                     |\n");
	printf("\t\t\t|  j.操作                         |\n");
	printf("\t\t\t|  x.退出程序运行                 |\n");
	printf("\t\t\t|  y.查看菜单选项                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}