#include <stdio.h>
#include <stdlib.h>
#include ".archivetempLQueue.h"

E = 0;   //查看队头元素
Node *pr;   //遍历队列
int qnumber = 0;   //*q
q=&qnumber;
int length,*Length;   //保留*q
void visit(void *q)   //遍历函数
{
	qnumber++;
}
foo = &visit;

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
	Q->front = (Node *)malloc(sizeof(Node));   //为头指针的指向开辟一个空间
	if (Q->front == NULL)
		printf("内存不足");
	Q->rear = Q->front;   //front和rear都指向头指针
	Q->length = 0;   //为空队列
	Q->front->next = NULL;
	printf("已经为你初始化一个新队列\n");
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	free(Q->front);   //销毁为头指针开辟的空间
	printf("已经为你销毁一个队列\n");
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if (Q->length == 0)   //空队列
	{
		printf("这是一个空队列\n");
		return FALSE;
	}
	if (Q->length > 0)   //非空队列
	{
		printf("这不是一个空队列\n");
		return TRUE;
	}
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	if (Q->length == 0)   //空队列
	{
		printf("没有队头元素\n");
		return FALSE;
	}
	if (Q->length > 0)   //非空队列
	{
		int Temp = 0, *temp = &Temp;
		temp = Q->front->next->data;
		E = *temp;    //利用int指针将结构体中的地址转化为值并显示
		printf("队头元素为%d\n", E);
		return TRUE;
	}
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	if (Q->length == 0)   //空队列
		printf("这是一个空队列\n");
	if (Q->length > 0)   //非空队列
	{
		printf("这个队列的长度为%d\n", Q->length);
		return Q->length;
	}
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data)
{
	Node *p = (Node *)malloc(sizeof(Node));   //开辟新节点
	if (p == NULL)
	{
		printf("内存不足\n");
		return FALSE;
	}
	if (Q->length == 0)   //空队列
	{
		p->next = NULL;
		p->data = data;   //为新节点赋值
		Q->rear = p;   //新的尾指针
		Q->front->next = Q->rear;   //头指针指向尾指针
	}
	if (Q->length > 0)
	{
		p->next = NULL;
		p->data = data;   //为新节点赋值
		Q->rear->next = p;   //原来的尾指针的next指向新节点
		Q->rear = p;   //新的尾指针
	}
	(Q->length)++;   //长度+1
	printf("入队成功\n");
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	if (Q->length == 0)   //空队列
	{
		printf("这是一个空队列\n");
		return FALSE;
	}
	if (Q->length > 0)   //非空队列
	{
		Node *p;   
		p = Q->front->next;   //保留头指针
		Q->front->next = Q->front->next->next;   //头指针下移一个单位
		free(p);   //释放原来的头指针指向的区域
		(Q->length)--;   //长度-1
		printf("出队成功\n");
		return TRUE;
	}
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	if (Q->length == 0)   //空队列
		printf("这是一个空队列\n");
	if (Q->length > 0)   //非空队列
	{
		free(Q->front->next);   //释放第一个节点
		Q->rear = Q->front;   //rear和front都指向头指针
		Q->front->next = NULL;
		Q->length = 0;   //长度为0
		printf("清空成功\n");
	}
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void(*foo)(void *q))
{
	for (pr = Q->front->next; pr != NULL; pr = pr->next)
		(*foo)(q);   //遍历队列并累加队列元素个数
	printf("这个队列共有%d个元素\n", qnumber);
	length = qnumber;
	qnumber = 0;
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q

 *  @notice      : None
 */
void LPrint(void *q)
{
	q = &length;   //q为上次保留的*q的地址
	Length = q;
	printf("上次*q的值是%d\n",*Length);
}
