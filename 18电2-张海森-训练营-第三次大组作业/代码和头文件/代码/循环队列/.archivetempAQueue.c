#include <stdio.h>
#include <stdlib.h>
#include ".archivetempAQueue.h"

extern record[MAXQUEUE];   //��¼״̬
extern count;   //���ڼƵڼ���
extern i;
extern current;   //ѭ��
int qnumber = 0;   
q = &qnumber;   //*q
int length, *Length;   //���г���
void visit(void *q)   //��������
{
	qnumber++;
}
foo = &visit;

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q)
{
	Q->front = -1;
	Q->rear = -1;   //ָ�븳ֵ
	Q->length = 0;   //����Ϊ0
	printf("�Ѿ�Ϊ���ʼ��һ��ѭ������\n");
}

/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	printf("�Ѿ��ɹ�Ϊ�����ٶ���\n");
}

/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : �������Ƿ�����
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	if (Q->length == MAXQUEUE)   //������
	{
		printf("��������\n");
		return TRUE;
	}
	if (Q->length < MAXQUEUE)   //��������
	{
		printf("����δ��\n");
		return FALSE;
	}
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	if (Q->length == 0)   //�ն���
	{
		printf("����Ϊ��\n");
		return TRUE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		printf("���в���\n");
		return FALSE;
	}
}

/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q ����ָ��Q�����Ԫ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	if (Q->length == 0)   //�ն���
	{
		printf("û�ж�ͷԪ��\n");
		return FALSE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		if (record[Q->front] == 1)   //char
		{
			char *p = Q->data[Q->front];
			printf("��ͷԪ��Ϊ%c\n", *p);
		}
		if (record[Q->front] == 2)   //int
		{
			int *p = Q->data[Q->front];
			printf("��ͷԪ��Ϊ%d\n", *p);
		}
		if (record[Q->front] == 3)   //float
		{
			float *p = Q->data[Q->front];
			printf("��ͷԪ��Ϊ%f\n", *p);
		}
	}
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : ���г���count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	if (Q->length == 0)   //�ն���
	{
		printf("����һ���ն���\n");
		return FALSE;
	}
	if (Q->length > 0)   //�ǿն���
	{
		printf("������еĳ���Ϊ%d", Q->length);
		return TRUE;
	}
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ����˻�Ϊ��
 */
Status EnAQueue(AQueue *Q, void *data)
{
	if (Q->length == MAXQUEUE)   //������
	{
		printf("��������\n");
		return FALSE;
	}
	else if(Q->length==0)   //�ն���
	{
		(Q->front)++;
		(Q->rear)++;   //front��rearͬʱΪһ����
		Q->data[Q->front] = data;   //��ֵ
		printf("��ӳɹ�\n");
		(Q->length)++;
		return TRUE;
	}
	else
	{
		(Q->rear)++;    //βԪ������
		if (Q->rear == MAXQUEUE)   //��ͷ����ͷѭ��
			Q->rear = 0;
		Q->data[Q->rear] = data;   //��ֵ
		(Q->length)++;   //����+1
		printf("��ӳɹ�\n");
		return TRUE;
	}
}

/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	if (Q->length == 0)   //�ն���
	{
		printf("�Ѿ���һ���ն���\n");
		return FALSE;
	}
	if (Q->length == 1)   //ֻ��һ��Ԫ��
	{
		Q->front = -1;
		Q->rear = -1;   //front��rearͬʱΪ-1���������κ���ֵ
		(Q->length)--;   //����-1
		printf("���ӳɹ�\n");
		return TRUE;
	}
	if (Q->length > 1)
	{
		(Q->front)++;   //ͷԪ������
		if (Q->front == MAXQUEUE)   //front����ԭ����β���ͷ����
			Q->front = 0;
		(Q->length)--;   //����-1
		printf("���ӳɹ�\n");
		return TRUE;
	}
}

/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	if (Q->length == 0)   //�ն���
		printf("����һ���ն���\n");
	if (Q->length > 0)   //�ǿն���
	{
		Q->length = 0;   //����Ϊ0
		Q->rear = -1;
		Q->front = -1;   //frong��rear���������κ���ֵ
		printf("�Ѿ�Ϊ����ն���\n");
	}
}

/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void(*foo)(void *q))
{
	for (i = 0, current = Q->front; i < Q->length; i++, current++)
		(*foo)(q);   //��������
	printf("������й���%d��Ԫ��\n", qnumber);
	length = qnumber;
	qnumber = 0;
	return TRUE;
}

/**
 *  @name        : void APrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 *  @notice      : None
 */
void APrint(void *q)
{
	q = &length; 
	Length = q;   //*q
	printf("�ϴ�*q��ֵ��%d\n", *Length);
}
