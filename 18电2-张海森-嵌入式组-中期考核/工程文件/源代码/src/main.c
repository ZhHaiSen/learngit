#include <stdio.h>
#include "library.h"

Book *L;   //�鱾
Borrow *Q;   //������
FILE *fp1, *fp2;   //�鼮�������ߡ�log

int main()
{
	Init();   //��ʼ��
	choose();   //��Ӧѡ���ͬ����
	Finish();   //��β
	return 0;
}

/*���������ϢΪѡ�����ͬ�Ĺ���*/
void choose()
{
	char c;
	c = ROM();
	while (c != 'x')
	{
		switch (c)
		{
		case '1':
			inrepository(L);   //�ɱ����
			break;
		case '2':
			outrepository(L);   //�������
			break;
		case '3':
			bookInfor();   //�鼮��Ϣ
			break;
		case '4':
			bookborrow(L);   //����
			break;
		case '5':
			bookreturn(L);   //�黹
			break;
		case '6':
			reservebook(L);   //ԤԼ����
			break;
		default:
			warn();   //�Ƿ�����
		}
		c = ROM();
	}
}

/*��ʼ��һ���洢�鼮��Ϣ������*/
void Init()
{
	int finish;   //�ж��Ƿ�����ĵ���β
	int i = 0;   //�ڸտ�ʼ���ĵ���ʱ��ص��ĵ���ͷ
	errno_t err;   //���ļ�
	Book *l;   //�õ��µ��鼮�ڵ�
	Borrow *q;   //�õ��µĽ����߽ڵ�
	L = (Book *)malloc(sizeof(Book));   //�鱾
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	if (L == NULL)
		printf("�ڴ�ռ䲻��!");   //�ڴ治��
	InitBook(L);   //��ʼ���洢�鼮��Ϣ������
	err = fopen_s(&fp1, "library", "r+");   //���鼮���������ĵ�
	if (err != 0)
		printf("Can't open \"library\" file.");   //��ʧ��
	err = fopen_s(&fp2, "log", "a");   //��log�ĵ�
	if (err != 0)
		printf("Can't open \"log\" file.");   //��ʧ��
	finish = getc(fp1);   //�ж��Ƿ�����ĵ���β
	while (finish != EOF)
	{
		int count;   //����Ľ���������
		Borrow *p;   //�õ��µĿ��Բ���Ľ����߽ڵ�
		if (i == 0) rewind(fp1);
		if (getc(fp1) == '$')   //�µ��鼮�ڵ㿪ʼ�ı�־
		{
			fscanf_s(fp1, "%s", l->ISBN, 50 * sizeof(char));
			fscanf_s(fp1, "%s", l->name, 100 * sizeof(char));
			fscanf_s(fp1, "%s", l->author, 100 * sizeof(char));
			fscanf_s(fp1, "%d", &(l->able_borrow), sizeof(int));
			fscanf_s(fp1, "%d", &(l->current_reserves), sizeof(int));
			fscanf_s(fp1, "%d", &(l->total_reserves), sizeof(int));
			fscanf_s(fp1, "%d", &(l->borrower), sizeof(int));
			p = (Borrow *)malloc(sizeof(Borrow));
			p->next = NULL;
			l->borrow = p;
			for (count = 1; count <= (l->borrower); count++)
			{
				q = (Borrow *)malloc(sizeof(Borrow));
				fscanf_s(fp1, "%u", &(q->library_card), sizeof(unsigned int));
				fscanf_s(fp1, "%d", &(q->borrow_date), sizeof(int));
				fscanf_s(fp1, "%d", &(q->return_date), sizeof(int));
				InsertBorrow(l->borrow, q);
			}
			InsertBook(L, l);   //�����µ��鼮�ڵ�
		}
		l = (Book *)malloc(sizeof(Book));
		i++;
		finish = getc(fp1);
	}
	fclose(fp1);   //�ر��鼮���������ĵ�
}

/*�õ������ѡ����ִ�ж�Ӧ����,ͬʱ���ַǷ�����*/
char ROM()
{
	int i = 0;   //��¼�����ַ�������
	char c, d;   //�õ���Ҫ�ַ�������������ַ�
	while (1)   //ֱ���õ������ַ����˳�ѭ��
	{
		message();
		remind();   //��ʾ��Ϣ
		c = getchar();   //��ȡ�ַ�
		while ((d = getchar()) != '\n')
			i++;   //��������ַ�����¼�ַ�������
		if (i == 0) break;   //ֻ��Ϊ1���ַ�ʱ�Ž����ж�
		else
			warn();   //����
		i = 0;   //i���¸�ֵ
	}
	return c;
}

void Finish()
{
	Book *l;   //��ȡ�鼮��Ϣ
	Borrow *q;   //��ȡ��������Ϣ
	errno_t err;   //���ļ�
	err = fopen_s(&fp1, "library", "w");   //���鼮���������ĵ�
	if (err != 0)
		printf("Can't open \"library\" file.");    //��ʧ��
	int i;    //ѭ���������н�������Ϣ
	for (l = L->next; l != NULL; l = l->next)
	{
		fprintf(fp1, "%c", '$');   //�µ��鼮�ڵ㿪ʼ�ı�־
		fprintf(fp1, "%50s ", l->ISBN);
		fprintf(fp1, "%100s ", l->name);
		fprintf(fp1, "%100s ", l->author);
		fprintf(fp1, " %d", l->able_borrow);
		fprintf(fp1, " %d", l->current_reserves);
		fprintf(fp1, " %d", l->total_reserves);
		fprintf(fp1, " %d", l->borrower);
		for (q = l->borrow, i = 0; i <= (l->borrower); q = q->next, i++)
		{
			if (i == 0) continue;
			fprintf(fp1, " %u", q->library_card);
			fprintf(fp1, " %d", q->borrow_date);
			fprintf(fp1, " %d", q->return_date);
		}
		fprintf(fp1, "%c", '\n');   //��һ�н�������
	}
	fclose(fp1);   //�ر��鼮���������ĵ�
	fclose(fp2);   //�ر�log�ĵ�
}