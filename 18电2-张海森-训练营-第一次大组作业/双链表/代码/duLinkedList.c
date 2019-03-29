#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"

e = 1;

void search(ElemType e)
{
	printf("你已调用visit函数的次数为：%d\n", e);
}

void(*visit)(ElemType e)=&search;

/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	*L = (DuLNode *)malloc(sizeof(DuLNode));   //为头节点开辟内存空间
	if (*L == NULL)
	{
		printf("内存空间不足，无法初始化一个新链表\n");
		return ERROR;                         //如果内存不足，就返回ERROR
	}
	(*L)->prior = NULL;                        //头节点的prior指针指向空
	(*L)->next = NULL;                         //头节点的next指针指向空
	printf("已成功初始化一个新的空链表\n");
	return SUCCESS;                           //初始化成功，返回SUCCESS
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	while ((*L)->next != NULL)   //当该节点不为最后一个节点时
	{
		(*L) = (*L)->next;   //*L指向下一个节点
		free((*L)->prior);   //销毁*L的上一个节点
	}
	free(*L);   //销毁最后一个节点
	printf("已经成功销毁链表\n");   //提示成功
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	if (p->prior == NULL)   //如果p节点为第一个节点
		q->prior = NULL;   //q节点的prior指针指向空
	else                   //如果p节点不是第一个节点
	{
		p->prior->next = q;   //原来的p的前一个字节的prior指针指向q
		q->prior = p->prior;   //q节点的prior指针指向p的前一个节点
	}
	q->next = p;   //q节点的next指针指向p
	p->prior = q;   //p节点的prior指针指向q
	printf("q节点已成功插入p节点前\n");   //提示成功
	return SUCCESS;   //插入成功，返回SUCCESS
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if (p->next == NULL)   //当p为原来的最后一个节点时
	{
		q->next = NULL;   //q的next指针指向空
	}
	else               //p不是原来的最后一个节点
	{
		p->next->prior = q;   //原来的p的后一个字节的prior指针指向q
		q->next = p->next;   //q的next指针指向p的下一节点
	}
	q->prior = p;   //q的qrior指针指向p
	p->next = q;          //p的next指针指向q
	printf("q节点已成功插入p节点后\n");   //提示成功
	return SUCCESS;   //插入成功，返回SUCCESS
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
	Status DeleteList_DuL(DuLNode *p, ElemType *e) 
	{
		if (p->next == NULL)   //如果p节点为最后一个节点
		{
			printf("这个节点之后没有其它的节点\n");
			return ERROR;   //删除失败，返回ERROR
		}
		else if (p->next->next == NULL)   //如果p节点是倒数第二个节点
		{
			p->next->prior = NULL;   //p的下一个节点的prior指针指向空
			p->next = NULL;   //p的next指针指向空
			printf("成功删除p节点后的第一个节点并给p节点赋值e\n");
		}
		else
		{
			p->next = p->next->next;   //p的next指针指向p的后面第两个节点
			p->next->next->prior = p;   //p的后面第二个节点的prior指针指向p
			printf("成功删除p节点后的第一个节点并给p节点赋值e\n");
		}
		p->data = *e;   //将需要赋的值赋给p的data
	}
 
/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit 
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLinkedList current = L;   //定义一个指向当前节点的指针
	while (current != NULL)   //遍历链表
	{
		if (current->next == NULL)
		{
			visit(e);   //call  visit函数
		}
		e++;
		current = current->next;
	}
}

