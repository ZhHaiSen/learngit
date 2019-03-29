#include <stdio.h>   //����ͷ�ļ�
#include <stdlib.h>
#include "linkedList.h"

int JIEDIAN = 0;   //���ڼ�����ѭ��
ElemType e = 0;    //visit�����Ĳ���
ElemType want;   //����Ѱ��dataΪ���ֵ�Ľڵ�
int i;   //���ڼ���

int main()   //main����
{
	void choose();
	void menu();
	void print();
	menu();   //��ӡ�˵�
	print();   //��ӡ��ʾ
	choose();   //ѡ��˵�ѡ��
	return 0;
}

void choose()
{
	void menu();   //�����˵�����
	void print();   //������ʾ����
	void search(ElemType e);   //��������
	void(*visit)(ElemType e);   //����(*visit)����
	visit = search;    //visitָ��search����
	char c;   //�˵�ѡ��
	ElemType number;   //׼������ڵ��е���
	LNode fNode;   //����ͷ�ڵ�
	LinkedList *head = &fNode;   //����һ��*head��Ϊͷָ��
	LinkedList phead = *head;         //���ڴ�ŵ�ǰ��ͷָ��
	ElemType value, *e = &value;   //�����޸Ľڵ�ֵ�ĺ���
	LNode *p, *q;   //����һ�������ڴ����½ڵ��ָ��
	LinkedList current;   //����һ������ָ��ǰλ�õ�ָ��
	c = getchar();   //����˵�ѡ��
	while (c != 'x')   //����x�˳�
	{
		switch (c)
		{
		case 'a':
		case 'A':InitList(head);
			phead = head;
			break;
		case 'b':
		case 'B':DestroyList(head);
			break;
		case 'c':
		case 'C':
			p = phead;   //pָ��ǰ���һ���ڵ�
			q = (LNode *)malloc(sizeof(LNode));   //Ϊ�½ڵ�����ڴ�
			printf("����������Ҫ���½ڵ��д�ŵ�ֵ:");
			scanf_s("%d", &number);
			printf("\n");
			q->data = number;   //Ϊ�½ڵ㸳ֵ
			InsertList(p, q);    //���뺯��
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'd':
		case 'D':printf("����Ҫɾ���ڼ����ڵ�ĺ���һ���ڵ�:");
			scanf_s("%d", &JIEDIAN);   //��Ҫɾ���ڼ����ڵ�
			current = (*head)->next;
			while (i != JIEDIAN)   //�ҵ��ýڵ�
			{
				current = current->next;
				i++;
			}
			i = 1;
			printf("���뽫����ڵ����ֵ��Ϊ:");
			scanf_s("%d", &(*e));   //��������Ҫ�����Ǹ��ڵ��ֵ
			DeleteList(current, e);   //ɾ�ڵ㺯��
			phead = (*head)->next;
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //pheadָ�����һ���ڵ�
			break;
		case 'e':
		case 'E':TraverseList(phead, visit);   //ִ�к���������visit����
			break;
		case 'f':
		case 'F':p = phead;   //pָ��ǰ���һ���ڵ�
			printf("����Ҫ�ҵ�ֵΪ���Ľڵ�");
			scanf_s("%d", &want);   //������Ҫ��ѯ�Ƿ���ڽڵ��ֵΪ����ֵ��ֵ
			SearchList(((*head)->next), want);   //ִ����������
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'g':
		case 'G':ReverseList(head);   //��ת
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'h':
		case 'H':IsLoopList((*head)->next);   //�ɻ�
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'i':
		case 'I':(*head)->next=ReverseEvenList(head);   //ż����ת
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'j':
		case 'J':FindMidNode(phead);   //���м�ڵ�
			printf("�м�ڵ�:");
			printf("����ֵ��%d", phead->data);
			phead = (*head)->next;   //pheadָ��ͷ�ڵ�
			while (phead != NULL)   //��������
			{
				printf("%d->", phead->data);
				phead = phead->next;
			}
			printf("\n");
			phead = (*head)->next;
			while (phead->next != NULL)
				phead = phead->next;   //phead�ص����һ���ڵ�
			break;
		case 'x':
		case 'X': break;   //�˳�����
		case 'y':
		case 'Y':menu(); break;   //�˵�����
		default:printf("��������ȷ�Ĳ˵�ѡ�\n");   //������ʾ
		}
		char d = getchar();
		print();
		c = getchar();
	}
}

void print()   //��ʾ����
{
	printf("��������Ӧ�˵�ѡ��ǰ��ĸ�����س�:");
}

void menu()   //��ӡ�˵�����
{
	printf("\t\t______________________________________________\n");
	printf("\t\t|                                            |\n");
	printf("\t\t|  a.��ʼ��һ������������һ��ͷ�ڵ㣩      |\n");
	printf("\t\t|  b.����һ������                            |\n");
	printf("\t\t|  c.���ڵ�p���뵽�ڵ�q��                    |\n");
	printf("\t\t|  d.ɾ���ڵ�p֮����Ǹ��ڵ㣬����ֵ���ڵ�p  |\n");
	printf("\t\t|  e.������������visit����                 |\n");
	printf("\t\t|  f.��������ֵ�ҵ�������Ӧ�Ľڵ�            |\n");
	printf("\t\t|  g.��ת����                                |\n");
	printf("\t\t|  h.�ж������Ƿ�Ϊһ����������              |\n");
	printf("\t\t|  i.��ת������ֵΪż���Ľڵ�                |\n");
	printf("\t\t|  j.�ҵ�������м�ڵ�                      |\n");
	printf("\t\t|  x.�˳���������                            |\n");
	printf("\t\t|  y.�鿴�˵�ѡ��                            |\n");
	printf("\t\t|____________________________________________|\n");
	printf("                                                  \n");
}