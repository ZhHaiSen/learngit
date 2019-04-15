#include <stdio.h>
#include <string.h>
#include "library.h"

/*�����������ļ������ڱ��ļ�Ҫ�õ��ı���*/
extern Borrow *Q;
extern Book *L;
extern int YEAR;
extern int MON;
extern int DAY;
extern int HOUR;
extern int MIN;
extern int SEC;
extern FILE *fp1, *fp2;

/*�ɱ����*/
Status inrepository(Book *L)
{
	int books,LOOP=0;   //�������������жϵ�ǰ�������Ƿ����Ȿ�鼮
	Book *l, *p;   //�ݴ浱ǰ�鼮��Ϣ�����������鼮����Ѱ�������Ϣ
	l = (Book *)malloc(sizeof(Book));
	printf("\n\t\t�����ǲɱ���⹦��,�밴�������ʾ��д�鱾��Ϣ\n");   //ʹ������д�鼮��Ϣ
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->ISBN), 50);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->name), 100);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->author), 100);
	printf("\t\t|                 |\n");
	printf("\t\t|    �������     |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%d",&books );
	for (p = L->next; p != NULL; p = p->next)   //������ǰ�鼮����
	{
		if (strcmp(l->ISBN, p->ISBN) == 0)   //�������鼮�Ѿ�λ�������� 
		{
			p->borrower = p->borrower;   //�ݲ�������
			p->total_reserves += books;
			p->current_reserves += books;
			p->able_borrow += books;
			LOOP = 1;   //��־��ǰ�鼮�Ѿ�λ��������
		}
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //������û�е�ǰ�鼮
	{
		Borrow *q;   //Ϊ�Ȿ�鼮�Ľ����������ٿռ�
		q = (Borrow *)malloc(sizeof(Borrow));   //������
		if (q == NULL)
			printf("�ڴ治��!");
		q->next = NULL;
		l->borrow = q;
		l->borrower = 0;   
		l->total_reserves = books;   //��¼�ݲ���
		l->current_reserves = books;
		l->able_borrow = books;
		InsertBook(L, l);   //���µ��鼮�ڵ���뵽�鼮������
	}
	for (p = L->next; strcmp(p->ISBN,l->ISBN)!=0; p = p->next)   //�ҵ�����鼮���ڽڵ�
		;
	printf("\n\t\t��ȷ�����µ���Ϣ�Ƿ���ȷ:\n");   //ȷ����Ϣ
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t%s\n", p->ISBN);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t%s\n", p->name);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t%s\n", p->author);
	printf("\t\t|                 |\n");
	printf("\t\t|     �ɽ���      |\n");
	printf("\t\t|_________________|");
	printf("\t%d\n", p->able_borrow);
	printf("\t\t|                 |\n");
	printf("\t\t|     �ִ���      |\n");
	printf("\t\t|_________________|");
	printf("\t%d\n", p->current_reserves);
	printf("\t\t|                 |\n");
	printf("\t\t|    �ܿ����     |\n");
	printf("\t\t|_________________|");
	printf("\t%d\n", p->total_reserves);
	systemtime();   //log�ļ�
	fprintf(fp2, "%d-%d-%d %d:%d:%d �ɱ����%s*%d", YEAR, MON, DAY, HOUR, MIN, SEC, p->ISBN, books);
	putc('\n', fp2);
	printf("\n\t\t���������Ϣ����,������N:");
	char c = getchar();
	c = getchar();
	if (c == 'n' || c == 'N')   //�������β����������鼮�ڵ��������ɾ��
	{
		DeleteBook(L, p->ISBN);
		fprintf(fp2, "%s", "give up this control");
		putc('\n', fp2);
	}
	return SUCCESS;
}

