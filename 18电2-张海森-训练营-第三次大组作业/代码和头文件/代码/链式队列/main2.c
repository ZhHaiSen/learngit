#include <stdio.h>
#include <stdlib.h>
#include ".archivetempLQueue.h"

int LOOP = 0;   //��¼��ǰ���޳�ʼ������
LQueue *Q;   //�������е�ͷָ�롢βָ��ͳ���
int E; 
void *e = &E;   //�鿴��ͷԪ��
int queuelength;   //�鿴���г���
void *data;   //���Ԫ��
Node *p;
int *P;   //���������������
void(*foo)(void *q);   //��������
void *q;   //��������

int main()
{
	void choose();
	void menu();
	void print();
	Q = (LQueue *)malloc(sizeof(LQueue));   //Ϊ�洢������Ϣ�Ľڵ����ռ�
	menu();    //�˵�
	print();    //��ʾ
	choose();   //ѡ��
	return 0;
}

void choose()
{
	void menu(); 
	void print();  
	char c = getchar();  
	while (c != 'x')
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)   //�Ѿ���ʼ��������
				printf("�Ѿ���ʼ����һ������\n");
			if (LOOP == 0)   //��û�г�ʼ��������
			{
				InitLQueue(Q);   //��ʼ��
				LOOP = 1;   //��ʼ��������
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				DestoryLQueue(Q);   //����
				LOOP = 0;   //�����ٶ���
			}
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				IsEmptyLQueue(Q);   //�п�
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				GetHeadLQueue(Q, e);   //�õ���ͷԪ��
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				queuelength = LengthLQueue(Q);   //�ⳤ��
			break;
		case 'f':
		case 'F':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				int *joindata;
				joindata = (int *)malloc(sizeof(int));   //��*data������ϵ
				printf("����������Ҫ��ӵ�����:");
				scanf_s("%d", joindata);   //������Ҫ��ֵ
				EnLQueue(Q, joindata);   //���
				for (p = Q->front->next; p != NULL; p = p->next)   //�����������ȫ��Ԫ��
				{
					P = p->data;
					printf("%d->", *P);
				}
				printf("\n");
			}
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				DeLQueue(Q);   //����
				if (Q->length > 0)
				{
					for (p = Q->front->next; p != NULL; p = p->next)   //�����������ȫ��Ԫ��
					{
						P = p->data;
						printf("%d->", *P);
					}
					printf("\n");
				}
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				ClearLQueue(Q);   //���
			break;
		case 'i':
		case 'I':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)   //��ʼ��������
				TraverseLQueue(Q, foo);   //��������
			break;
		case 'j':
		case 'J':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)   //��ʼ��������
				LPrint(q);   //��������
			break;
		case 'x':
		case 'X':
			break;   
		case 'y':
		case 'Y':
			menu(); 
			break;
		default:printf("��������ȷ�Ĳ˵�ѡ�\n");
		}
		char d = getchar();
		print();
		c = getchar();
	}
}

void print()   //��ӡ��ص���ʾ
{
	printf("��������Ӧ�˵�ѡ��ǰ��ĸ�����س�:");
}

void menu()   //�˵�ѡ��Ĵ�ӡ����
{
	printf("\t\t\t___________________________________\n");
	printf("\t\t\t|                                 |\n");
	printf("\t\t\t|  a.��ʼ������                   |\n");
	printf("\t\t\t|  b.���ٶ���                     |\n");
	printf("\t\t\t|  c.�п�                         |\n");
	printf("\t\t\t|  d.�鿴��ͷԪ��                 |\n");
	printf("\t\t\t|  e.�鿴���г���                 |\n");
	printf("\t\t\t|  f.���                         |\n");
	printf("\t\t\t|  g.����                         |\n");
	printf("\t\t\t|  h.��ն���                     |\n");
	printf("\t\t\t|  i.��������                     |\n");
	printf("\t\t\t|  j.����                         |\n");
	printf("\t\t\t|  x.�˳���������                 |\n");
	printf("\t\t\t|  y.�鿴�˵�ѡ��                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}