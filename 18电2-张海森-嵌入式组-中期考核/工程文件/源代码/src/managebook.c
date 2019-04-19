#include <stdio.h>
#include <string.h>
#include <conio.h>
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
	char c , d;
	Book *l, *p;   //�ݴ浱ǰ�鼮��Ϣ�����������鼮����Ѱ�������Ϣ
	l = (Book *)malloc(sizeof(Book));
	while (LOOP != 2)
	{
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
		scanf_s("%d", &books);
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
		for (p = L->next; strcmp(p->ISBN, l->ISBN) != 0; p = p->next)   //�ҵ�����鼮���ڽڵ�
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
		printf("\n\t\t���������Ϣ����,������N(�������س�):");
		char c = getchar();
		c = getchar();
		if (c == 'n' || c == 'N')   //�������β����������鼮�ڵ��������ɾ��
		{
			c = getchar();
			DeleteBook(L, p->ISBN);
			fprintf(fp2, "%s", "give up this control");
			putc('\n', fp2);
		}
		printf("\n\t\t������˳��ɱ���⣬������x(���򰴻س�):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*�������*/
Status outrepository(Book *L)
{
	int LOOP = 0;   //�ж�����������Ҫɾ�����鼮
	char c  , d;
	Book *l,*p;   //�ݴ�Ҫɾ�����鼮����Ϣ�ͱ����鼮����
	l = (Book *)malloc(sizeof(Book));
	while (LOOP!=2)
	{
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
			char c = getchar();
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
			printf("\n\t\t���������Ϣ����,������N(�������س�):");
			char c = getchar();
			c = getchar();
			if (c == 'n' || c == 'N')
			{
				c = getchar();
				fprintf(fp2, "%s", "give up this control");
				putc('\n', fp2);
			}
			else   //δ����n/N
			{
				DeleteBook(L, l->ISBN);   //ɾ��ָ���鼮
				printf("\n\t\tɾ���ɹ�!\n");
			}
		}
		LOOP = 0;
		printf("\n\t\t������˳������棬������x(���򰴻س�):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*�鼮��Ϣ*/
Status bookInfor()
{
	bookinformation();
	char c = 'a';
	while (c != 'x')
	{
		printf("\n\t\t����������Ҫ���еĲ���ǰ������(�˳���x):");
		c = getchar();
		char d;
		while ((d = getchar()) != '\n')
			;
		switch (c)
		{
		case '1':
			librarybook(L);
			break;
		case '2':
			allbooks(L);   //�鿴ĳ����ȫ����������
			break;
		case '3':
			allinformation(L);   //�鿴ĳ�鼮��״̬��Ϣ
			break;
		case 'x':
			break;
		default:
			warn();   //�Ƿ�����
		}
	}
	return SUCCESS;
}

/*����*/
Status bookborrow(Book *L)
{
	int LOOP = 0;   //�����ж���Ҫ���ĵ���Ϣ�Ƿ����鼮������
	char c, d;
	char bookname[100], bookauthor[100];
	int year, mon, day;
	Book *l,*p;   //�ݴ���źͱ����鼮����
	l = (Book *)malloc(sizeof(Book));
	while (LOOP != 2)
	{
		printf("\n\t\t�����ǽ��Ĺ���,�밴��Ҫ����д�����Ϣ:\n");   //��д���������
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", bookname, 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", bookauthor, 100);
		for (p = L->next; p != NULL; p = p->next)   //�����鼮����
		{
			if (strcmp(p->name, bookname) == 0 && strcmp(p->author, bookauthor) == 0)
				LOOP = 1;   //��Ҫ�����鼮���鼮������
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //��Ҫ�����鼮�����鼮������
		{
			printf("\n\t\t��������(����)����!\n");
			c = getchar();
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
				q->return_date = YEAR * 10000 + MON * 100 + DAY;
				year = YEAR;
				mon = MON;
				day = DAY;;
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
				printf("\n\t\t���������Ϣ����,������N(�������س�):");
				char c = getchar();
				c = getchar();
				if (c == 'n' || c == 'N')
				{
					c = getchar();
				}
				else
				{
					systemtime();    //log�ļ�
					fprintf(fp2, "%d-%d-%d %d:%d:%d %u�����鼮%s", YEAR, MON, DAY, HOUR, MIN, SEC, q->library_card, p->ISBN);
					putc('\n', fp2);
					InsertBorrow(p->borrow, q);   //���µĽ�������Ϣ���뵽���鼮��Ӧ�Ľ�����������
					p->borrower++;   //��������������
					p->current_reserves--;   //�ݲ�������
					p->able_borrow--;
					printf("\n\t\t���ĳɹ�,����%d��%d��%d��ǰǰ������\n", year, mon, day);
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t������˳����ģ�������x(���򰴻س�):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*�黹*/
Status bookreturn(Book *L)
{
	int LOOP = 0;   //�ж���������Ƿ����鼮�������ж�Ӧ���鼮������֤���Ƿ��ڸ��鼮�Ľ�����������
	char a, b;
	Book *l,*d;   //�ݴ��鼮��Ϣ�ͱ����鼮����
	Borrow *q, *p;   //�ݴ����֤�źͱ������鼮�Ľ���������
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	while (LOOP != 2)
	{
		printf("\n\t\t�����ǹ黹����,�밴��Ҫ����д�����Ϣ:\n");   //��д�黹��źͽ���֤��
		printf("\t\t _________________ \n");
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
		printf("\t\t|    ����֤��     |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%u", &(q->library_card));
		for (d = L->next; d != NULL; d = d->next)   //�����鼮����
		{
			if (strcmp(d->name, l->name) == 0 && strcmp(d->author, l->author) == 0)
				LOOP = 1;   //�鼮������������Ҫ�ҵ����
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //�鼮������û������Ҫ�ҵ����
		{
			printf("\n\t\t��������(����)����!\n");
			char c = getchar();
		}
		else   //�鼮������������Ҫ�ҵ����
		{
			LOOP = 0;   //����LOOP,������һ�ֵ��ж�,��������Ľ���֤���Ƿ��ڸ��鼮�Ľ�����������
			for (p = d->borrow; p != NULL; p = p->next)   //�������鼮�Ľ���������
			{
				if (p->library_card == q->library_card)
					LOOP = 1;   //������Ľ���֤���ڸ��鼮����Ӧ�Ľ�����������
				if (LOOP == 1) break;
			}
			if (LOOP == 0)   //������Ľ���֤�Ų��ڸ��鼮�Ľ�����������
			{
				printf("\n\t\t����Ľ���֤�Ų���ȷ!\n");
				char c = getchar();
			}
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
				printf("\n\t\t���������Ϣ����,������N(�������س�):");
				char c = getchar();
				c = getchar();
				if (c == 'n' || c == 'N')
				{
					c = getchar();
				}
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
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t������˳��黹��������x(���򰴻س�):");
		a = getchar();
		if (a == 'x') LOOP = 2;
		if (a == '\n') continue;
		while ((b = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*ԤԼ����*/
Status reservebook(Book *L)
{
	int LOOP = 0,i;   //�ж��鼮������������Ҫ���ĵ��鼮�������ڵ�ǰ��ԤԼ��������֮��黹�ѽ��鼮����
	int year, mon, day,Year,Mon,Day;   //�洢ԤԼ�������ں͵�ǰ����
	char c, d;
	unsigned int card;   //�ݴ����֤��
	char bookname[100];   //�ݴ����
	char bookwriter[100];
	Book *l;   //�����鼮����
	Borrow *q;   //������Ҫ�����鼮�Ľ���������
	while (LOOP != 2)
	{
		printf("\n\t\t������ԤԼ���鹦��,�밴����ʾ��д�����Ϣ\n");   //��д����֤�ź���Ҫ���ĵ��鼮�����
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|    ����֤��     |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%u", &card);
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &bookname, 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      ����       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &bookwriter, 100);
		for (l = L->next; l != NULL; l = l->next)   //�����鼮����
		{
			if (strcmp(l->name, bookname) == 0 && strcmp(l->author, bookwriter) == 0)
				LOOP = 1;   //�鼮�������и��������Ӧ���鼮
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //�鼮������û�и��������Ӧ���鼮
		{
			printf("\n\t\t�������������!\n");
			char c = getchar();
		}
		else
		{
			LOOP = 0;   //�ж������ڵ�ǰ��ԤԼ����ʱ��֮�ڹ黹�ѽ��鼮����
			systemtime();   //��ȡ��ǰ�ꡢ�¡���
			Year = YEAR;
			Mon = MON;
			Day = DAY;
			printf("\n\t\t����������ҪԤԼ���ĵ�ʱ��(3����֮����Ч)\n");   //����ԤԼ����ʱ��
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|       ��        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &year);
			printf("\t\t|                 |\n");
			printf("\t\t|       ��        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &mon);
			printf("\t\t|                 |\n");
			printf("\t\t|       ��        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &day);
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
			{
				printf("\n\t\t����ʱ������!\n");
				char c = getchar();
			}
			else if ((year * 10000 + mon * 100 + day) > (YEAR * 10000 + MON * 100 + DAY))   //������ʱ���ڵ�ǰʱ��������º�
			{
				printf("\n\t\t������3����֮�ڵ�ʱ��!\n");
				char c = getchar();
			}
			else
			{
				for (q = l->borrow; q != NULL; q = q->next)   //������Ҫ���ĵ��鼮�Ľ���������
				{
					if (q->return_date > (YEAR * 10000 + MON * 100 + DAY) && q->return_date < (year * 10000 + mon * 100 + day))
						LOOP = 1;   //���ڵ�ǰ��ԤԼ����ʱ��֮�ڹ黹�ѽ��鼮����
					if (LOOP == 1) break;
				}
				if (l->able_borrow == 0 && LOOP == 0)   //���������鼮��Դ
					printf("\n\t\t�Բ���,ԤԼʧ��\n");
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
					printf("\n\t\t���������Ϣ����,������N(�������س�):");
					char c = getchar();
					c = getchar();
					if (c == 'n' || c == 'N')
					{
						c = getchar();
					}
					else
					{
						systemtime();   //log�ļ�
						fprintf(fp2, "%d-%d-%d %d:%d:%d %uԤԼ����%s", YEAR, MON, DAY, HOUR, MIN, SEC, card, l->ISBN);
						putc('\n', fp2);
						//���鼮��Դ
						if (l->able_borrow > 0 && LOOP == 0)
						{
							(l->able_borrow)--;
							printf("\n\t\tԤԼ�ɹ�,����%d��%d��%d��ǰ������\n", year, mon, day);
						}
						else
						{
							(l->able_borrow)--;
							printf("\n\t\tԤԼ�ɹ�,����%d��%d��%d��ǰ������\n", year, mon, day);
						}
					}
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t������˳��黹��������x(���򰴻س�):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}

/*�鿴�����鼮*/
void librarybook(Book *L)
{
	Book *l;
	printf("\n\t\t��ͼ�����ȫ���鼮����:\n");
	for (l = L->next; l != NULL; l = l->next)
	{
		printf("\n\t\t%s", l->ISBN);
		printf("\t");
		printf("\t%s", l->name);
		printf("\t%s", l->author);
	}
	printf("\n");
}

/*ȫ������*/
void allbooks(Book *L)
{
	char authorname[100];   //�ݴ�������
	char c='a',d;
	int LOOP = 0;   //�ж��鼮���������޸����ߵ��鼮
	int n = 0;   //ÿ���4�������ͻ������
	Book *l;   //�����鼮����
	l = (Book *)malloc(sizeof(Book));
	while (c != 'x')
	{
		printf("\n\t\t����Ҫ������λ���ߵ���������:");
		scanf_s("%s", authorname, 100);
		scanf_s("%c", &c, 1);
		for (l = L->next; l != NULL; l = l->next)   //�����鼮����
		{
			if (strcmp(l->author, authorname) == 0)
				LOOP = 1;   //�鼮�������и����ߵ�����
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //�鼮������û�и����ߵ�����
			printf("\n\t\t�Բ���,��ͼ�����û���ղظ����ߵ�����\n");
		else   //�鼮�������и����ߵ�����
		{
			systemtime();    //log�ļ�
			fprintf(fp2, "%d-%d-%d %d:%d:%d �鿴%sȫ������", YEAR, MON, DAY, HOUR, MIN, SEC, l->author);
			putc('\n', fp2);
			printf("\n\t\t��λ���ߵ�������:\n\t");
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
			printf("\n");
		}
		printf("\n\t\t������˳����ң�������x(���򰴻س�):");
		c = getchar();
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}

/*�鼮��Ϣ*/
void allinformation(Book *L)
{
	int LOOP = 0,i;   //�ж��鼮������������Ҫ���ĵ��鼮�����������ڵĽ�������Ϣ
	char c='a',d;
	Book *l;   //�����鼮����
	Borrow *q;   //���������ڵĽ�������Ϣ
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	char bookinf[100];   //�ݴ���������
	while (c != 'x')
	{
		printf("\n\t\t����������Ҫ���ĵ��鼮�����/����/����:");
		scanf_s("%s", bookinf, 100);
		scanf_s("%c", &c, 1);
		for (l = L->next; l != NULL; l = l->next)   //�����鼮����
		{
			if (strcmp(l->ISBN, bookinf) == 0 || strcmp(l->name, bookinf) == 0 || strcmp(l->author, bookinf) == 0)
				LOOP = 1;   //�ҵ�����Ŷ�Ӧ���鼮
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //�����ڸ���Ŷ�Ӧ���鼮
			printf("\n\t\tͼ����в������Ȿ��\n");
		else   //�ҵ�����Ŷ�Ӧ���鼮
		{
			systemtime();   //log�ļ�
			fprintf(fp2, "%d-%d-%d %d:%d:%d �鿴�鼮%s��Ϣ", YEAR, MON, DAY, HOUR, MIN, SEC, bookinf);
			putc('\n', fp2);
			for (; l != NULL; l = l->next)
			{
				if (strcmp(l->ISBN, bookinf) == 0 || strcmp(l->name, bookinf) == 0 || strcmp(l->author, bookinf) == 0)
				{
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
					printf("\n");
				}
			}
		}
		printf("\n\t\t������˳����ң�������x(���򰴻س�):");
		c = getchar();
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}