/*�������*/
Status outrepository(Book *L)
{
	int LOOP = 0;   //�ж�����������Ҫɾ�����鼮
	Book *l,*p;   //�ݴ�Ҫɾ�����鼮����Ϣ�ͱ����鼮����
	l = (Book *)malloc(sizeof(Book));
	printf("\n\t\t�����������湦��,�밴�������ʾ��д�鱾��Ϣ\n");   //��дҪɾ�����鼮����Ϣ
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->ISBN), 50);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->name), 100);
	printf("\t\t|                 |\n");
	printf("\t\t|      ����       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->author), 100);
	for (p = L->next; p != NULL; p = p->next)   //�����鼮����
	{
		if (strcmp(p->ISBN, l->ISBN) == 0)
			LOOP = 1;   //�ҵ�Ҫɾ�����鼮,LOOPֵ�ĸı��ʾ����ɾ��������鼮
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //�Ҳ���Ҫɾ�����鼮
	{
		printf("\n\t\t�����������!\n");
		return ERROR;
	}
	else   //����ɾ��������鼮
	{
		printf("\n\t\t��ȷ�����µ���Ϣ�Ƿ���ȷ:\n");   //ȷ���鼮��Ϣ
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      ���       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->ISBN);
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->name);
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->author);
		printf("\t\t|                 |\n");
		printf("\t\t|     �ɽ���      |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->able_borrow);
		printf("\t\t|                 |\n");
		printf("\t\t|     �ִ���      |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->current_reserves);
		printf("\t\t|                 |\n");
		printf("\t\t|    �ܿ����     |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->total_reserves);
		systemtime();   //log�ļ�
		fprintf(fp2, "%d-%d-%d %d:%d:%d �������%s", YEAR, MON, DAY, HOUR, MIN, SEC, p->ISBN);
		putc('\n', fp2);
		printf("\n\t\t���������Ϣ����,������N:");
		char c = getchar();
		c = getchar();
		if (c == 'n' || c == 'N')
		{
			fprintf(fp2, "%s", "give up this control");
			putc('\n', fp2);
			return ERROR;
		}
		else   //δ����n/N
		{
			DeleteBook(L, l->ISBN);   //ɾ��ָ���鼮
			printf("\n\t\tɾ���ɹ�!\n");
		}
	}
	return SUCCESS;
}

/*�鼮��Ϣ*/
Status bookInfor()
{
	bookinformation();
	printf("\n\t\t����������Ҫ���еĲ���ǰ������:");
	char c = getchar();
	char d;
	while ((d = getchar()) != '\n')
		;
	switch (c)
	{
	case '1':
		allbooks(L);   //�鿴ĳ����ȫ����������
		break;
	case '2':
		allinformation(L);   //�鿴ĳ�鼮��״̬��Ϣ
		break;
	default:
		warn();   //�Ƿ�����
	}
	return SUCCESS;
}

/*����*/
Status bookborrow(Book *L)
{
	int LOOP = 0;   //�����ж���Ҫ���ĵ���Ϣ�Ƿ����鼮������
	Book *l,*p;   //�ݴ���źͱ����鼮����
	l = (Book *)malloc(sizeof(Book));
	printf("\n\t\t�����ǽ��Ĺ���,�밴��Ҫ����д�����Ϣ:\n");   //��д���������
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->ISBN), 50);
	for (p = L->next; p != NULL; p = p->next)   //�����鼮����
	{
		if (strcmp(p->ISBN, l->ISBN) == 0)
			LOOP = 1;   //��Ҫ�����鼮���鼮������
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //��Ҫ�����鼮�����鼮������
	{
		printf("\n\t\t�����������!\n");
		return ERROR;
	}
	else   //��Ҫ�����鼮���鼮������
	{
		if (p->able_borrow <= 0)   //�ɽ���С�ڵ����㣬���ɽ���
			printf("\n\t\t�����ִ������㣬��ǰ�Ȿ�鲻�ɽ���\n");
		else   //���Խ���
		{
			Borrow *q;   //��Ž�������Ϣ
			int day;   //ѭ��90��,��ȡ�����º������
			q = (Borrow *)malloc(sizeof(Borrow));
			printf("\n\t\t����ʵ��д��������Ϣ\n");   //��д��������Ϣ
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|    ����֤��     |\n");
			printf("\t\t|_________________|");
			printf("\t");
			scanf_s("%d", &(q->library_card));
			systemtime();   //ϵͳ��д��������
			q->borrow_date = YEAR * 10000 + MON * 100 + DAY;
			for (day = 0; day < 90; day++)   //����90��������,����Ϊ�黹���ڼ����������Ϣ��
			{
				DAY++;
				if (MON == 2)
					if (DAY > 28)
					{
						DAY = 1;
						MON++;
					}
				if(MON==1||MON==3||MON==5||MON==7||MON==8||MON==10)
					if (DAY > 31)
					{
						DAY = 1;
						MON++;
					}
				if(MON==4||MON==6||MON==9||MON==11)
					if (DAY > 30)
					{
						DAY = 1;
						MON++;
					}
				if(MON==12)
					if (DAY > 31)
					{
						DAY = 1;
						MON = 1;
						YEAR++;
					}
			}
			q->return_date = YEAR * 10000 + MON  * 100 + DAY;
			printf("\n\t\t��ȷ�����µ���Ϣ�Ƿ���ȷ:\n");   //ȷ����Ϣ
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|    ����֤��     |\n");
			printf("\t\t|_________________|");
			printf("\t%u\n", q->library_card);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", q->borrow_date);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", q->return_date);
			printf("\t\t|                 |\n");
			printf("\t\t|      ���       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->ISBN);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->name);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->author);
			printf("\n\t\t���������Ϣ����,������N:");
			char c = getchar();
			c = getchar();
			if (c == 'n' || c == 'N')
				return ERROR;
			else
			{
				systemtime();    //log�ļ�
				fprintf(fp2, "%d-%d-%d %d:%d:%d %u�����鼮%s", YEAR, MON, DAY, HOUR, MIN, SEC, q->library_card,p->ISBN);
				putc('\n', fp2);
				InsertBorrow(p->borrow, q);   //���µĽ�������Ϣ���뵽���鼮��Ӧ�Ľ�����������
				p->borrower++;   //��������������
				p->current_reserves--;   //�ݲ�������
				p->able_borrow--;
				printf("\n\t\t���ĳɹ�,����%d��%d��%d��ǰǰ������\n", YEAR, MON, DAY);
				return SUCCESS;
			}
		}
	}
}

