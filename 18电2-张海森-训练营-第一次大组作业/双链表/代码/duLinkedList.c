#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"

e = 1;

void search(ElemType e)
{
	printf("���ѵ���visit�����Ĵ���Ϊ��%d\n", e);
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
	*L = (DuLNode *)malloc(sizeof(DuLNode));   //Ϊͷ�ڵ㿪���ڴ�ռ�
	if (*L == NULL)
	{
		printf("�ڴ�ռ䲻�㣬�޷���ʼ��һ��������\n");
		return ERROR;                         //����ڴ治�㣬�ͷ���ERROR
	}
	(*L)->prior = NULL;                        //ͷ�ڵ��priorָ��ָ���
	(*L)->next = NULL;                         //ͷ�ڵ��nextָ��ָ���
	printf("�ѳɹ���ʼ��һ���µĿ�����\n");
	return SUCCESS;                           //��ʼ���ɹ�������SUCCESS
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	while ((*L)->next != NULL)   //���ýڵ㲻Ϊ���һ���ڵ�ʱ
	{
		(*L) = (*L)->next;   //*Lָ����һ���ڵ�
		free((*L)->prior);   //����*L����һ���ڵ�
	}
	free(*L);   //�������һ���ڵ�
	printf("�Ѿ��ɹ���������\n");   //��ʾ�ɹ�
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	if (p->prior == NULL)   //���p�ڵ�Ϊ��һ���ڵ�
		q->prior = NULL;   //q�ڵ��priorָ��ָ���
	else                   //���p�ڵ㲻�ǵ�һ���ڵ�
	{
		p->prior->next = q;   //ԭ����p��ǰһ���ֽڵ�priorָ��ָ��q
		q->prior = p->prior;   //q�ڵ��priorָ��ָ��p��ǰһ���ڵ�
	}
	q->next = p;   //q�ڵ��nextָ��ָ��p
	p->prior = q;   //p�ڵ��priorָ��ָ��q
	printf("q�ڵ��ѳɹ�����p�ڵ�ǰ\n");   //��ʾ�ɹ�
	return SUCCESS;   //����ɹ�������SUCCESS
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if (p->next == NULL)   //��pΪԭ�������һ���ڵ�ʱ
	{
		q->next = NULL;   //q��nextָ��ָ���
	}
	else               //p����ԭ�������һ���ڵ�
	{
		p->next->prior = q;   //ԭ����p�ĺ�һ���ֽڵ�priorָ��ָ��q
		q->next = p->next;   //q��nextָ��ָ��p����һ�ڵ�
	}
	q->prior = p;   //q��qriorָ��ָ��p
	p->next = q;          //p��nextָ��ָ��q
	printf("q�ڵ��ѳɹ�����p�ڵ��\n");   //��ʾ�ɹ�
	return SUCCESS;   //����ɹ�������SUCCESS
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
		if (p->next == NULL)   //���p�ڵ�Ϊ���һ���ڵ�
		{
			printf("����ڵ�֮��û�������Ľڵ�\n");
			return ERROR;   //ɾ��ʧ�ܣ�����ERROR
		}
		else if (p->next->next == NULL)   //���p�ڵ��ǵ����ڶ����ڵ�
		{
			p->next->prior = NULL;   //p����һ���ڵ��priorָ��ָ���
			p->next = NULL;   //p��nextָ��ָ���
			printf("�ɹ�ɾ��p�ڵ��ĵ�һ���ڵ㲢��p�ڵ㸳ֵe\n");
		}
		else
		{
			p->next = p->next->next;   //p��nextָ��ָ��p�ĺ���������ڵ�
			p->next->next->prior = p;   //p�ĺ���ڶ����ڵ��priorָ��ָ��p
			printf("�ɹ�ɾ��p�ڵ��ĵ�һ���ڵ㲢��p�ڵ㸳ֵe\n");
		}
		p->data = *e;   //����Ҫ����ֵ����p��data
	}
 
/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit 
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLinkedList current = L;   //����һ��ָ��ǰ�ڵ��ָ��
	while (current != NULL)   //��������
	{
		if (current->next == NULL)
		{
			visit(e);   //call  visit����
		}
		e++;
		current = current->next;
	}
}

