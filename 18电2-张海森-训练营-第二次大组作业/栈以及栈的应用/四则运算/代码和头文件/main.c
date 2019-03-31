#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

LinkStack *S;   //����ջ��Ϣ�Ľڵ�
ElemType StackTop, *e = &StackTop;   //ջ��Ԫ��
ElemType topdata, *Tdata = &topdata;   //�õ�ջ��Ԫ�ز���ջ��Ԫ�س�ջ
char current = 0, expression[100];   //current�������뵱ǰ�ַ���expression�����ݴ浱ǰ�ַ�����c�����˳�����,d���������س�
int i, j;   //i���ڽ��ַ��������ݴ�������,j������׺���ʽת��׺���ʽ
float first, second, sum = 0;   //first���ڴ��ջ����һ�����֣�second���ڴ��ջ���ڶ������֣�sum���ڴ��������

int main()
{
	void middle_toward_behind(char *x);
	float behind_toward_sum(char *x);
	S = (LinkStack *)malloc(sizeof(LinkStack));   //Ϊ����ջ��Ϣ�Ľڵ�����ڴ�
	char c;   //����˵�ѡ��
	printf("\t\t\t���س��������㣬��x�˳�����\n");
	while (1)   
	{
		printf("�����������ʽ�����س�:");
		for (i=0; current != '\n';i++)   //ѭ�������ַ���
		{
			scanf_s("%c", &current);
			expression[i] = current;
		}
		current = 0;   //���¸�ֵ���ٴν���ѭ��
		middle_toward_behind(expression[100]);   //��׺����׺
		sum = behind_toward_sum(expression[100]);   //��׺����
		for (j = 0; expression[j] != '\0'; j++)   //�����׺���ʽ
			printf("%c", expression[j]);
		printf("=%f", sum);   //������
		printf("\n");
		c = getchar();   //�����������
		if (c == 'x') break;
	}
	return 0;
}

void middle_toward_behind(char *x)   //��׺���׺
{
	initLStack(S);   //�½���ջ
	for (i = 0, j = 0; expression[i] != '\n'; i++)   //����ÿһ���ַ�
	{
		if (expression[i] >= 48 && expression[i] <= 57)   //����
		{
			expression[j] = expression[i];   //ֱ�����
			j++;
		}
		if (expression[i] == 40)  //��
		{
			pushLStack(S, expression[i]);   //��ջ
		}
		if (expression[i] == 43 || expression[i] == 45 || expression[i] == 42 || expression[i] == 47)   //+  -  *  /
		{
			if (S->count > 0)   //�ǿ�ջ
			{
				if (expression[i] == 43 || expression[i] == 45)   //+  -
				{
					getTopLStack(S, e);
					if (*e == 40)   //(
						pushLStack(S, expression[i]);   //ѹջ
					if (*e == 43 || *e == 45 || *e == 42 || *e == 47)   //+  -  *  /
					{
						for (; *e != 40 && S->count > 0;)   //�ȸ���������ȼ���Ļ���ȵĶ���ջ
						{
							popLStack(S, Tdata);
							expression[j] = *Tdata;
							j++;
							if (S->count > 0)
							{
								getTopLStack(S, e);
							}
						}
						pushLStack(S, expression[i]);   //�������ѹջ
					}
				}
				if (expression[i] == 42 || expression[i] == 47)   //*  /
				{
					getTopLStack(S, e);
					if (*e == 40 || *e == 43 || *e == 45)   //(  +  -
						pushLStack(S, expression[i]);   //ѹջ
					if (*e == 42 || *e == 47)   //*  /
					{
						for (; *e == 40 || *e == 43 || *e == 45 || S->count == 0;)   //�ȸ���������ȼ���Ļ�����ȵĳ�ջ
						{
							popLStack(S, Tdata);
							expression[j] = *Tdata;
							j++;
							getTopLStack(S, e);
						}
						pushLStack(S, expression[i]);   //���������ջ
					}
				}
			}
			if (S->count == 0)   //��ջ
				pushLStack(S, expression[i]);   //ֱ��ѹջ
		}
		if (expression[i] == 41)   //��
		{
			getTopLStack(S, e);
			while (*e != 40)   //ֱ�����������ţ������ջ
			{
				popLStack(S, Tdata);
				expression[j] = *Tdata;
				j++;
				getTopLStack(S, e);
			}
			popLStack(S, Tdata);
		}
	}
	if (S->count > 0)   //���������
	{
		for (; S->count != 0;)   //ȫ����ջ
		{
			popLStack(S, Tdata);
			expression[j] = *Tdata;
			j++;
		}
	}
	expression[j] = '\0';   //���ñ�־λ
	destroyLStack(S);    //����ջ
}

float behind_toward_sum(char *x)   //��׺����
{
	initLStack(S);   //��ʼ��ջ
	for (j = 0; expression[j] != '\0'; j++)   //������ɨ��
	{
		if (expression[j] >= 48 && expression[j] <= 57)   //��ֵ
			pushLStack(S, expression[j] - 48);   //����ֵ��������ʽѹջ
		if (expression[j] == 43)   //+
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = first + second;   //ջ��������Ԫ�����Ϊһ����
			pushLStack(S, sum);   //����ѹջ
		}
		if (expression[j] == 45)   //-
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = second - first;   //ջ���ڶ���Ԫ�ؼ���һ��Ԫ��Ϊһ����
			pushLStack(S, sum);   //����ѹջ
		}
		if (expression[j] == 42)   //*
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = first * second;   //ջ������Ԫ�����Ϊһ����
			pushLStack(S, sum);   //����ѹջ
		}
		if (expression[j] == 47)   //    /
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = second / first;//ջ���ڶ��������Ե�һ����Ϊһ����
			pushLStack(S, sum);   //����ѹջ
		}
	}
	popLStack(S, Tdata);   //���ս����ջ
	sum = *Tdata;   //sum=���ս��
	destroyLStack(S);   //����ջ
	return sum;
}