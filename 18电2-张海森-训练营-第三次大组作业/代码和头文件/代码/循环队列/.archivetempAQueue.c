#include <stdio.h>
#include <stdlib.h>
#include ".archivetempAQueue.h"

extern record[MAXQUEUE];   //记录状态
extern count;   //用于计第几个
extern i;
extern current;   //循环
int qnumber = 0;   
q = &qnumber;   //*q
int length, *Length;   //队列长度
void visit(void *q)   //遍历函数
{
	qnumber++;
}
foo = &visit;

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q)
{
	Q->front = -1;
	Q->rear = -1;   //指针赋值
	Q->length = 0;   //长度为0
	printf("已经为你初始化一个循环队列\n");
}

/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	printf("已经成功为你销毁队列\n");
}

/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if (Q->length == MAXQUEUE)   //满队列
	{
		printf("队列已满\n");
		return TRUE;
	}
	if (Q->length < MAXQUEUE)   //非满队列
	{
		printf("队列未满\n");
		return FALSE;
	}
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	if (Q->length == 0)   //空队列
	{
		printf("队列为空\n");
		return TRUE;
	}
	if (Q->length > 0)   //非空队列
	{
		printf("队列不空\n");
		return FALSE;
	}
}

/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	if (Q->length == 0)   //空队列
	{
		printf("没有队头元素\n");
		return FALSE;
	}
	if (Q->length > 0)   //非空队列
	{
		if (record[Q->front] == 1)   //char
		{
			char *p = Q->data[Q->front];
			printf("队头元素为%c\n", *p);
		}
		if (record[Q->front] == 2)   //int
		{
			int *p = Q->data[Q->front];
			printf("队头元素为%d\n", *p);
		}
		if (record[Q->front] == 3)   //float
		{
			float *p = Q->data[Q->front];
			printf("队头元素为%f\n", *p);
		}
	}
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	if (Q->length == 0)   //空队列
	{
		printf("这是一个空队列\n");
		return FALSE;
	}
	if (Q->length > 0)   //非空队列
	{
		printf("这个队列的长度为%d", Q->length);
		return TRUE;
	}
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data)
{
	if (Q->length == MAXQUEUE)   //满队列
	{
		printf("队列已满\n");
		return FALSE;
	}
	else if(Q->length==0)   //空队列
	{
		(Q->front)++;
		(Q->rear)++;   //front和rear同时为一个数
		Q->data[Q->front] = data;   //赋值
		printf("入队成功\n");
		(Q->length)++;
		return TRUE;
	}
	else
	{
		(Q->rear)++;    //尾元素下移
		if (Q->rear == MAXQUEUE)   //过头，从头循环
			Q->rear = 0;
		Q->data[Q->rear] = data;   //赋值
		(Q->length)++;   //长度+1
		printf("入队成功\n");
		return TRUE;
	}
}

/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	if (Q->length == 0)   //空队列
	{
		printf("已经是一个空队列\n");
		return FALSE;
	}
	if (Q->length == 1)   //只有一个元素
	{
		Q->front = -1;
		Q->rear = -1;   //front和rear同时为-1，不代表任何数值
		(Q->length)--;   //长度-1
		printf("出队成功\n");
		return TRUE;
	}
	if (Q->length > 1)
	{
		(Q->front)++;   //头元素下移
		if (Q->front == MAXQUEUE)   //front过了原来的尾则从头再来
			Q->front = 0;
		(Q->length)--;   //长度-1
		printf("出队成功\n");
		return TRUE;
	}
}

/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	if (Q->length == 0)   //空队列
		printf("这是一个空队列\n");
	if (Q->length > 0)   //非空队列
	{
		Q->length = 0;   //长度为0
		Q->rear = -1;
		Q->front = -1;   //frong和rear都不代表任何数值
		printf("已经为你清空队列\n");
	}
}

/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void(*foo)(void *q))
{
	for (i = 0, current = Q->front; i < Q->length; i++, current++)
		(*foo)(q);   //遍历队列
	printf("这个队列共有%d个元素\n", qnumber);
	length = qnumber;
	qnumber = 0;
	return TRUE;
}

/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
void APrint(void *q)
{
	q = &length; 
	Length = q;   //*q
	printf("上次*q的值是%d\n", *Length);
}
