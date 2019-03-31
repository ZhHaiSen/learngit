#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SqStack.h"

int LOOP = 0;   //�ж����޴�����ջ
SqStack stack;   //����һ���½ڵ�
SqStack *S = &stack;       //����һ��ָ��ջ��ָ��
int sizes;   //ջ�ĳ�ʼ����С
ElemType StackTop, *e = &StackTop;   //���ջ��Ԫ��
int StackLength;   //���ջ����
ElemType data = 0, Edata = 0;
ElemType *edata = &Edata;   //����ջ������
int i;   //���ڼ����ͱ�ʾջ������

int main()
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
				printf("����Ҫ����һ������˳��ջ:");
				scanf_s("%d", &sizes);   //����size
				if (sizes <= 0)
					printf("�޷�Ϊ�㴴��������ջ\n");
				else
				{
					initStack(S, sizes);   //��ʼ��ջ
					LOOP = 1;
				}
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				isEmptyStack(S);   //�п�
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				getTopStack(S, e);   //�õ�ջ��Ԫ��
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				clearStack(S);   //���ջ
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //������
				printf("��ǰû��ջ\n");
			if (LOOP == 1)
			{
				destroyStack(S);   //����ջ
				LOOP = 0;
			}
		case 'f':
		case 'F':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
				stackLength(S, StackLength);   //���ջ����
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
			{
				printf("����������Ҫѹ��ջ�е�����:");   //����ջ������
				scanf_s("%d", &data);
				pushStack(S, data);   //��ջ
				printf("��ǰջ��Ԫ��:");
				for (i = 0; i <= S->top; i++)   //�������ջ��Ԫ��
					printf("%d->", S->elem[i]);
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)
				printf("��û�д�����ջ\n");
			if (LOOP == 1)
			{
				popStack(S, edata);   //��ջ
				printf("��ǰջ��Ԫ��:");
				for (i = 0; i <= S->top; i++)   //�������ջ��Ԫ��
					printf("%d->", S->elem[i]);
				if (S->top == -1)   //����Ԫ�ض���ջ
					printf("��ǰΪ��ջ");
				printf("\n");
			}
			break;
		case 'x':
		case 'X':
			break;   //�˳�����
		case 'y':
		case 'Y':
			menu();   //��ʾ�˵�
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
	printf("\t\t\t|  f.���ջ                       |\n");
	printf("\t\t\t|  g.��ջ                         |\n");
	printf("\t\t\t|  h.��ջ                         |\n");
	printf("\t\t\t|  x.�˳���������                 |\n");
	printf("\t\t\t|  y.�鿴�˵�ѡ��                 |\n");
	printf("\t\t\t|_________________________________|\n");
	printf("                                         \n");
}