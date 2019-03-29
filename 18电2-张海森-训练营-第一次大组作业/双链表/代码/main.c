#include <stdio.h>   //����ͷ�ļ�
#include <stdlib.h>
#include "duLinkedList.h"

int JIEDIAN = 0;   //���ڼ����ܽڵ���
ElemType e;    //visit�����Ĳ���
int LOOP=0; //�����ж����޴���һ������
DuLinkedList phead;   //ͷָ�뿽��
int NodeNum = 1;   //��ǰ�ڵ���

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
	int i=1;  //���ڼ�����ѭ��
	ElemType number;   //׼������ڵ��е���
	ElemType value, *e = &value;   //�����޸Ľڵ�ֵ�ĺ���
	DuLNode fNode;   //����ͷ�ڵ�
	DuLinkedList *head=&fNode;   //����һ��*head��Ϊͷָ��
	phead=*head;         //���ڴ�ŵ�ǰ��ͷָ��
	DuLinkedList current;   //����һ������ָ��ǰλ�õ�ָ��
	DuLNode *p,*q;   //����һ�������ڴ����½ڵ��ָ��
	c = getchar();   //����˵�ѡ��
	while (c != 'x')   //����x�˳�
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)
				printf("�Ѿ�������һ������\n");
			if (LOOP == 0)
			{
				InitList_DuL(head);   //��ʼ��������
				(*head)->data = 0;
				phead = *head;
				LOOP = 1;
			}
			break;
			/******************************************************************************************************************/
		case 'b':
		case 'B':
			if (LOOP == 0)
			{
				printf("�㻹û�д�������\n");
			}
			if (LOOP == 1)
			{
				DestroyList_DuL(head);   //���ٸ�����
				LOOP = 0;
			}
			break;
			/******************************************************************************************************************/
		case 'c':
		case 'C':
			if (LOOP == 0)
			{
				printf("�㻹û�д�������\n");
			}
			if (LOOP == 1)
			{
				printf("����Ҫ�ڵڼ����ڵ�֮ǰ����ڵ�:");
				scanf_s("%d", &JIEDIAN);
				if (JIEDIAN <= 0)
					printf("�޷�Ϊ�����\n");
				else if (JIEDIAN > NodeNum)
					printf("����������ڵ�\n");
				else
				{
					p = phead;   //pָ��ǰ���һ���ڵ�
					if (phead->prior == NULL)
					{
						printf("��ǰ��û���κνڵ�\n");
					}
					else
					{
						NodeNum = 1;
						q = (DuLNode *)malloc(sizeof(DuLNode));   //Ϊ�½ڵ�����ڴ�
						printf("����������Ҫ���½ڵ��д�ŵ�ֵ:");
						scanf_s("%d", &number);
						printf("\n");
						q->data = number;   //Ϊ�½ڵ㸳ֵ
						current = (*head)->next;
						while (i != JIEDIAN)   //�ҵ��ýڵ�
						{
							current = current->next;
							i++;
						}
						i = 1;
						p = current;
						InsertBeforeList_DuL(p, q);   //ǰ�庯��
						phead = (*head)->next;   //pheadָ��ͷ�ڵ�
						while (phead != NULL)   //��������
						{
							printf("%d->", phead->data);
							phead = phead->next;
						}
						printf("\n");
						phead = (*head)->next;
						while (phead->next != NULL)
						{
							NodeNum = NodeNum + 1;;
							phead = phead->next;   //phead�ص����һ���ڵ�
						}
					}
				}
			}
			break;
			/********************************************************************************************************************/
		case 'd':
		case 'D':
			if (LOOP == 0)
			{
				printf("�㻹û�д�������\n");
			}
			if (LOOP == 1)
			{
				p = phead;   //pheadָ�����һ���ڵ�
				NodeNum = 1;
				q = (DuLNode *)malloc(sizeof(DuLNode));   //Ϊ�½ڵ�����ڴ�
				printf("����������Ҫ���½ڵ��д�ŵ�ֵ:");
				scanf_s("%d", &number);
				printf("\n");
				q->data = number;   //Ϊ�½ڵ㸳ֵ
				InsertAfterList_DuL(p, q);   //��庯��
				phead = (*head)->next;
				while (phead != NULL)   //��������
				{
					printf("%d->", phead->data);
					phead = phead->next;
				}
				phead = (*head)->next;
				while (phead->next != NULL)
				{
					NodeNum = NodeNum + 1;;
					phead = phead->next;   //pheadָ��ǰ���һ���ڵ�
				}
				printf("\n");
			}
			break;
			/******************************************************************************************************************/
		case 'e':
		case 'E':
			if (LOOP == 0)
			{
				printf("�㻹û�д�������\n");
			}
			if (LOOP == 1)
			{
				printf("����Ҫɾ���ڼ����ڵ�ĺ���һ���ڵ�:");
				scanf_s("%d", &JIEDIAN);   //��Ҫɾ���ڼ����ڵ�
				if (JIEDIAN <= 0)
					printf("�޷�Ϊ�����\n");
				else if (JIEDIAN > NodeNum)
				{
					printf("����������ڵ�\n");
				}
				else
				{
					NodeNum = 1;
					current = (*head)->next;
					while (i != JIEDIAN)   //�ҵ��ýڵ�
					{
						current = current->next;
						i++;
					}
					i = 1;
					printf("���뽫����ڵ����ֵ��Ϊ:");
					scanf_s("%d", &(*e));   //��������Ҫ�����Ǹ��ڵ��ֵ
					DeleteList_DuL(current, e);   //ɾ�ڵ㺯��
					phead = (*head)->next;
					while (phead != NULL)   //��������
					{
						printf("%d->", phead->data);
						phead = phead->next;
					}
					printf("\n");
					phead = (*head)->next;
					while (phead->next != NULL)
					{
						NodeNum++;
						phead = phead->next;   //pheadָ�����һ���ڵ�
					}
				}
			}
			break;
			/******************************************************************************************************************/
		case 'f':
		case 'F':
			if (LOOP == 0)
			{
				printf("�㻹û�д�������\n");
			}
			if (LOOP == 1)
			{
				TraverseList_DuL(phead, visit);   //����������visit�����ĺ���
			}
			break;
			/******************************************************************************************************************/
		case 'x':
		case 'X': 
			break;   //�˳���������
			/******************************************************************************************************************/
		case 'y':
		case 'Y':
			menu();   //��ʾ�˵�
			break;
			/******************************************************************************************************************/
		default:printf("��������ȷ�Ĳ˵�ѡ�\n");   //������ʾ
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
	printf("\t\t____________________________________________________\n");
	printf("\t\t|                                                  |\n");
	printf("\t\t|  a.��ʼ��һ������������һ��ͷ�ڵ㣩            |\n");
	printf("\t\t|  b.����һ������                                  |\n");
	printf("\t\t|  c.���ڵ�q���뵽����ڵ�pǰ                      |\n");
	printf("\t\t|  d.���ڵ�q���뵽��ǰ�ڵ�p��                      |\n");
	printf("\t\t|  e.ɾ���ڵ�p֮����Ǹ��ڵ㣬����ֵ���ڵ�p        |\n");
	printf("\t\t|  f.������������visit����(��ʾ���ü���visit����)|\n");
	printf("\t\t|  x.�˳���������                                  |\n");
	printf("\t\t|  y.�鿴�˵�ѡ��                                  |\n");
	printf("\t\t|__________________________________________________|\n");
	printf("                                                        \n");
}
