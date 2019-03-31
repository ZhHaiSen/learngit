#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int I = 0;

//��ջ(���������)
Status initLStack(LinkStack *s)   //��ʼ��
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));   //Ϊջ��ָ�뿪�ٿռ�
	if (s->top == NULL)   //�ڴ治��
	{
		return ERROR;
	}
	s->top->data = 0;   //ͷ�ڵ�
	s->top->next = NULL;   //ͷ�ڵ��nextָ��ָ��NULL
	s->count = 0;   //ջ��Ԫ�ظ���
	return OK;
}

Status isEmptyLStack(LinkStack *s)  //�ж���ջ�Ƿ�Ϊ��
{
	if (s->count==0)   //��ջ
	{
		return ERROR;
	}
	if (s->count>0)   //�ǿ�ջ
	{
		return OK;
	}
}

Status getTopLStack(LinkStack *s, ElemType *e)  //�õ�ջ��Ԫ��
{
	if (s->count==0)   //��ջ
	{
		return ERROR;
	}
	if (s->count>0)   //�ǿ�ջ
	{
		*e = s->top->data;   //�õ�ջ��Ԫ��
		return OK;
	}
}

Status clearLStack(LinkStack *s)   //���ջ
{
	if (s->count == 0)   //��ջ
	{
		return ERROR;
	}
	if (s->count > 0)   //�ǿ�ջ
	{
		LinkStack *p, *current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		p->top = s->top;
		current->top = s->top->next;
		for (; current->top->next != NULL; p->top = current->top, current->top = current->top->next)   //ѭ����ջ
		{
			free(p->top);
			I--;
		}
		I--;
		current->count = I;
		*s = *current;   //��*s�ĸı䱣������
		return OK;
	}
}

Status destroyLStack(LinkStack *s)   //����ջ
{
	free(s->top);   //�ͷ�ջ�Ŀռ�
	return OK;
}

Status LStackLength(LinkStack *s, int *length)    //���ջ����
{
	if (s->count == 0)   //��ջ
	{
		return ERROR;
	}
	if (s->count != 0)   //�ǿ�ջ
	{
		*length = s->count;   //�õ�ջ�ĳ���
		return OK;
	}
}

Status pushLStack(LinkStack *s, ElemType data)   //��ջ
{
	LinkStack *current;
	current= (LinkStack *)malloc(sizeof(LinkStack));
	current->top = (LinkStackPtr)malloc(sizeof(StackNode));
	current->top->data = data;   //Ϊ�½ڵ㸳ֵ
	current->top->next = s->top;   //�½ڵ�ָ��ջ��Ԫ��
	I++;
	current->count = I;   //ջ��Ԫ�ؼ�һ
	*s = *current;   //�½ڵ㼴Ϊջ��Ԫ��
	return OK;
}

Status popLStack(LinkStack *s, ElemType *data)   //��ջ
{
	if (s->count == 0)   //��ջ
	{
		return ERROR;
	}
	if (s->count > 0)
	{
		LinkStack *p,*current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		*data = s->top->data;   //*dataΪ��ջԪ��
		p->top = s->top;   //����pָ�룬ָ��ջ��Ԫ��
		current->top = s->top->next;   //ջ��ָ��ָ��ջ�ĵڶ���Ԫ��
		free(p->top);   //�ͷ�p�ڵ���ָ�ռ�
		I--;
		current->count = I;   //ջ��Ԫ�ؼ�һ
		*s = *current;   //ջ�еڶ���Ԫ�ؼ�Ϊջ��Ԫ��
		return OK;
	}
}