/*�黹*/
Status bookreturn(Book *L)
{
	int LOOP = 0;   //�ж���������Ƿ����鼮�������ж�Ӧ���鼮������֤���Ƿ��ڸ��鼮�Ľ�����������
	Book *l,*d;   //�ݴ��鼮��Ϣ�ͱ����鼮����
	Borrow *q, *p;   //�ݴ����֤�źͱ������鼮�Ľ���������
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	printf("\n\t\t�����ǹ黹����,�밴��Ҫ����д�����Ϣ:\n");   //��д�黹��źͽ���֤��
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s", &(l->ISBN), 50);
	printf("\t\t|                 |\n");
	printf("\t\t|    ����֤��     |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%u",&(q->library_card));
	for (d = L->next; d != NULL; d = d->next)   //�����鼮����
	{
		if (strcmp(d->ISBN, l->ISBN) == 0)
			LOOP = 1;   //�鼮������������Ҫ�ҵ����
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //�鼮������û������Ҫ�ҵ����
		printf("\n\t\t�������Ų���ȷ!\n");
	else   //�鼮������������Ҫ�ҵ����
	{
		LOOP = 0;   //����LOOP,������һ�ֵ��ж�,��������Ľ���֤���Ƿ��ڸ��鼮�Ľ�����������
		for (p = d->borrow; p != NULL; p = p->next)   //�������鼮�Ľ���������
		{
			if (p->library_card==q->library_card)
				LOOP = 1;   //������Ľ���֤���ڸ��鼮����Ӧ�Ľ�����������
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //������Ľ���֤�Ų��ڸ��鼮�Ľ�����������
			printf("\n\t\t����Ľ���֤�Ų���ȷ!\n");
		else   //������Ľ���֤���ڸ��鼮�Ľ�����������
		{
			printf("\n\t\t��ȷ�����µ���Ϣ�Ƿ���ȷ:\n");   //ȷ����Ϣ
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|    ����֤��     |\n");
			printf("\t\t|_________________|");
			printf("\t%u\n", p->library_card);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", p->borrow_date);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", p->return_date);
			printf("\t\t|                 |\n");
			printf("\t\t|      ���       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", d->ISBN);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", d->name);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", d->author);
			printf("\n\t\t���������Ϣ����,������N:");
			char c = getchar();
			c = getchar();
			if (c == 'n' || c == 'N')
				return ERROR;
			else
			{
				systemtime();   //log�ļ�
				fprintf(fp2, "%d-%d-%d %d:%d:%d %u�黹�鼮%s", YEAR, MON, DAY, HOUR, MIN, SEC, p->library_card, d->ISBN);
				putc('\n', fp2);
				systemtime();   //�Ƿ����ڹ黹���ж�
				if ((YEAR * 10000 + MON * 100 + DAY) > p->return_date)
					printf("\t\t��ע��,�Ѿ������涨���ڻ���!\n");
				DeleteBorrow(d->borrow, p->library_card);   //�Ӹý�����������ɾ����������ߵ���Ϣ
				d->borrower--;   //��������������
				d->current_reserves++;   //�ݲ�������
				d->able_borrow++;
				printf("\n\t\t����ɹ�\n");
				return SUCCESS;
			}
		}
	}
}

