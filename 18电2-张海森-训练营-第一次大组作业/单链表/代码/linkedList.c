#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void search(ElemType e)
{
	e = e + 1;
}

void(*visit)(ElemType e);

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
	*L = (LNode *)malloc(sizeof(LNode));   //为头节点开辟内存空间
	if (*L == NULL)
	{
		printf("内存空间不足，无法初始化一个新链表\n");
		return ERROR;                       //如果内存不足，就返回ERROR
	}
	(*L)->next = NULL;                        //头节点的next指针指向空
	printf("已成功初始化一个新的空链表\n");
	return SUCCESS;                         //初始化成功，返回SUCCESS
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	LinkedList temp;   //定义一个指针并指向头节点，以及一个临时指针用于保存所要释放的节点
	while ((*L) != NULL)   //当current不为空指针时执行循环，遍历链表
	{
		temp = (*L)->next;      //保留一个指向当前节点的指针
		free(*L);   //current指向下一个节点
		*L = temp;        //释放当前节点内存
	}
	printf("已经成功销毁当前链表\n");
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if (p->next == NULL)   //当p为原来的最后一个节点时
		q->next = NULL;   //q的next指针指向空
	else               //p不是原来的最后一个节点
		q->next = p->next;   //q的next指针指向p的下一节点
	p->next = q;          //p的next指针指向q
	printf("q节点已成功插入p节点后\n");
	return SUCCESS;   //插入成功，返回SUCCESS
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	if (p->next == NULL)   //如果这是最后一个节点
	{
		printf("这个节点之后没有其它的节点\n");   //无法删除
		return ERROR;   //返回ERROR
	}
	else   //不是最后一个节点
	{
		p->next = p->next->next;   //p的next指针指向p的后面第2个节点或者指向空
		p->data = *e;   //把p节点的值设成e
		printf("成功删除p节点后的第一个节点并给p节点赋值e\n");   //提示成功
		return SUCCESS;   //删除成功，赋值成功，返回SUCCESS
	}
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit 
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	LinkedList current = L;   //定义一个指向当前节点的指针
	while (current != NULL)   //遍历链表
	{
		*visit;   //call  visit函数
		current = current->next;
	}
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e 
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	LinkedList current = L;   //current指针用于记录当前位置
	while (current != NULL)   //遍历链表，直到最后一个节点
	{
		if (current->data == e)   //找到所给值位于的节点
		{
			printf("成功找到该节点\n");
			return SUCCESS;
		}
		if (current->data == e) break;   //找到所需节点就跳出循环
		current = current->next;   //current指向下一节点
	}
	if (current == NULL)   //如果遍历完链表都没有找到
	{
		printf("未能找到该节点\n");   //查找失败
		return ERROR;
	}
} 

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list 
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	LinkedList thisnode = *L, nextnode=(*L)->next, save=nextnode->next;   //定义一个指向当前节点的指针，一个指向下一节点的指针，一个保留下下个节点的指针
	while (save!= NULL)    //直到thisnode和nextnode分别指向倒数两个节点
	{
		nextnode->next = thisnode;   //nextnode指向thisnode
		thisnode = nextnode;   //thisnode后移
		nextnode = save;       //nextnode后移
		save = nextnode->next;   //save再次保留下下个节点的指针
	}
	nextnode->next = thisnode;   //跳出循环时，倒数两个节点未改变指向，故要改变指向
	(*L)->next = NULL;   //第一个节点指向空
	*L = nextnode;   //头指针指向最后一个节点
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LinkedList current = L;   //定义一个指向当前节点的指针
	while (1)
	{
		if (current == NULL)   //发现有一个节点指向空，不是环形链表
		{
			printf("这不是一个环形链表\n");
			return ERROR;
		}
		if (current == NULL) break;   //跳出循环
		if (current == L)   //发现有一个节点又指向第一个节点，是环形链表
		{
			printf("这是一个环形链表\n");
			return SUCCESS;
		}
		if (current == NULL) break;   //跳出循环
		current = current->next;   //current指针指向下一个节点
	}
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish 
 */
LNode* ReverseEvenList(LinkedList *L) {
	LinkedList  thisnode = *L, nextnode,compare;   //定义一个指向当前节点的指针，一个指向下一节点的指针，一个用于交换的指针
	nextnode = thisnode->next;   //nextnode指向thisnode的下一个
	if (nextnode->data % 2 == 0)   //如果第二个就为偶数
		return nextnode;   //需要更改头指针
	else   //第二个节点不为偶数
		return *L;   //不需改变头指针
	while (nextnode->next != NULL)   //当nextnode不到最后一个节点
	{
		if ((nextnode->data) % 2 == 0)   //如果下一节点的值为偶数
		{
			compare = thisnode;
			thisnode = nextnode;   
			nextnode = compare;   //现为反转后的指针指向做准备
			nextnode->next = nextnode->next->next;   //前一个节点指向它的后两个节点
			thisnode->next = nextnode;   //下一个节点指向前一个节点
		}
		thisnode = nextnode;  //thisnode指向下一个节点
		nextnode = nextnode->next;   //nextnode指向下一个节点
	}
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish 
 */
LNode* FindMidNode(LinkedList *L) {
	LinkedList current = *L;   //设置一个指针指向当前节点
	int i1, i2;   //用于计数、循环
	for (i1 = 1; current != NULL; i1++)   //计共有多少节点
		current = current->next;
	current = *L;   //current重新指向头节点
	for (i2 = 1; i2 < i1 / 2; i2++)   //让current指向中间的节点
		current = current->next;
	*L = current;   //对*L经行赋值，改变它的值并传回主调函数
	return *L;   //返回*L
}
