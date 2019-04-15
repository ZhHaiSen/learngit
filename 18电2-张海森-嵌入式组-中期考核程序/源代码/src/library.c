#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*创建一个存储书本信息和一类存储借阅者信息的链表*/
Status InitBook(Book *L)
{
	L->next = NULL;   //初始化，头节点的指针指向空，防止野指针造成的危害
	L->borrow = NULL;   //因为头节点不存储书本信息，故头节点不存在借阅者链表
	return SUCCESS;
}

Status InitBorrow(Borrow *Q)
{
	Q->next = NULL;   //初始化，头节点的指针指向空，防止野指针造成的危害
	return SUCCESS;
}

/*用于摧毁链表，可在某本书没有利用价值时销毁该书的借阅者链表*/
Status DestroyBorrow(Borrow *Q)   //借阅者
{
	Borrow *pfirst,*psecond;
	for (pfirst = Q, psecond = Q->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)
		free(pfirst);
	free(pfirst);   //遍历链表，释放所有节点所占用的空间
	return SUCCESS;
}

Status DestroyBook(Book *L)   //所有图书
{
	Borrow *pfirst, *psecond;
	for (pfirst = L, psecond = L->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)
		free(pfirst);
	free(pfirst);   //遍历链表，释放所有节点所占用的空间
	return SUCCESS;
}

/*链表的插入操作，可用于增加书籍信息或者增加借阅者信息*/
Status InsertBorrow(Borrow *Q,Borrow *q)   //借阅者
{
	Borrow *p;
	for (p = Q; p->next != NULL; p = p->next)   //获取指向最后一个节点的指针
		;
	q->next = NULL;   //新节点指向空，防止新节点成为最后一个节点后，它的指针造成危害
	p->next = q;   //q作为最后一个节点插入到借阅者链表中
	return SUCCESS;
}

Status InsertBook(Book *L, Book *l)   //书本
{
	Book *p;
	for (p = L; p->next != NULL; p = p->next)   //获取指向最后一个节点的指针
		;
	l->next = NULL;   //新节点指向空，防止新节点成为最后一个节点后，它的指针造成危害
	p->next = l;   //l作为最后一个节点插入到书本链表中
	return SUCCESS;
}

/*链表的删除操作，可用于删除书籍信息或者删除借阅者信息*/
Status DeleteBorrow(Borrow *Q,unsigned int x)   //借阅者
{
	int LOOP = 0;   //记录是否已删除节点
	Borrow *pfirst,*psecond;
	for (pfirst = Q,psecond=pfirst->next; psecond != NULL; pfirst=psecond,psecond = psecond->next)   //遍历链表
	{
		if (psecond->library_card == x)
		{
			LOOP = 1;
			pfirst->next = psecond->next;
			free(psecond);   //找到并删除存储这位借阅者信息的节点
			return SUCCESS;
		}
		if (LOOP == 1) break;   //已删除所要找的节点
	}
}

Status DeleteBook(Book *L, char x[])   //书本
{
	int LOOP = 0;   //记录是否已删除节点
	Book *pfirst, *psecond;
	for (pfirst = L, psecond = pfirst->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)   //遍历链表
	{
		if (strcmp(psecond->ISBN, x) == 0)
		{
			LOOP = 1;
			pfirst->next = psecond->next;
			free(psecond);   //找到并删除存储这本书的节点
			return SUCCESS;
		}
		if (LOOP == 1) break;   //已删除所要找的节点
	}
}
