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
	*L = (LNode *)malloc(sizeof(LNode));   //Ϊͷ�ڵ㿪���ڴ�ռ�
	if (*L == NULL)
	{
		printf("�ڴ�ռ䲻�㣬�޷���ʼ��һ��������\n");
		return ERROR;                       //����ڴ治�㣬�ͷ���ERROR
	}
	(*L)->next = NULL;                        //ͷ�ڵ��nextָ��ָ���
	printf("�ѳɹ���ʼ��һ���µĿ�����\n");
	return SUCCESS;                         //��ʼ���ɹ�������SUCCESS
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	LinkedList temp;   //����һ��ָ�벢ָ��ͷ�ڵ㣬�Լ�һ����ʱָ�����ڱ�����Ҫ�ͷŵĽڵ�
	while ((*L) != NULL)   //��current��Ϊ��ָ��ʱִ��ѭ������������
	{
		temp = (*L)->next;      //����һ��ָ��ǰ�ڵ��ָ��
		free(*L);   //currentָ����һ���ڵ�
		*L = temp;        //�ͷŵ�ǰ�ڵ��ڴ�
	}
	printf("�Ѿ��ɹ����ٵ�ǰ����\n");
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if (p->next == NULL)   //��pΪԭ�������һ���ڵ�ʱ
		q->next = NULL;   //q��nextָ��ָ���
	else               //p����ԭ�������һ���ڵ�
		q->next = p->next;   //q��nextָ��ָ��p����һ�ڵ�
	p->next = q;          //p��nextָ��ָ��q
	printf("q�ڵ��ѳɹ�����p�ڵ��\n");
	return SUCCESS;   //����ɹ�������SUCCESS
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	if (p->next == NULL)   //����������һ���ڵ�
	{
		printf("����ڵ�֮��û�������Ľڵ�\n");   //�޷�ɾ��
		return ERROR;   //����ERROR
	}
	else   //�������һ���ڵ�
	{
		p->next = p->next->next;   //p��nextָ��ָ��p�ĺ����2���ڵ����ָ���
		p->data = *e;   //��p�ڵ��ֵ���e
		printf("�ɹ�ɾ��p�ڵ��ĵ�һ���ڵ㲢��p�ڵ㸳ֵe\n");   //��ʾ�ɹ�
		return SUCCESS;   //ɾ���ɹ�����ֵ�ɹ�������SUCCESS
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
	LinkedList current = L;   //����һ��ָ��ǰ�ڵ��ָ��
	while (current != NULL)   //��������
	{
		*visit;   //call  visit����
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
	LinkedList current = L;   //currentָ�����ڼ�¼��ǰλ��
	while (current != NULL)   //��������ֱ�����һ���ڵ�
	{
		if (current->data == e)   //�ҵ�����ֵλ�ڵĽڵ�
		{
			printf("�ɹ��ҵ��ýڵ�\n");
			return SUCCESS;
		}
		if (current->data == e) break;   //�ҵ�����ڵ������ѭ��
		current = current->next;   //currentָ����һ�ڵ�
	}
	if (current == NULL)   //�������������û���ҵ�
	{
		printf("δ���ҵ��ýڵ�\n");   //����ʧ��
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
	LinkedList thisnode = *L, nextnode=(*L)->next, save=nextnode->next;   //����һ��ָ��ǰ�ڵ��ָ�룬һ��ָ����һ�ڵ��ָ�룬һ���������¸��ڵ��ָ��
	while (save!= NULL)    //ֱ��thisnode��nextnode�ֱ�ָ���������ڵ�
	{
		nextnode->next = thisnode;   //nextnodeָ��thisnode
		thisnode = nextnode;   //thisnode����
		nextnode = save;       //nextnode����
		save = nextnode->next;   //save�ٴα������¸��ڵ��ָ��
	}
	nextnode->next = thisnode;   //����ѭ��ʱ�����������ڵ�δ�ı�ָ�򣬹�Ҫ�ı�ָ��
	(*L)->next = NULL;   //��һ���ڵ�ָ���
	*L = nextnode;   //ͷָ��ָ�����һ���ڵ�
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LinkedList current = L;   //����һ��ָ��ǰ�ڵ��ָ��
	while (1)
	{
		if (current == NULL)   //������һ���ڵ�ָ��գ����ǻ�������
		{
			printf("�ⲻ��һ����������\n");
			return ERROR;
		}
		if (current == NULL) break;   //����ѭ��
		if (current == L)   //������һ���ڵ���ָ���һ���ڵ㣬�ǻ�������
		{
			printf("����һ����������\n");
			return SUCCESS;
		}
		if (current == NULL) break;   //����ѭ��
		current = current->next;   //currentָ��ָ����һ���ڵ�
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
	LinkedList  thisnode = *L, nextnode,compare;   //����һ��ָ��ǰ�ڵ��ָ�룬һ��ָ����һ�ڵ��ָ�룬һ�����ڽ�����ָ��
	nextnode = thisnode->next;   //nextnodeָ��thisnode����һ��
	if (nextnode->data % 2 == 0)   //����ڶ�����Ϊż��
		return nextnode;   //��Ҫ����ͷָ��
	else   //�ڶ����ڵ㲻Ϊż��
		return *L;   //����ı�ͷָ��
	while (nextnode->next != NULL)   //��nextnode�������һ���ڵ�
	{
		if ((nextnode->data) % 2 == 0)   //�����һ�ڵ��ֵΪż��
		{
			compare = thisnode;
			thisnode = nextnode;   
			nextnode = compare;   //��Ϊ��ת���ָ��ָ����׼��
			nextnode->next = nextnode->next->next;   //ǰһ���ڵ�ָ�����ĺ������ڵ�
			thisnode->next = nextnode;   //��һ���ڵ�ָ��ǰһ���ڵ�
		}
		thisnode = nextnode;  //thisnodeָ����һ���ڵ�
		nextnode = nextnode->next;   //nextnodeָ����һ���ڵ�
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
	LinkedList current = *L;   //����һ��ָ��ָ��ǰ�ڵ�
	int i1, i2;   //���ڼ�����ѭ��
	for (i1 = 1; current != NULL; i1++)   //�ƹ��ж��ٽڵ�
		current = current->next;
	current = *L;   //current����ָ��ͷ�ڵ�
	for (i2 = 1; i2 < i1 / 2; i2++)   //��currentָ���м�Ľڵ�
		current = current->next;
	*L = current;   //��*L���и�ֵ���ı�����ֵ��������������
	return *L;   //����*L
}
