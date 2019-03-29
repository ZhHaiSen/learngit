#include <stdio.h>   //包含头文件
#include <stdlib.h>
#include "duLinkedList.h"

int JIEDIAN = 0;   //用于计量总节点数
ElemType e;    //visit函数的参数
int LOOP=0; //用于判断有无创建一个链表
DuLinkedList phead;   //头指针拷贝
int NodeNum = 1;   //当前节点数

int main()   //main函数
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
	void search(ElemType e);   //声明函数
	void(*visit)(ElemType e);   //声明(*visit)函数
	visit = search;    //visit指向search函数
	char c;   //菜单选项
	int i=1;  //用于计数、循环
	ElemType number;   //准备存入节点中的数
	ElemType value, *e = &value;   //用于修改节点值的函数
	DuLNode fNode;   //创建头节点
	DuLinkedList *head=&fNode;   //定义一个*head作为头指针
	phead=*head;         //用于存放当前的头指针
	DuLinkedList current;   //定义一个用于指向当前位置的指针
	DuLNode *p,*q;   //定义一个可用于创建新节点的指针
	c = getchar();   //输入菜单选项
	while (c != 'x')   //输入x退出
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)
				printf("已经创建过一个链表\n");
			if (LOOP == 0)
			{
				InitList_DuL(head);   //初始化空链表
				(*head)->data = 0;
				phead = *head;
				LOOP = 1;
			}
			break;
			/******************************************************************************************************************/
		case 'b':
		case 'B':
			if (LOOP == 0)
			{
				printf("你还没有创建链表\n");
			}
			if (LOOP == 1)
			{
				DestroyList_DuL(head);   //销毁该链表
				LOOP = 0;
			}
			break;
			/******************************************************************************************************************/
		case 'c':
		case 'C':
			if (LOOP == 0)
			{
				printf("你还没有创建链表\n");
			}
			if (LOOP == 1)
			{
				printf("你想要在第几个节点之前插入节点:");
				scanf_s("%d", &JIEDIAN);
				if (JIEDIAN <= 0)
					printf("无法为你插入\n");
				else if (JIEDIAN > NodeNum)
					printf("不存在这个节点\n");
				else
				{
					p = phead;   //p指向当前最后一个节点
					if (phead->prior == NULL)
					{
						printf("当前还没有任何节点\n");
					}
					else
					{
						NodeNum = 1;
						q = (DuLNode *)malloc(sizeof(DuLNode));   //为新节点分配内存
						printf("请输入你想要在新节点中存放的值:");
						scanf_s("%d", &number);
						printf("\n");
						q->data = number;   //为新节点赋值
						current = (*head)->next;
						while (i != JIEDIAN)   //找到该节点
						{
							current = current->next;
							i++;
						}
						i = 1;
						p = current;
						InsertBeforeList_DuL(p, q);   //前插函数
						phead = (*head)->next;   //phead指向头节点
						while (phead != NULL)   //遍历链表
						{
							printf("%d->", phead->data);
							phead = phead->next;
						}
						printf("\n");
						phead = (*head)->next;
						while (phead->next != NULL)
						{
							NodeNum = NodeNum + 1;;
							phead = phead->next;   //phead回到最后一个节点
						}
					}
				}
			}
			break;
			/********************************************************************************************************************/
		case 'd':
		case 'D':
			if (LOOP == 0)
			{
				printf("你还没有创建链表\n");
			}
			if (LOOP == 1)
			{
				p = phead;   //phead指向最后一个节点
				NodeNum = 1;
				q = (DuLNode *)malloc(sizeof(DuLNode));   //为新节点分配内存
				printf("请输入你想要在新节点中存放的值:");
				scanf_s("%d", &number);
				printf("\n");
				q->data = number;   //为新节点赋值
				InsertAfterList_DuL(p, q);   //后插函数
				phead = (*head)->next;
				while (phead != NULL)   //遍历链表
				{
					printf("%d->", phead->data);
					phead = phead->next;
				}
				phead = (*head)->next;
				while (phead->next != NULL)
				{
					NodeNum = NodeNum + 1;;
					phead = phead->next;   //phead指向当前最后一个节点
				}
				printf("\n");
			}
			break;
			/******************************************************************************************************************/
		case 'e':
		case 'E':
			if (LOOP == 0)
			{
				printf("你还没有创建链表\n");
			}
			if (LOOP == 1)
			{
				printf("你想要删除第几个节点的后面一个节点:");
				scanf_s("%d", &JIEDIAN);   //想要删除第几个节点
				if (JIEDIAN <= 0)
					printf("无法为你插入\n");
				else if (JIEDIAN > NodeNum)
				{
					printf("不存在这个节点\n");
				}
				else
				{
					NodeNum = 1;
					current = (*head)->next;
					while (i != JIEDIAN)   //找到该节点
					{
						current = current->next;
						i++;
					}
					i = 1;
					printf("你想将这个节点的数值改为:");
					scanf_s("%d", &(*e));   //输入你想要赋给那个节点的值
					DeleteList_DuL(current, e);   //删节点函数
					phead = (*head)->next;
					while (phead != NULL)   //遍历链表
					{
						printf("%d->", phead->data);
						phead = phead->next;
					}
					printf("\n");
					phead = (*head)->next;
					while (phead->next != NULL)
					{
						NodeNum++;
						phead = phead->next;   //phead指向最后一个节点
					}
				}
			}
			break;
			/******************************************************************************************************************/
		case 'f':
		case 'F':
			if (LOOP == 0)
			{
				printf("你还没有创建链表\n");
			}
			if (LOOP == 1)
			{
				TraverseList_DuL(phead, visit);   //遍历及调用visit函数的函数
			}
			break;
			/******************************************************************************************************************/
		case 'x':
		case 'X': 
			break;   //退出程序运行
			/******************************************************************************************************************/
		case 'y':
		case 'Y':
			menu();   //显示菜单
			break;
			/******************************************************************************************************************/
		default:printf("请输入正确的菜单选项！\n");   //错误提示
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
	printf("\t\t____________________________________________________\n");
	printf("\t\t|                                                  |\n");
	printf("\t\t|  a.初始化一个空链表（包含一个头节点）            |\n");
	printf("\t\t|  b.销毁一个链表                                  |\n");
	printf("\t\t|  c.将节点q插入到任意节点p前                      |\n");
	printf("\t\t|  d.将节点q插入到当前节点p后                      |\n");
	printf("\t\t|  e.删除节点p之后的那个节点，并赋值给节点p        |\n");
	printf("\t\t|  f.遍历链表并调用visit功能(显示调用几次visit函数)|\n");
	printf("\t\t|  x.退出程序运行                                  |\n");
	printf("\t\t|  y.查看菜单选项                                  |\n");
	printf("\t\t|__________________________________________________|\n");
	printf("                                                        \n");
}
