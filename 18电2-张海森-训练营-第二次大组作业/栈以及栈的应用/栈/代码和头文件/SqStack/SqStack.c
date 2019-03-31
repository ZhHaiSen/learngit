#include <stdio.h>
#include <stdbool.h>
#include "SqStack.h"

//˳��ջ(���������)
Status initStack(SqStack *s, int sizes)  //��ʼ��ջ
{
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));   //Ϊջ����ռ�
	if (s->elem == NULL)   //�ڴ治��
		return ERROR;
	s->top = -1;   //ͷָ��Ϊ-1
	s->size = sizes;   //ջ�Ĵ�С
	printf("�ɹ�����һ��˳��ջ\n");
	return OK;
}

bool isEmptyStack(SqStack *s)   //�ж�ջ�Ƿ�Ϊ��
{
	if (s->top == -1)   //ͷָ��δָ���κ�ջԪ��
	{
		printf("����һ����ջ\n");
		return 1;
	}
	if (s->top >= 0)   //ͷָ��ָ��ջԪ��
	{
		printf("�ⲻ��һ����ջ\n");
		return 0;
	}
}

Status getTopStack(SqStack *s, ElemType *e)   //�õ�ջ��Ԫ��
{
	if (s->top == -1)   //��ջ
	{
		printf("û��ջ��Ԫ��\n");
		return ERROR;
	}
	if (s->top > -1)   //�ǿ�ջ
	{
		*e = s->elem[s->top];   //�õ�ջ��Ԫ��
		printf("�ɹ��õ�ջ��Ԫ��\n");
		printf("ջ��Ԫ��Ϊ%d\n", *e);
		return OK;
	}
}

Status clearStack(SqStack *s)   //���ջ
{
	if (s->top == -1)   //��ջ
	{
		printf("�Ѿ��ǿ�ջ\n");
		return ERROR;
	}
	if (s->top > -1)   //�ǿ�ջ
	{
		for (; s->top != -1; s->top--)
		{
			free(s->elem[s->top]);   //�ͷ�����ջ�ڵ���ڴ�
		}
		printf("�Ѿ��ɹ����ջ\n");
		return OK;
	}
}

Status destroyStack(SqStack *s)  //����ջ
{
	free(s->elem);   //�ͷ�ջ�Ŀռ�
	printf("�ɹ�����ջ\n");
	return OK;
}

Status stackLength(SqStack *s, int length)   //���ջ
{
	length = s->top + 1;   //length=top+1
	printf("���ջ����%d��Ԫ��\n", length);
	return OK;
}

Status pushStack(SqStack *s, ElemType data)  //��ջ
{
	if (s == NULL || s->top == s->size)   //ջ��
		s->elem[s->top + 1] = (ElemType *)malloc(s->size * sizeof(ElemType));
	s->top++;   //ջ��ָ��ָ���¼���Ľڵ�
	s->elem[s->top] = data;   //Ϊ�¼���Ľڵ㸳ֵ
	printf("��ջ�ɹ�\n");
	return OK;
}

Status popStack(SqStack *s, ElemType *data)   //��ջ
{
	if (s == NULL || s->top == -1)   //��ջ
	{
		printf("��ǰջΪһ����ջ\n");
		return ERROR;
	}
	else   //�ǿ�ջ
	{
		*data = s->elem[s->top];   //�õ�ջ��Ԫ��
		s->top--;   //ջ��ָ��ָ����һ���ڵ�
		printf("��ջ�ɹ�\n");
		return OK;
	}
}