/*ԤԼ����*/
Status reservebook(Book *L)
{
	int LOOP = 0,i;   //�ж��鼮������������Ҫ���ĵ��鼮�������ڵ�ǰ��ԤԼ��������֮��黹�ѽ��鼮����
	int year, mon, day,Year,Mon,Day;   //�洢ԤԼ�������ں͵�ǰ����
	unsigned int card;   //�ݴ����֤��
	char booknumber[50];   //�ݴ����
	Book *l;   //�����鼮����
	Borrow *q;   //������Ҫ�����鼮�Ľ���������
	printf("\n\t\t������ԤԼ���鹦��,�밴����ʾ��д�����Ϣ");   //��д����֤�ź���Ҫ���ĵ��鼮�����
	printf("\t\t _________________ \n");
	printf("\t\t|                 |\n");
	printf("\t\t|    ����֤��     |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%u",&card);
	printf("\t\t|                 |\n");
	printf("\t\t|      ���       |\n");
	printf("\t\t|_________________|");
	printf("\t");
	scanf_s("%s",&booknumber,50 );
	for (l = L->next; l != NULL; l = l->next)   //�����鼮����
	{
		if (strcmp(l->ISBN, booknumber) == 0)
			LOOP = 1;   //�鼮�������и��������Ӧ���鼮
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //�鼮������û�и��������Ӧ���鼮
		printf("\t\t���������д���!\n");
	else
	{
		LOOP = 0;   //�ж������ڵ�ǰ��ԤԼ����ʱ��֮�ڹ黹�ѽ��鼮����
		systemtime();   //��ȡ��ǰ�ꡢ�¡���
		Year = YEAR;
		Mon = MON;
		Day = DAY;
		printf("\t\t����������ҪԤԼ���ĵ�ʱ��(3����֮����Ч)\n");   //����ԤԼ����ʱ��
		printf("\t\t|                 |\n");
		printf("\t\t|       ��        |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n",&year);
		printf("\t\t|                 |\n");
		printf("\t\t|       ��        |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n",&mon);
		printf("\t\t|                 |\n");
		printf("\t\t|       ��        |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n",&day);
		for (i = 0; i < 90; i++)   //ѭ��90��,�õ��Ե�ǰʱ��Ϊ��׼�������º������
		{
			DAY++;
			if (MON == 2)
				if (DAY > 28)
				{
					DAY = 1;
					MON++;
				}
			if (MON == 1 || MON == 3 || MON == 5 || MON == 7 || MON == 8 || MON == 10)
				if (DAY > 31)
				{
					DAY = 1;
					MON++;
				}
			if (MON == 4 || MON == 6 || MON == 9 || MON == 11)
				if (DAY > 30)
				{
					DAY = 1;
					MON++;
				}
			if (MON == 12)
				if (DAY > 31)
				{
					DAY = 1;
					MON = 1;
					YEAR++;
				}
		}
		if ((year * 10000 + mon * 100 + day) <= (Year * 10000 + Mon * 100 + Day))   //������ʱ���ڵ�ǰʱ��֮ǰ
			printf("\t\t����ʱ������!\n");
		else if ((year * 10000 + mon * 100 + day) > (YEAR * 10000 + MON * 100 + DAY))   //������ʱ���ڵ�ǰʱ��������º�
			printf("\t\t������3����֮�ڵ�ʱ��!\n");
		else
		{
			for (q = l->borrow; q != NULL; q = q->next)   //������Ҫ���ĵ��鼮�Ľ���������
			{
				if (q->return_date > (YEAR * 10000 + MON * 100 + DAY) && q->return_date < (year * 10000 + mon * 100 + day))
					LOOP = 1;   //���ڵ�ǰ��ԤԼ����ʱ��֮�ڹ黹�ѽ��鼮����
				if (LOOP == 1) break;
			}
			if (l->able_borrow == 0 && LOOP == 0)   //���������鼮��Դ
				printf("\t\t�Բ���,ԤԼʧ��\n");
			else
			{
				printf("\n\t\t��ȷ�����µ���Ϣ�Ƿ���ȷ:\n");   //ȷ����Ϣ
				printf("\t\t _________________ \n");
				printf("\t\t|                 |\n");
				printf("\t\t|    ����֤��     |\n");
				printf("\t\t|_________________|");
				printf("\t%u\n", card);
				printf("\t\t|                 |\n");
				printf("\t\t|   ԤԼ��������  |\n");
				printf("\t\t|_________________|");
				printf("\t%d\n", year * 10000 + mon * 100 + day);
				printf("\t\t|                 |\n");
				printf("\t\t|      ���       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", l->ISBN);
				printf("\t\t|                 |\n");
				printf("\t\t|      ����       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", l->name);
				printf("\t\t|                 |\n");
				printf("\t\t|      ����       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", l->author);
				printf("\n\t\t���������Ϣ����,������N:");
				char c = getchar();
				c = getchar();
				if (c == 'n' || c == 'N')
					return ERROR;
				else
				{
					systemtime();   //log�ļ�
					fprintf(fp2, "%d-%d-%d %d:%d:%d %sԤԼ����%s", YEAR, MON, DAY, HOUR, MIN, SEC, card, l->ISBN);
					putc('\n', fp2);
					//���鼮��Դ
					if (l->able_borrow > 0 && LOOP == 0)  
					{
						(l->able_borrow)--;
						printf("\t\tԤԼ�ɹ�,����%d��%d��%d��ǰ������\n");
						return SUCCESS;
					}
					else   
					{
						(l->able_borrow)--;
						printf("\t\tԤԼ�ɹ�,����%d��%d��%d��ǰ������\n");
						return SUCCESS;
					}
				}
			}
		}
	}
}

/*ȫ������*/
void allbooks(Book *L)
{
	char authorname[100];   //�ݴ�������
	int LOOP = 0;   //�ж��鼮���������޸����ߵ��鼮
	int n = 0;   //ÿ���4�������ͻ������
	Book *l;   //�����鼮����
	l = (Book *)malloc(sizeof(Book));
	printf("\n\t\t����Ҫ������λ���ߵ���������:");
	scanf_s("%s", authorname, 100);
	for (l = L->next; l != NULL; l = l->next)   //�����鼮����
	{
		if (strcmp(l->author, authorname) == 0)
			LOOP = 1;   //�鼮�������и����ߵ�����
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //�鼮������û�и����ߵ�����
		printf("\t\t�Բ���,��ͼ�����û���ղظ����ߵ�����\n");
	else   //�鼮�������и����ߵ�����
	{
		systemtime();    //log�ļ�
		fprintf(fp2, "%d-%d-%d %d:%d:%d �鿴%sȫ������", YEAR, MON, DAY, HOUR, MIN, SEC, l->author);
		putc('\n', fp2);
		printf("\t\t��λ���ߵ�������:\n\t");
		for (; l != NULL; l = l->next)   //�ҳ��鼮���������и����ߵ�����
		{
			if (strcmp(l->author, authorname) == 0)
			{
				printf("\t%s", l->name);
				n++;
			}
			if (n % 4 == 0)   //ÿ���4�������ͻ������
				printf("\n\t");
		}
	}
}

/*�鼮��Ϣ*/
void allinformation(Book *L)
{
	int LOOP = 0,i;   //�ж��鼮������������Ҫ���ĵ��鼮�����������ڵĽ�������Ϣ
	Book *l;   //�����鼮����
	Borrow *q;   //���������ڵĽ�������Ϣ
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	char booknumber[50];   //�ݴ���������
	printf("\t\t����������Ҫ���ĵ��鼮�����:");
	scanf_s("%s", booknumber, 50);
	for (l = L->next; l != NULL; l = l->next)   //�����鼮����
	{
		if (strcmp(l->ISBN, booknumber) == 0)
			LOOP = 1;   //�ҵ�����Ŷ�Ӧ���鼮
		if (LOOP == 1) break;
	}
	if (LOOP == 0)   //�����ڸ���Ŷ�Ӧ���鼮
		printf("\t\tͼ����в����ڸ��������Ӧ���鼮\n");
	else   //�ҵ�����Ŷ�Ӧ���鼮
	{
		systemtime();   //log�ļ�
		fprintf(fp2, "%d-%d-%d %d:%d:%d �鿴�鼮%s��Ϣ", YEAR, MON, DAY, HOUR, MIN, SEC, l->ISBN);
		putc('\n', fp2);
		q = l->borrow;
		if (q->next == NULL)   //���鼮û�н�����,��ֻ����鼮��Ϣ
		{
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|      ���       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->ISBN);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->name);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->author);
			printf("\t\t|                 |\n");
			printf("\t\t|     �ɽ���      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->able_borrow);
			printf("\t\t|                 |\n");
			printf("\t\t|     �ִ���      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->current_reserves);
			printf("\t\t|                 |\n");
			printf("\t\t|    �ܿ����     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->total_reserves);
		}
		else   //���鼮�н�����
		{
			for (q = l->borrow, i = 1; i <= 1; i++, q = q->next)   //�ҵ�������ڵĽ�������Ϣ,�����鼮��Ϣ�͸ý�������Ϣһ�����
				;
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|      ���       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->ISBN);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->name);
			printf("\t\t|                 |\n");
			printf("\t\t|      ����       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", l->author);
			printf("\t\t|                 |\n");
			printf("\t\t|     �ɽ���      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->able_borrow);
			printf("\t\t|                 |\n");
			printf("\t\t|     �ִ���      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->current_reserves);
			printf("\t\t|                 |\n");
			printf("\t\t|    �ܿ����     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", l->total_reserves);
			printf("\t\t|                 |\n");
			printf("\t\t|    ����֤��     |\n");
			printf("\t\t|_________________|");
			printf("\t%u\n", q->library_card);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", q->borrow_date);
			printf("\t\t|                 |\n");
			printf("\t\t|    ��������     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", q->return_date);
		}
	}
}
