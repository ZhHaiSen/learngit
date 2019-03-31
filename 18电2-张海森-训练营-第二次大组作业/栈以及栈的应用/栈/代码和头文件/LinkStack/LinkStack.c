#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int I = 0;

//链栈(基于链表的)
Status initLStack(LinkStack *s)   //初始化
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));   //为栈顶指针开辟空间
	if (s->top == NULL)   //内存不足
	{
		return ERROR;
	}
	s->top->data = 0;   //头节点
	s->top->next = NULL;   //头节点的next指针指向NULL
	s->count = 0;   //栈中元素个数
	return OK;
}

Status isEmptyLStack(LinkStack *s)  //判断链栈是否为空
{
	if (s->count==0)   //空栈
	{
		return ERROR;
	}
	if (s->count>0)   //非空栈
	{
		return OK;
	}
}

Status getTopLStack(LinkStack *s, ElemType *e)  //得到栈顶元素
{
	if (s->count==0)   //空栈
	{
		return ERROR;
	}
	if (s->count>0)   //非空栈
	{
		*e = s->top->data;   //得到栈顶元素
		return OK;
	}
}

Status clearLStack(LinkStack *s)   //清空栈
{
	if (s->count == 0)   //空栈
	{
		return ERROR;
	}
	if (s->count > 0)   //非空栈
	{
		LinkStack *p, *current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		p->top = s->top;
		current->top = s->top->next;
		for (; current->top->next != NULL; p->top = current->top, current->top = current->top->next)   //循环出栈
		{
			free(p->top);
			I--;
		}
		I--;
		current->count = I;
		*s = *current;   //将*s的改变保留下来
		return OK;
	}
}

Status destroyLStack(LinkStack *s)   //销毁栈
{
	free(s->top);   //释放栈的空间
	return OK;
}

Status LStackLength(LinkStack *s, int *length)    //检测栈长度
{
	if (s->count == 0)   //空栈
	{
		return ERROR;
	}
	if (s->count != 0)   //非空栈
	{
		*length = s->count;   //得到栈的长度
		return OK;
	}
}

Status pushLStack(LinkStack *s, ElemType data)   //入栈
{
	LinkStack *current;
	current= (LinkStack *)malloc(sizeof(LinkStack));
	current->top = (LinkStackPtr)malloc(sizeof(StackNode));
	current->top->data = data;   //为新节点赋值
	current->top->next = s->top;   //新节点指向栈顶元素
	I++;
	current->count = I;   //栈中元素加一
	*s = *current;   //新节点即为栈顶元素
	return OK;
}

Status popLStack(LinkStack *s, ElemType *data)   //出栈
{
	if (s->count == 0)   //空栈
	{
		return ERROR;
	}
	if (s->count > 0)
	{
		LinkStack *p,*current;
		p = (LinkStack *)malloc(sizeof(LinkStack));
		current = (LinkStack *)malloc(sizeof(LinkStack));
		*data = s->top->data;   //*data为出栈元素
		p->top = s->top;   //生成p指针，指向栈顶元素
		current->top = s->top->next;   //栈顶指针指向栈的第二个元素
		free(p->top);   //释放p节点所指空间
		I--;
		current->count = I;   //栈中元素减一
		*s = *current;   //栈中第二个元素即为栈顶元素
		return OK;
	}
}
