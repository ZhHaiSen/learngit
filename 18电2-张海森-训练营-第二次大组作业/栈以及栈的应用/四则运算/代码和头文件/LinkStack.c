#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int I = 0;

//链栈(基于链表的)
Status initLStack(LinkStack *s)   //初始化
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (s->top == NULL)
	{
		printf("内存不足\n");
		return ERROR;
	}
	s->top->data = 0;
	s->top->next = NULL;
	s->count = 0;
	return OK;
}

Status isEmptyLStack(LinkStack *s)  //判断链栈是否为空
{
	if (s->count==0)
	{
		return ERROR;
	}
	if (s->count>0)
	{
		return OK;
	}
}

Status getTopLStack(LinkStack *s, ElemType *e)  //得到栈顶元素
{
	if (s->count==0)
	{
;		return ERROR;
	}
	if (s->count>0)
	{
		*e = s->top->data;
		return OK;
	}
}

Status clearLStack(LinkStack *s)   //清空栈
{
	if (s->count == 0)
	{
		return ERROR;
	}
	if (s->count > 0)
	{
		LinkStack *p, *current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		p->top = s->top;
		current->top = s->top->next;
		for (; current->top->next != NULL; p->top = current->top, current->top = current->top->next)
		{
			free(p->top);
			I--;
		}
		I--;
		current->count = I;
		*s = *current;
		return OK;
	}
}

Status destroyLStack(LinkStack *s)   //销毁栈
{
	free(s->top);
	return OK;
}

Status LStackLength(LinkStack *s, int *length)    //检测栈长度
{
	if (s->count == 0)
	{
		return ERROR;
	}
	if (s->count != 0)
	{
		*length = s->count;
		return OK;
	}
}

Status pushLStack(LinkStack *s, ElemType data)   //入栈
{
	LinkStack *current;
	current= (LinkStack *)malloc(sizeof(LinkStack));
	current->top = (LinkStackPtr)malloc(sizeof(StackNode));
	current->top->data = data;
	current->top->next = s->top;
	I++;
	current->count = I;
	*s = *current;
	return OK;
}

Status popLStack(LinkStack *s, ElemType *data)   //出栈
{
	if (s->count == 0)
	{
		return ERROR;
	}
	if (s->count > 0)
	{
		LinkStack *p,*current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		*data = s->top->data;
		p->top = s->top;
		current->top = s->top->next;
		free(p->top);
		I--;
		current->count = I;
		*s = *current;
		return OK;
	}
}
