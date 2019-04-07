#include <stdio.h>
#include <stdlib.h>
#include ".archivetempLQueue.h"

E = 0;   //�鿴��ͷԪ��
Node *pr;   //��������
int qnumber = 0;   //*q
q=&qnumber;
int length,*Length;   //����*q
void visit(void *q)   //��������
{
	qnumber++;
}
foo = &visit;

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
	Q->front = (Node *)malloc(sizeof(Node));   //Ϊͷָ���ָ�򿪱�һ���ռ�
	if (Q->front == NULL)
		printf("�ڴ治��");
	Q->rear = Q->front;   //front��rear��ָ��ͷָ��
	Q->length = 0;   //Ϊ�ն���
	Q->front->next = NULL;
	printf("�Ѿ�Ϊ���ʼ��һ���¶���\n");
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	free(Q->front);   //����Ϊͷָ�뿪�ٵĿռ�
	printf("�Ѿ�Ϊ������һ������\n");
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	if (Q->length == 0)   //�ն���
	{
		printf("����һ���ն���\n");
		return FALSE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		printf("�ⲻ��һ���ն���\n");
		return TRUE;
	}
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	if (Q->length == 0)   //�ն���
	{
		printf("û�ж�ͷԪ��\n");
		return FALSE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		int Temp = 0, *temp = &Temp;
		temp = Q->front->next->data;
		E = *temp;    //����intָ�뽫�ṹ���еĵ�ַת��Ϊֵ����ʾ
		printf("��ͷԪ��Ϊ%d\n", E);
		return TRUE;
	}
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	if (Q->length == 0)   //�ն���
		printf("����һ���ն���\n");
	if (Q->length > 0)   //�ǿն���
	{
		printf("������еĳ���Ϊ%d\n", Q->length);
		return Q->length;
	}
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data)
{
	Node *p = (Node *)malloc(sizeof(Node));   //�����½ڵ�
	if (p == NULL)
	{
		printf("�ڴ治��\n");
		return FALSE;
	}
	if (Q->length == 0)   //�ն���
	{
		p->next = NULL;
		p->data = data;   //Ϊ�½ڵ㸳ֵ
		Q->rear = p;   //�µ�βָ��
		Q->front->next = Q->rear;   //ͷָ��ָ��βָ��
	}
	if (Q->length > 0)
	{
		p->next = NULL;
		p->data = data;   //Ϊ�½ڵ㸳ֵ
		Q->rear->next = p;   //ԭ����βָ���nextָ���½ڵ�
		Q->rear = p;   //�µ�βָ��
	}
	(Q->length)++;   //����+1
	printf("��ӳɹ�\n");
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	if (Q->length == 0)   //�ն���
	{
		printf("����һ���ն���\n");
		return FALSE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		Node *p;   
		p = Q->front->next;   //����ͷָ��
		Q->front->next = Q->front->next->next;   //ͷָ������һ����λ
		free(p);   //�ͷ�ԭ����ͷָ��ָ�������
		(Q->length)--;   //����-1
		printf("���ӳɹ�\n");
		return TRUE;
	}
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	if (Q->length == 0)   //�ն���
		printf("����һ���ն���\n");
	if (Q->length > 0)   //�ǿն���
	{
		free(Q->front->next);   //�ͷŵ�һ���ڵ�
		Q->rear = Q->front;   //rear��front��ָ��ͷָ��
		Q->front->next = NULL;
		Q->length = 0;   //����Ϊ0
		printf("��ճɹ�\n");
	}
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void(*foo)(void *q))
{
	for (pr = Q->front->next; pr != NULL; pr = pr->next)
		(*foo)(q);   //�������в��ۼӶ���Ԫ�ظ���
	printf("������й���%d��Ԫ��\n", qnumber);
	length = qnumber;
	qnumber = 0;
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void *q)
{
	q = &length;   //qΪ�ϴα�����*q�ĵ�ַ
	Length = q;
	printf("�ϴ�*q��ֵ��%d\n",*Length);
}
