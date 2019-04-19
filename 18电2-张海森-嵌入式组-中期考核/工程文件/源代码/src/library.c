#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*�����洢�鱾��Ϣ����������Ϣ��ʹ������Ϣ������*/
Status InitBook(Book *L)
{
	L->next = NULL;   //��ʼ����ͷ�ڵ��ָ��ָ��գ���ֹҰָ����ɵ�Σ��
	L->borrow = NULL;   //��Ϊͷ�ڵ㲻�洢�鱾��Ϣ����ͷ�ڵ㲻���ڽ���������
	return SUCCESS;
}

Status InitBorrow(Borrow *Q)
{
	Q->next = NULL;   //��ʼ����ͷ�ڵ��ָ��ָ��գ���ֹҰָ����ɵ�Σ��
	return SUCCESS;
}

Status InitUser(User *P)
{
	P->next = NULL;   //��ʼ����ͷ�ڵ��ָ��ָ��գ���ֹҰָ����ɵ�Σ��
	return SUCCESS;
}

/*���ڴݻ���������ĳ����û�����ü�ֵʱ���ٸ���Ľ���������*/
Status DestroyBorrow(Borrow *Q)   //������
{
	Borrow *pfirst,*psecond;
	for (pfirst = Q, psecond = Q->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)
		free(pfirst);
	free(pfirst);   //���������ͷ����нڵ���ռ�õĿռ�
	return SUCCESS;
}

Status DestroyBook(Book *L)   //����ͼ��
{
	Borrow *pfirst, *psecond;
	for (pfirst = L, psecond = L->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)
		free(pfirst);
	free(pfirst);   //���������ͷ����нڵ���ռ�õĿռ�
	return SUCCESS;
}

Status DestroyUser(User *P)   //ʹ����
{
	User *pfirst, *psecond;
	for (pfirst = P, psecond = P->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)
		free(pfirst);
	free(pfirst);   //���������ͷ����нڵ���ռ�õĿռ�
	return SUCCESS;
}

/*����Ĳ�������������������鼮�������ߺ�ʹ������Ϣ*/
Status InsertBorrow(Borrow *Q,Borrow *q)   //������
{
	Borrow *p;
	for (p = Q; p->next != NULL; p = p->next)   //��ȡָ�����һ���ڵ��ָ��
		;
	q->next = NULL;   //�½ڵ�ָ��գ���ֹ�½ڵ��Ϊ���һ���ڵ������ָ�����Σ��
	p->next = q;   //q��Ϊ���һ���ڵ���뵽������������
	return SUCCESS;
}

Status InsertBook(Book *L, Book *l)   //�鱾
{
	Book *p;
	for (p = L; p->next != NULL; p = p->next)   //��ȡָ�����һ���ڵ��ָ��
		;
	l->next = NULL;   //�½ڵ�ָ��գ���ֹ�½ڵ��Ϊ���һ���ڵ������ָ�����Σ��
	p->next = l;   //l��Ϊ���һ���ڵ���뵽�鱾������
	return SUCCESS;
}

Status InsertUser(User *P, User *p)   //������
{
	User *t;
	for (t = P; t->next != NULL; t = t->next)   //��ȡָ�����һ���ڵ��ָ��
		;
	p->next = NULL;   //�½ڵ�ָ��գ���ֹ�½ڵ��Ϊ���һ���ڵ������ָ�����Σ��
	t->next = p;   //q��Ϊ���һ���ڵ���뵽ʹ����������
	return SUCCESS;
}

/*�����ɾ��������������ɾ���鼮��Ϣ����ɾ����������Ϣ*/
Status DeleteBorrow(Borrow *Q,unsigned int x)   //������
{
	int LOOP = 0;   //��¼�Ƿ���ɾ���ڵ�
	Borrow *pfirst,*psecond;
	for (pfirst = Q,psecond=pfirst->next; psecond != NULL; pfirst=psecond,psecond = psecond->next)   //��������
	{
		if (psecond->library_card == x)
		{
			LOOP = 1;
			pfirst->next = psecond->next;
			free(psecond);   //�ҵ���ɾ���洢��λ��������Ϣ�Ľڵ�
			return SUCCESS;
		}
		if (LOOP == 1) break;   //��ɾ����Ҫ�ҵĽڵ�
	}
}

Status DeleteBook(Book *L, char x[])   //�鱾
{
	int LOOP = 0;   //��¼�Ƿ���ɾ���ڵ�
	Book *pfirst, *psecond;
	for (pfirst = L, psecond = pfirst->next; psecond != NULL; pfirst = psecond, psecond = psecond->next)   //��������
	{
		if (strcmp(psecond->ISBN, x) == 0)
		{
			LOOP = 1;
			pfirst->next = psecond->next;
			free(psecond);   //�ҵ���ɾ���洢�Ȿ��Ľڵ�
			return SUCCESS;
		}
		if (LOOP == 1) break;   //��ɾ����Ҫ�ҵĽڵ�
	}
}
