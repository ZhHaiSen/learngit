#include <stdio.h>
#include <stdlib.h>
#include ".archivetempAQueue.h"

int LOOP = 0;   //��־λ
int record[MAXQUEUE] = { 0 };   //״̬��¼����
int count=-1;   //�洢��ӦԪ�ص����͵�˳��
AQueue *Q;   //Q
char form[100];   //�������Ԫ��
int i;
int j;
int figure;   //�ܹ�λ��
int redix_point;   //С��������λ��
int current;   //�������������ֵ
char d;
void *e;   //��ͷԪ��
void *q;  //��������ָ��
void(*foo)(void *q);   //��������

int main()
{
	void choose();
	void menu();
	void print();
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
				Q = (AQueue *)malloc(sizeof(AQueue));   //ΪQ���ٿռ�
				InitAQueue(Q);   //��ʼ��
				LOOP = 1;
			}
			break;
		case 'b':
		case 'B':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				free(Q);   //�ͷ�Q������ķ�Χ
				DestoryAQueue(Q);   //����
				LOOP = 0;
			}
			break;
		case 'c':
		case 'C':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				IsFullAQueue(Q);   //����
			break;
		case 'd':
		case 'D':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				IsEmptyAQueue(Q);   //�п�
			break;
		case 'e':
		case 'E':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				GetHeadAQueue(Q, e);   //�õ���ͷԪ��
			break;
		case 'f':
		case 'F':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
				LengthAQueue(Q);   //�õ����г���
			break;
		case 'g':
		case 'G':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				printf("����������Ҫ��ӵ���ĸ������:");
				for (i = 0; ; i++)
				{
					scanf_s("%c", &form[i], 1);
					if (form[i] == '\n') break;
				}   //�����������ĸ����ֵת�����ַ���
				figure = i;   //λ��
				count =(Q->rear)+1;		   //count��ǰ��¼		
				for (i = 0; form[i] != '\n'; i++)   //�鿴������ĸ��С����
				{
					record[count] = 2;   //����
					if (form[i] >= 65 && form[i] <= 122)
						record[count] = 1;   //�ַ���
					if (form[i] == 46)   //������
					{
						redix_point = i;
						record[count] = 3;
					}
					if (form[i] == 46) break;
				}
				i = 0;
				if (record[count] == 1)   //�ַ���
				{
					char *p;
					p = (char *)malloc(sizeof(char));
					*p = form[i];
					EnAQueue(Q, p);   //���
				}
				if (record[count] == 2)   //����
				{
					int *sum;
					sum = (int *)malloc(sizeof(int));
					*sum = 0;
					int save;
					for (i = 0; i < figure - 1; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < figure - i - 1; j++)
						{
							save = save * 10;
						}
						*sum = *sum + save;
					}
					save = form[i] - 48;
					*sum = *sum + save;   //ת��Ϊʮ����
					EnAQueue(Q, sum);   //���
				}
				if (record[count] == 3)   //������
				{
					float *sum;
					sum = (float *)malloc(sizeof(float));
					*sum = 0;
					float save;
					for (i = 0; i < redix_point - 1; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < redix_point - i - 1; j++)
						{
							save = save * 10;
						}
						*sum = *sum + save;
					}
					save = form[i] - 48;
					*sum = *sum + save;
					for (i = redix_point + 1; i < figure; i++)
					{
						save = form[i] - 48;
						for (j = 0; j < i - redix_point; j++)
						{
							save = save / 10;
						}
						*sum = *sum + save;
					}   //ת��Ϊʮ����
					EnAQueue(Q, sum);   //���
				}
				for (i = 0,current=Q->front; i < Q->length; i++,current++)
				{
					if (current == MAXQUEUE)   //�������һ������ͷ���
						current = 0;
					if (record[current] == 1)   //�ַ���
					{
						char *number = (char *)Q->data[current];
						printf("%c->", *number);
					}
					if (record[current] == 2)   //����
					{
						int *number = (int *)Q->data[current];
						printf("%d->", *number);
					}
					if (record[current] == 3)   //������
					{
						float *number = (float *)Q->data[current];
						printf("%f->", *number);
					}
				}
				printf("\n");
			}
			break;
		case 'h':
		case 'H':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)    //��ʼ��������
			{
				DeAQueue(Q);   //����
				for (i = 0, current = Q->front; i < Q->length; i++, current++)
				{
					if (current == MAXQUEUE)   //Խ�����һ������ͷ���
						current = 0;
					if (record[current] == 1)   //�ַ���
					{
						char *p = Q->data[current];
						printf("%c->", *p);
					}
					if (record[current] == 2)   //����
					{
						int *p = Q->data[current];
						printf("%d->", *p);
					}
					if (record[current] == 3)   //������
					{
						float *p = Q->data[current];
						printf("%f->", *p);
					}
				}
				printf("\n");
			}
			break;
		case 'i':
		case 'I':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)   //��ʼ��������
				ClearAQueue(Q);   //��ն���
			break;
		case 'j':
		case 'J':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)   //��ʼ��������
				TraverseAQueue(Q, foo);   //��������
			break;
		case 'k':
		case 'K':
			if (LOOP == 0)   //���в�����
				printf("û�ж���\n");
			if (LOOP == 1)
				APrint(q);   //��������
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
		d = getchar();
		print();
		c = getchar();
		d = getchar();
	}
}

void print()   //��ӡ��ص���ʾ
{
	printf("��������Ӧ�˵�ѡ��ǰ��ĸ�����س�:");
}

void menu()   //�˵�ѡ��Ĵ�ӡ����
{
	printf("\t\t\t ___________________________________\n");
	printf("\t\t\t|                                  |\n");
	printf("\t\t\t|   a.��ʼ������                   |\n");
	printf("\t\t\t|   b.���ٶ���                     |\n");
	printf("\t\t\t|   c.����                         |\n");
	printf("\t\t\t|   d.�п�                         |\n");
	printf("\t\t\t|   e.�鿴��ͷԪ��                 |\n");
	printf("\t\t\t|   f.�鿴���г���                 |\n");
	printf("\t\t\t|   g.���                         |\n");
	printf("\t\t\t|   h.����                         |\n");
	printf("\t\t\t|   i.��ն���                     |\n");
	printf("\t\t\t|   j.��������                     |\n");
	printf("\t\t\t|   k.����                         |\n");
	printf("\t\t\t|   x.�˳���������                 |\n");
	printf("\t\t\t|   y.�鿴�˵�ѡ��                 |\n");
	printf("\t\t\t|   ÿ���һ��������Ҫ��һ�λس�   |\n");
	printf("\t\t\t|__________________________________|\n");
	printf("                                          \n");
}