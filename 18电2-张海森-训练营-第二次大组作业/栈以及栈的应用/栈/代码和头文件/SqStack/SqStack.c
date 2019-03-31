#include <stdio.h>
#include <stdbool.h>
#include "SqStack.h"

//顺序栈(基于数组的)
Status initStack(SqStack *s, int sizes)  //初始化栈
{
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));   //为栈分配空间
	if (s->elem == NULL)   //内存不足
		return ERROR;
	s->top = -1;   //头指针为-1
	s->size = sizes;   //栈的大小
	printf("成功创建一个顺序栈\n");
	return OK;
}

bool isEmptyStack(SqStack *s)   //判断栈是否为空
{
	if (s->top == -1)   //头指针未指向任何栈元素
	{
		printf("这是一个空栈\n");
		return 1;
	}
	if (s->top >= 0)   //头指针指向栈元素
	{
		printf("这不是一个空栈\n");
		return 0;
	}
}

Status getTopStack(SqStack *s, ElemType *e)   //得到栈顶元素
{
	if (s->top == -1)   //空栈
	{
		printf("没有栈顶元素\n");
		return ERROR;
	}
	if (s->top > -1)   //非空栈
	{
		*e = s->elem[s->top];   //得到栈顶元素
		printf("成功得到栈顶元素\n");
		printf("栈顶元素为%d\n", *e);
		return OK;
	}
}

Status clearStack(SqStack *s)   //清空栈
{
	if (s->top == -1)   //空栈
	{
		printf("已经是空栈\n");
		return ERROR;
	}
	if (s->top > -1)   //非空栈
	{
		for (; s->top != -1; s->top--)
		{
			free(s->elem[s->top]);   //释放所有栈节点的内存
		}
		printf("已经成功清空栈\n");
		return OK;
	}
}

Status destroyStack(SqStack *s)  //销毁栈
{
	free(s->elem);   //释放栈的空间
	printf("成功销毁栈\n");
	return OK;
}

Status stackLength(SqStack *s, int length)   //检测栈
{
	length = s->top + 1;   //length=top+1
	printf("这个栈共有%d个元素\n", length);
	return OK;
}

Status pushStack(SqStack *s, ElemType data)  //入栈
{
	if (s == NULL || s->top == s->size)   //栈满
		s->elem[s->top + 1] = (ElemType *)malloc(s->size * sizeof(ElemType));
	s->top++;   //栈顶指针指向新加入的节点
	s->elem[s->top] = data;   //为新加入的节点赋值
	printf("入栈成功\n");
	return OK;
}

Status popStack(SqStack *s, ElemType *data)   //出栈
{
	if (s == NULL || s->top == -1)   //空栈
	{
		printf("当前栈为一个空栈\n");
		return ERROR;
	}
	else   //非空栈
	{
		*data = s->elem[s->top];   //得到栈顶元素
		s->top--;   //栈顶指针指向下一个节点
		printf("出栈成功\n");
		return OK;
	}
}


