#include <stdio.h>
#include <stdlib.h>
#include ".archivetempAQueue.h"

int LOOP = 0;   //标志位
int record[MAXQUEUE] = { 0 };   //状态记录数组
int count=-1;   //存储相应元素的类型的顺序
AQueue *Q;   //Q
char form[100];   //输入入队元素
int i;
int j;
int figure;   //总共位数
int redix_point;   //小数点所在位数
int current;   //遍历队列输出数值
char d;
void *e;   //队头元素
void *q;  //遍历操作指针
void(*foo)(void *q);   //遍历函数

int main()
{
	void choose();
	void menu();
	void print();
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
				Q = (AQueue *)malloc(sizeof(AQueue));   //为Q开辟空间
				InitAQueue(Q);   //初始化
				LOOP = 1;
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				free(Q);   //释放Q所代表的范围
				DestoryAQueue(Q);   //销毁
				LOOP = 0;
			}
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				IsFullAQueue(Q);   //判满
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				IsEmptyAQueue(Q);   //判空
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				GetHeadAQueue(Q, e);   //得到队头元素
			break;
		case 'f':
		case 'F':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
				LengthAQueue(Q);   //得到队列长度
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				printf("请输入你想要入队的字母或数据:");
				for (i = 0; ; i++)
				{
					scanf_s("%c", &form[i], 1);
					if (form[i] == '\n') break;
				}   //将所输入的字母或数值转化成字符串
				figure = i;   //位数
				count =(Q->rear)+1;		   //count提前记录		
				for (i = 0; form[i] != '\n'; i++)   //查看有无字母、小数点
				{
					record[count] = 2;   //整型
					if (form[i] >= 65 && form[i] <= 122)
						record[count] = 1;   //字符型
					if (form[i] == 46)   //浮点型
					{
						redix_point = i;
						record[count] = 3;
					}
					if (form[i] == 46) break;
				}
				i = 0;
				if (record[count] == 1)   //字符型
				{
					char *p;
					p = (char *)malloc(sizeof(char));
					*p = form[i];
					EnAQueue(Q, p);   //入队
				}
				if (record[count] == 2)   //整型
				{
					int *sum;
					sum = (int *)malloc(sizeof(int));
					*sum = 0;
					int save;
					for (i = 0; i < figure - 1; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < figure - i - 1; j++)
						{
							save = save * 10;
						}
						*sum = *sum + save;
					}
					save = form[i] - 48;
					*sum = *sum + save;   //转化为十进制
					EnAQueue(Q, sum);   //入队
				}
				if (record[count] == 3)   //浮点型
				{
					float *sum;
					sum = (float *)malloc(sizeof(float));
					*sum = 0;
					float save;
					for (i = 0; i < redix_point - 1; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < redix_point - i - 1; j++)
						{
							save = save * 10;
						}
						*sum = *sum + save;
					}
					save = form[i] - 48;
					*sum = *sum + save;
					for (i = redix_point + 1; i < figure; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < i - redix_point; j++)
						{
							save = save / 10;
						}
						*sum = *sum + save;
					}   //转化为十进制
					EnAQueue(Q, sum);   //入队
				}
				for (i = 0,current=Q->front; i < Q->length; i++,current++)
				{
					if (current == MAXQUEUE)   //跳过最后一个，从头输出
						current = 0;
					if (record[current] == 1)   //字符型
					{
						char *number = (char *)Q->data[current];
						printf("%c->", *number);
					}
					if (record[current] == 2)   //整型
					{
						int *number = (int *)Q->data[current];
						printf("%d->", *number);
					}
					if (record[current] == 3)   //浮点型
					{
						float *number = (float *)Q->data[current];
						printf("%f->", *number);
					}
				}
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)    //初始化过队列
			{
				DeAQueue(Q);   //出队
				for (i = 0, current = Q->front; i < Q->length; i++, current++)
				{
					if (current == MAXQUEUE)   //越过最后一个，从头输出
						current = 0;
					if (record[current] == 1)   //字符型
					{
						char *p = Q->data[current];
						printf("%c->", *p);
					}
					if (record[current] == 2)   //整型
					{
						int *p = Q->data[current];
						printf("%d->", *p);
					}
					if (record[current] == 3)   //浮点型
					{
						float *p = Q->data[current];
						printf("%f->", *p);
					}
				}
				printf("\n");
			}
			break;
		case 'i':
		case 'I':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)   //初始化过队列
				ClearAQueue(Q);   //清空队列
			break;
		case 'j':
		case 'J':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)   //初始化过队列
				TraverseAQueue(Q, foo);   //遍历队列
			break;
		case 'k':
		case 'K':
			if (LOOP == 0)   //队列不存在
				printf("没有队列\n");
			if (LOOP == 1)
				APrint(q);   //操作函数
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
		d = getchar();
		print();
		c = getchar();
		d = getchar();
	}
}

void print()   //打印相关的提示
{
	printf("请输入相应菜单选项前字母并按回车:");
}

void menu()   //菜单选项的打印函数
{
	printf("\t\t\t ___________________________________\n");
	printf("\t\t\t|                                  |\n");
	printf("\t\t\t|   a.初始化队列                   |\n");
	printf("\t\t\t|   b.销毁队列                     |\n");
	printf("\t\t\t|   c.判满                         |\n");
	printf("\t\t\t|   d.判空                         |\n");
	printf("\t\t\t|   e.查看队头元素                 |\n");
	printf("\t\t\t|   f.查看队列长度                 |\n");
	printf("\t\t\t|   g.入队                         |\n");
	printf("\t\t\t|   h.出队                         |\n");
	printf("\t\t\t|   i.清空队列                     |\n");
	printf("\t\t\t|   j.遍历函数                     |\n");
	printf("\t\t\t|   k.操作                         |\n");
	printf("\t\t\t|   x.退出程序运行                 |\n");
	printf("\t\t\t|   y.查看菜单选项                 |\n");
	printf("\t\t\t|   每完成一个操作需要按一次回车   |\n");
	printf("\t\t\t|__________________________________|\n");
	printf("                                          \n");
}