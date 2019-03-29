#include <stdio.h>   //包含头文件
#include <stdlib.h>
#include "linkedList.h"

int JIEDIAN = 0;   //用于计数和循环
ElemType e = 0;    //visit函数的参数
ElemType want;   //用于寻找data为这个值的节点
int i;   //用于计数

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
	ElemType number;   //准备存入节点中的数
	LNode fNode;   //创建头节点
	LinkedList *head = &fNode;   //定义一个*head作为头指针
	LinkedList phead = *head;         //用于存放当前的头指针
	ElemType value, *e = &value;   //用于修改节点值的函数
	LNode *p, *q;   //定义一个可用于创建新节点的指针
	LinkedList current;   //定义一个用于指向当前位置的指针
	c = getchar();   //输入菜单选项
	while (c != 'x')   //输入x退出
	{
		switch (c)
		{
		case 'a':
		case 'A':InitList(head);
			phead = head;
			break;
		case 'b':
		case 'B':DestroyList(head);
			break;
		case 'c':
		case 'C':
			p = phead;   //p指向当前最后一个节点
			q = (LNode *)malloc(sizeof(LNode));   //为新节点分配内存
			printf("请输入你想要在新节点中存放的值:");
			scanf_s("%d", &number);
			printf("\n");
			q->data = number;   //为新节点赋值
			InsertList(p, q);    //插入函数
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'd':
		case 'D':printf("你想要删除第几个节点的后面一个节点:");
			scanf_s("%d", &JIEDIAN);   //想要删除第几个节点
			current = (*head)->next;
			while (i != JIEDIAN)   //找到该节点
			{
				current = current->next;
				i++;
			}
			i = 1;
			printf("你想将这个节点的数值改为:");
			scanf_s("%d", &(*e));   //输入你想要赋给那个节点的值
			DeleteList(current, e);   //删节点函数
			phead = (*head)->next;
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead指向最后一个节点
			break;
		case 'e':
		case 'E':TraverseList(phead, visit);   //执行函数并调用visit函数
			break;
		case 'f':
		case 'F':p = phead;   //p指向当前最后一个节点
			printf("你想要找到值为几的节点");
			scanf_s("%d", &want);   //输入想要查询是否存在节点的值为给定值的值
			SearchList(((*head)->next), want);   //执行搜索函数
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'g':
		case 'G':ReverseList(head);   //反转
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'h':
		case 'H':IsLoopList((*head)->next);   //成环
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'i':
		case 'I':(*head)->next=ReverseEvenList(head);   //偶数反转
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'j':
		case 'J':FindMidNode(phead);   //找中间节点
			printf("中间节点:");
			printf("它的值是%d", phead->data);
			phead = (*head)->next;   //phead指向头节点
			while (phead != NULL)   //遍历链表
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead回到最后一个节点
			break;
		case 'x':
		case 'X': break;   //退出程序
		case 'y':
		case 'Y':menu(); break;   //菜单功能
		default:printf("请输入正确的菜单选项！\n");   //错误提示
		}
		char d = getchar();
		print();
		c = getchar();
	}
}

void print()   //提示函数
{
	printf("请输入相应菜单选项前字母并按回车:");
}

void menu()   //打印菜单函数
{
	printf("\t\t______________________________________________\n");
	printf("\t\t|                                            |\n");
	printf("\t\t|  a.初始化一个空链表（包含一个头节点）      |\n");
	printf("\t\t|  b.销毁一个链表                            |\n");
	printf("\t\t|  c.将节点p插入到节点q后                    |\n");
	printf("\t\t|  d.删除节点p之后的那个节点，并赋值给节点p  |\n");
	printf("\t\t|  e.遍历链表并调用visit功能                 |\n");
	printf("\t\t|  f.根据所给值找到其所对应的节点            |\n");
	printf("\t\t|  g.反转链表                                |\n");
	printf("\t\t|  h.判断链表是否为一个环形链表              |\n");
	printf("\t\t|  i.反转链表中值为偶数的节点                |\n");
	printf("\t\t|  j.找到链表的中间节点                      |\n");
	printf("\t\t|  x.退出程序运行                            |\n");
	printf("\t\t|  y.查看菜单选项                            |\n");
	printf("\t\t|____________________________________________|\n");
	printf("                                                  \n");
}