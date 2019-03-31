#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int LOOP = 0;   //�ж���û�д�����ջ
LinkStack *S;    //�µ�ջ��Ϣ�ڵ�
ElemType StackTop, *e = &StackTop;   //���ջ��Ԫ��
int StackLength,*length=&StackLength;   //���ջ����
ElemType data = 0, Edata = 0;
ElemType *edata = &Edata;   //����ջ������
LinkStack scurrent;   //ջ��Ϣ�ڵ�Ŀ���

int main()
{
	void choose();
	void menu();
	void print();
	menu();   //��ӡ�˵�
	print();   //��ӡ��ʾ
	S = (LinkStack *)malloc(sizeof(LinkStack));   //Ϊջ��Ϣ�Ľڵ����ռ�
	choose();   //ѡ��˵�ѡ��
	return 0;
}

void choose()
{
	void menu();   //�����˵�����
	void print();   //������ʾ����
	char c = getchar();   //����˵�ѡ��
	while (c != 'x')   //����x�˳�
	{
		switch (c)
		{
		case 'a':
		case 'A':
			if (LOOP == 1)
				printf("�Ѿ�������һ����ջ\n");
			if (LOOP == 0)
			{
				initLStack(S);   //��ʼ��ջ
				LOOP = 1;
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				isEmptyLStack(S);   //�п�
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				getTopLStack(S, e);   //�õ�ջ��Ԫ��
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				clearLStack(S);   //���ջ
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)
				printf("��ǰû��ջ\n");
			if (LOOP == 1)
			{
				destroyLStack(S);  //����ջ
				LOOP = 0;
			}
		case 'f':
		case 'F':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				LStackLength(S, length);   //���ջ�ĳ���
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
			{
				printf("����������Ҫѹ��ջ�е�����:");
				scanf_s("%d", &data);   //������ջ����
				pushLStack(S, data);   //��ջ
				printf("��ǰջ��Ԫ��:");
				for (scurrent = *S; scurrent.top->next != NULL; scurrent.top = scurrent.top->next)   //���ջ�е�ǰԪ��
					printf("%d->", scurrent.top->data);
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
			{
				popLStack(S, edata);   //��ջ
				printf("��ǰջ��Ԫ��:");
				for (scurrent = *S; scurrent.top->next != NULL; scurrent.top = scurrent.top->next)   //���ջ�е�ǰԪ��
					printf("%d->", scurrent.top->data);
				printf("\n");
				if (S->count==0)   //��ջ
					printf("��ǰΪ��ջ");
				printf("\n");
			}
			break;
		case 'x':
		case 'X':
			break;   //�˳�����
		case 'y':
		case 'Y':
			menu();   //�˵�ѡ��
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
	printf("\t\t\t|  a.��ʼ��ջ                     |\n");
	printf("\t\t\t|  b.�ж�ջ�Ƿ�Ϊ��               |\n");
	printf("\t\t\t|  c.�õ�ջ��Ԫ��                 |\n");
	printf("\t\t\t|  d.���ջ                       |\n");
	printf("\t\t\t|  e.����ջ                       |\n");
	printf("\t\t\t|  f.���ջ����                   |\n");
	printf("\t\t\t|  g.��ջ                         |\n");
	printf("\t\t\t|  h.��ջ                         |\n");
	printf("\t\t\t|  x.�˳���������                 |\n");
	printf("\t\t\t|  y.�鿴�˵�ѡ��                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}