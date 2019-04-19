#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "library.h"

/*出现于其他文件中且在本文件要用到的变量*/
extern Borrow *Q;
extern Book *L;
extern int YEAR;
extern int MON;
extern int DAY;
extern int HOUR;
extern int MIN;
extern int SEC;
extern FILE *fp1, *fp2;

/*采编入库*/
Status inrepository(Book *L)
{
	int books,LOOP=0;   //存放入库数量和判断当前链表中是否有这本书籍
	char c , d;
	Book *l, *p;   //暂存当前书籍信息和用来遍历书籍链表寻找相关信息
	l = (Book *)malloc(sizeof(Book));
	while (LOOP != 2)
	{
		printf("\n\t\t以下是采编入库功能,请按照相关提示填写书本信息\n");   //使用者填写书籍信息
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      书号       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->ISBN), 50);
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->name), 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->author), 100);
		printf("\t\t|                 |\n");
		printf("\t\t|    入库数量     |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%d", &books);
		for (p = L->next; p != NULL; p = p->next)   //遍历当前书籍链表
		{
			if (strcmp(l->ISBN, p->ISBN) == 0)   //如果入库书籍已经位于链表中 
			{
				p->borrower = p->borrower;   //馆藏量增加
				p->total_reserves += books;
				p->current_reserves += books;
				p->able_borrow += books;
				LOOP = 1;   //标志当前书籍已经位于链表中
			}
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //链表中没有当前书籍
		{
			Borrow *q;   //为这本书籍的借阅者链表开辟空间
			q = (Borrow *)malloc(sizeof(Borrow));   //借阅者
			if (q == NULL)
				printf("内存不足!");
			q->next = NULL;
			l->borrow = q;
			l->borrower = 0;
			l->total_reserves = books;   //记录馆藏量
			l->current_reserves = books;
			l->able_borrow = books;
			InsertBook(L, l);   //将新的书籍节点加入到书籍链表中
		}
		for (p = L->next; strcmp(p->ISBN, l->ISBN) != 0; p = p->next)   //找到入库书籍所在节点
			;
		printf("\n\t\t请确认以下的信息是否正确:\n");   //确认信息
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      书号       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->ISBN);
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->name);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t%s\n", p->author);
		printf("\t\t|                 |\n");
		printf("\t\t|     可借量      |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->able_borrow);
		printf("\t\t|                 |\n");
		printf("\t\t|     现存量      |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->current_reserves);
		printf("\t\t|                 |\n");
		printf("\t\t|    总库存量     |\n");
		printf("\t\t|_________________|");
		printf("\t%d\n", p->total_reserves);
		systemtime();   //log文件
		fprintf(fp2, "%d-%d-%d %d:%d:%d 采编入库%s*%d", YEAR, MON, DAY, HOUR, MIN, SEC, p->ISBN, books);
		putc('\n', fp2);
		printf("\n\t\t如果以上信息有误,请输入N(继续按回车):");
		char c = getchar();
		c = getchar();
		if (c == 'n' || c == 'N')   //放弃本次操作，则将新书籍节点从链表中删除
		{
			c = getchar();
			DeleteBook(L, p->ISBN);
			fprintf(fp2, "%s", "give up this control");
			putc('\n', fp2);
		}
		printf("\n\t\t如果想退出采编入库，请输入x(否则按回车):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*清除出库*/
Status outrepository(Book *L)
{
	int LOOP = 0;   //判断链表中有无要删除的书籍
	char c  , d;
	Book *l,*p;   //暂存要删除的书籍的信息和遍历书籍链表
	l = (Book *)malloc(sizeof(Book));
	while (LOOP!=2)
	{
		printf("\n\t\t以下是清除库存功能,请按照相关提示填写书本信息\n");   //填写要删除的书籍的信息
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      书号       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->ISBN), 50);
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->name), 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->author), 100);
		for (p = L->next; p != NULL; p = p->next)   //遍历书籍链表
		{
			if (strcmp(p->ISBN, l->ISBN) == 0)
				LOOP = 1;   //找到要删除的书籍,LOOP值的改变表示可以删除输入的书籍
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //找不到要删除的书籍
		{
			char c = getchar();
			printf("\n\t\t输入书号有误!\n");
			return ERROR;
		}
		else   //可以删除输入的书籍
		{
			printf("\n\t\t请确认以下的信息是否正确:\n");   //确认书籍信息
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|      书号       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->ISBN);
			printf("\t\t|                 |\n");
			printf("\t\t|      书名       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->name);
			printf("\t\t|                 |\n");
			printf("\t\t|      作者       |\n");
			printf("\t\t|_________________|");
			printf("\t%s\n", p->author);
			printf("\t\t|                 |\n");
			printf("\t\t|     可借量      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", p->able_borrow);
			printf("\t\t|                 |\n");
			printf("\t\t|     现存量      |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", p->current_reserves);
			printf("\t\t|                 |\n");
			printf("\t\t|    总库存量     |\n");
			printf("\t\t|_________________|");
			printf("\t%d\n", p->total_reserves);
			systemtime();   //log文件
			fprintf(fp2, "%d-%d-%d %d:%d:%d 清除出库%s", YEAR, MON, DAY, HOUR, MIN, SEC, p->ISBN);
			putc('\n', fp2);
			printf("\n\t\t如果以上信息有误,请输入N(继续按回车):");
			char c = getchar();
			c = getchar();
			if (c == 'n' || c == 'N')
			{
				c = getchar();
				fprintf(fp2, "%s", "give up this control");
				putc('\n', fp2);
			}
			else   //未输入n/N
			{
				DeleteBook(L, l->ISBN);   //删除指定书籍
				printf("\n\t\t删除成功!\n");
			}
		}
		LOOP = 0;
		printf("\n\t\t如果想退出清除库存，请输入x(否则按回车):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*书籍信息*/
Status bookInfor()
{
	bookinformation();
	char c = 'a';
	while (c != 'x')
	{
		printf("\n\t\t请输入你想要进行的操作前的数字(退出按x):");
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
			allbooks(L);   //查看某著者全部著作名称
			break;
		case '3':
			allinformation(L);   //查看某书籍的状态信息
			break;
		case 'x':
			break;
		default:
			warn();   //非法输入
		}
	}
	return SUCCESS;
}

/*借阅*/
Status bookborrow(Book *L)
{
	int LOOP = 0;   //用于判断所要借阅的信息是否在书籍链表中
	char c, d;
	char bookname[100], bookauthor[100];
	int year, mon, day;
	Book *l,*p;   //暂存书号和遍历书籍链表
	l = (Book *)malloc(sizeof(Book));
	while (LOOP != 2)
	{
		printf("\n\t\t以下是借阅功能,请按照要求填写相关信息:\n");   //填写借阅书书号
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", bookname, 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", bookauthor, 100);
		for (p = L->next; p != NULL; p = p->next)   //遍历书籍链表
		{
			if (strcmp(p->name, bookname) == 0 && strcmp(p->author, bookauthor) == 0)
				LOOP = 1;   //所要借阅书籍在书籍链表中
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //所要借阅书籍不在书籍链表中
		{
			printf("\n\t\t输入书名(作者)有误!\n");
			c = getchar();
		}
		else   //所要借阅书籍在书籍链表中
		{
			if (p->able_borrow <= 0)   //可借量小于等于零，不可借阅
				printf("\n\t\t由于现存量不足，当前这本书不可借阅\n");
			else   //可以借阅
			{
				Borrow *q;   //存放借阅者信息
				int day;   //循环90次,获取三个月后的日期
				q = (Borrow *)malloc(sizeof(Borrow));
				printf("\n\t\t请如实填写借阅者信息\n");   //填写借阅者信息
				printf("\t\t _________________ \n");
				printf("\t\t|                 |\n");
				printf("\t\t|    借阅证号     |\n");
				printf("\t\t|_________________|");
				printf("\t");
				scanf_s("%d", &(q->library_card));
				systemtime();   //系统填写借阅日期
				q->borrow_date = YEAR * 10000 + MON * 100 + DAY;
				for (day = 0; day < 90; day++)   //计算90天后的日期,并作为归还日期记入借阅者信息中
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
				printf("\n\t\t请确认以下的信息是否正确:\n");   //确认信息
				printf("\t\t _________________ \n");
				printf("\t\t|                 |\n");
				printf("\t\t|    借阅证号     |\n");
				printf("\t\t|_________________|");
				printf("\t%u\n", q->library_card);
				printf("\t\t|                 |\n");
				printf("\t\t|    借书日期     |\n");
				printf("\t\t|_________________|");
				printf("\t%d\n", q->borrow_date);
				printf("\t\t|                 |\n");
				printf("\t\t|    还书日期     |\n");
				printf("\t\t|_________________|");
				printf("\t%d\n", q->return_date);
				printf("\t\t|                 |\n");
				printf("\t\t|      书号       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", p->ISBN);
				printf("\t\t|                 |\n");
				printf("\t\t|      书名       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", p->name);
				printf("\t\t|                 |\n");
				printf("\t\t|      作者       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", p->author);
				printf("\n\t\t如果以上信息有误,请输入N(继续按回车):");
				char c = getchar();
				c = getchar();
				if (c == 'n' || c == 'N')
				{
					c = getchar();
				}
				else
				{
					systemtime();    //log文件
					fprintf(fp2, "%d-%d-%d %d:%d:%d %u借阅书籍%s", YEAR, MON, DAY, HOUR, MIN, SEC, q->library_card, p->ISBN);
					putc('\n', fp2);
					InsertBorrow(p->borrow, q);   //将新的借阅者信息加入到该书籍对应的借阅者链表中
					p->borrower++;   //借阅者数量增加
					p->current_reserves--;   //馆藏量减少
					p->able_borrow--;
					printf("\n\t\t借阅成功,请于%d年%d月%d日前前来还书\n", year, mon, day);
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t如果想退出借阅，请输入x(否则按回车):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*归还*/
Status bookreturn(Book *L)
{
	int LOOP = 0;   //判断输入书号是否在书籍链表中有对应的书籍及借阅证号是否在该书籍的借阅者链表中
	char a, b;
	Book *l,*d;   //暂存书籍信息和遍历书籍链表
	Borrow *q, *p;   //暂存借阅证号和遍历该书籍的借阅者链表
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	while (LOOP != 2)
	{
		printf("\n\t\t以下是归还功能,请按照要求填写相关信息:\n");   //填写归还书号和借阅证号
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->name), 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &(l->author), 100);
		printf("\t\t|                 |\n");
		printf("\t\t|    借阅证号     |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%u", &(q->library_card));
		for (d = L->next; d != NULL; d = d->next)   //遍历书籍链表
		{
			if (strcmp(d->name, l->name) == 0 && strcmp(d->author, l->author) == 0)
				LOOP = 1;   //书籍链表中有所需要找的书号
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //书籍链表中没有所需要找的书号
		{
			printf("\n\t\t输入书名(作者)有误!\n");
			char c = getchar();
		}
		else   //书籍链表中有所需要找的书号
		{
			LOOP = 0;   //重置LOOP,进行新一轮的判断,即所输入的借阅证号是否在该书籍的借阅者链表中
			for (p = d->borrow; p != NULL; p = p->next)   //遍历该书籍的借阅者链表
			{
				if (p->library_card == q->library_card)
					LOOP = 1;   //所输入的借阅证号在该书籍所对应的借阅者链表中
				if (LOOP == 1) break;
			}
			if (LOOP == 0)   //所输入的借阅证号不在该书籍的借阅者链表中
			{
				printf("\n\t\t输入的借阅证号不正确!\n");
				char c = getchar();
			}
			else   //所输入的借阅证号在该书籍的借阅者链表中
			{
				printf("\n\t\t请确认以下的信息是否正确:\n");   //确认信息
				printf("\t\t _________________ \n");
				printf("\t\t|                 |\n");
				printf("\t\t|    借阅证号     |\n");
				printf("\t\t|_________________|");
				printf("\t%u\n", p->library_card);
				printf("\t\t|                 |\n");
				printf("\t\t|    借书日期     |\n");
				printf("\t\t|_________________|");
				printf("\t%d\n", p->borrow_date);
				printf("\t\t|                 |\n");
				printf("\t\t|    还书日期     |\n");
				printf("\t\t|_________________|");
				printf("\t%d\n", p->return_date);
				printf("\t\t|                 |\n");
				printf("\t\t|      书号       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", d->ISBN);
				printf("\t\t|                 |\n");
				printf("\t\t|      书名       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", d->name);
				printf("\t\t|                 |\n");
				printf("\t\t|      作者       |\n");
				printf("\t\t|_________________|");
				printf("\t%s\n", d->author);
				printf("\n\t\t如果以上信息有误,请输入N(继续按回车):");
				char c = getchar();
				c = getchar();
				if (c == 'n' || c == 'N')
				{
					c = getchar();
				}
				else
				{
					systemtime();   //log文件
					fprintf(fp2, "%d-%d-%d %d:%d:%d %u归还书籍%s", YEAR, MON, DAY, HOUR, MIN, SEC, p->library_card, d->ISBN);
					putc('\n', fp2);
					systemtime();   //是否逾期归还的判断
					if ((YEAR * 10000 + MON * 100 + DAY) > p->return_date)
						printf("\t\t请注意,已经超过规定日期还书!\n");
					DeleteBorrow(d->borrow, p->library_card);   //从该借阅者链表中删除这个借阅者的信息
					d->borrower--;   //借阅者数量减少
					d->current_reserves++;   //馆藏量增加
					d->able_borrow++;
					printf("\n\t\t还书成功\n");
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t如果想退出归还，请输入x(否则按回车):");
		a = getchar();
		if (a == 'x') LOOP = 2;
		if (a == '\n') continue;
		while ((b = getchar()) != '\n')
			;
	}
	return SUCCESS;
}

/*预约借书*/
Status reservebook(Book *L)
{
	int LOOP = 0,i;   //判断书籍链表中有无所要借阅的书籍和有无在当前到预约借书日期之间归还已借书籍的人
	int year, mon, day,Year,Mon,Day;   //存储预约借阅日期和当前日期
	char c, d;
	unsigned int card;   //暂存借阅证号
	char bookname[100];   //暂存书号
	char bookwriter[100];
	Book *l;   //遍历书籍链表
	Borrow *q;   //遍历所要借阅书籍的借阅者链表
	while (LOOP != 2)
	{
		printf("\n\t\t以下是预约借书功能,请按照提示填写相关信息\n");   //填写借阅证号和所要借阅的书籍的书号
		printf("\t\t _________________ \n");
		printf("\t\t|                 |\n");
		printf("\t\t|    借阅证号     |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%u", &card);
		printf("\t\t|                 |\n");
		printf("\t\t|      书名       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &bookname, 100);
		printf("\t\t|                 |\n");
		printf("\t\t|      作者       |\n");
		printf("\t\t|_________________|");
		printf("\t");
		scanf_s("%s", &bookwriter, 100);
		for (l = L->next; l != NULL; l = l->next)   //遍历书籍链表
		{
			if (strcmp(l->name, bookname) == 0 && strcmp(l->author, bookwriter) == 0)
				LOOP = 1;   //书籍链表中有该书号所对应的书籍
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //书籍链表中没有该书号所对应的书籍
		{
			printf("\n\t\t输入的书名有误!\n");
			char c = getchar();
		}
		else
		{
			LOOP = 0;   //判断有无在当前到预约借阅时间之内归还已借书籍的人
			systemtime();   //获取当前年、月、日
			Year = YEAR;
			Mon = MON;
			Day = DAY;
			printf("\n\t\t请输入你想要预约借阅的时间(3个月之内有效)\n");   //输入预约借阅时间
			printf("\t\t _________________ \n");
			printf("\t\t|                 |\n");
			printf("\t\t|       年        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &year);
			printf("\t\t|                 |\n");
			printf("\t\t|       月        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &mon);
			printf("\t\t|                 |\n");
			printf("\t\t|       日        |\n");
			printf("\t\t|_________________|");
			scanf_s("%d", &day);
			for (i = 0; i < 90; i++)   //循环90次,得到以当前时间为基准的三个月后的日期
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
			if ((year * 10000 + mon * 100 + day) <= (Year * 10000 + Mon * 100 + Day))   //所输入时间在当前时间之前
			{
				printf("\n\t\t输入时间有误!\n");
				char c = getchar();
			}
			else if ((year * 10000 + mon * 100 + day) > (YEAR * 10000 + MON * 100 + DAY))   //所输入时间在当前时间的三个月后
			{
				printf("\n\t\t请输入3个月之内的时间!\n");
				char c = getchar();
			}
			else
			{
				for (q = l->borrow; q != NULL; q = q->next)   //遍历所要借阅的书籍的借阅者链表
				{
					if (q->return_date > (YEAR * 10000 + MON * 100 + DAY) && q->return_date < (year * 10000 + mon * 100 + day))
						LOOP = 1;   //有在当前到预约借阅时间之内归还已借书籍的人
					if (LOOP == 1) break;
				}
				if (l->able_borrow == 0 && LOOP == 0)   //不可能有书籍来源
					printf("\n\t\t对不起,预约失败\n");
				else
				{
					printf("\n\t\t请确认以下的信息是否正确:\n");   //确认信息
					printf("\t\t _________________ \n");
					printf("\t\t|                 |\n");
					printf("\t\t|    借阅证号     |\n");
					printf("\t\t|_________________|");
					printf("\t%u\n", card);
					printf("\t\t|                 |\n");
					printf("\t\t|   预约借书日期  |\n");
					printf("\t\t|_________________|");
					printf("\t%d\n", year * 10000 + mon * 100 + day);
					printf("\t\t|                 |\n");
					printf("\t\t|      书号       |\n");
					printf("\t\t|_________________|");
					printf("\t%s\n", l->ISBN);
					printf("\t\t|                 |\n");
					printf("\t\t|      书名       |\n");
					printf("\t\t|_________________|");
					printf("\t%s\n", l->name);
					printf("\t\t|                 |\n");
					printf("\t\t|      作者       |\n");
					printf("\t\t|_________________|");
					printf("\t%s\n", l->author);
					printf("\n\t\t如果以上信息有误,请输入N(继续按回车):");
					char c = getchar();
					c = getchar();
					if (c == 'n' || c == 'N')
					{
						c = getchar();
					}
					else
					{
						systemtime();   //log文件
						fprintf(fp2, "%d-%d-%d %d:%d:%d %u预约借书%s", YEAR, MON, DAY, HOUR, MIN, SEC, card, l->ISBN);
						putc('\n', fp2);
						//有书籍来源
						if (l->able_borrow > 0 && LOOP == 0)
						{
							(l->able_borrow)--;
							printf("\n\t\t预约成功,请与%d年%d月%d日前来借书\n", year, mon, day);
						}
						else
						{
							(l->able_borrow)--;
							printf("\n\t\t预约成功,请与%d年%d月%d日前来借书\n", year, mon, day);
						}
					}
				}
			}
		}
		LOOP = 0;
		printf("\n\t\t如果想退出归还，请输入x(否则按回车):");
		c = getchar();
		if (c == 'x') LOOP = 2;
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}

/*查看所有书籍*/
void librarybook(Book *L)
{
	Book *l;
	printf("\n\t\t本图书馆中全部书籍如下:\n");
	for (l = L->next; l != NULL; l = l->next)
	{
		printf("\n\t\t%s", l->ISBN);
		printf("\t");
		printf("\t%s", l->name);
		printf("\t%s", l->author);
	}
	printf("\n");
}

/*全部著作*/
void allbooks(Book *L)
{
	char authorname[100];   //暂存著者名
	char c='a',d;
	int LOOP = 0;   //判断书籍链表中有无该著者的书籍
	int n = 0;   //每输出4本著作就换行输出
	Book *l;   //遍历书籍链表
	l = (Book *)malloc(sizeof(Book));
	while (c != 'x')
	{
		printf("\n\t\t你想要查找哪位著者的所有著作:");
		scanf_s("%s", authorname, 100);
		scanf_s("%c", &c, 1);
		for (l = L->next; l != NULL; l = l->next)   //遍历书籍链表
		{
			if (strcmp(l->author, authorname) == 0)
				LOOP = 1;   //书籍链表中有该著者的著作
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //书籍链表中没有该著者的著作
			printf("\n\t\t对不起,本图书馆内没有收藏该著者的著作\n");
		else   //书籍链表中有该著者的著作
		{
			systemtime();    //log文件
			fprintf(fp2, "%d-%d-%d %d:%d:%d 查看%s全部著作", YEAR, MON, DAY, HOUR, MIN, SEC, l->author);
			putc('\n', fp2);
			printf("\n\t\t这位著者的著作有:\n\t");
			for (; l != NULL; l = l->next)   //找出书籍链表中所有该著者的著作
			{
				if (strcmp(l->author, authorname) == 0)
				{
					printf("\t%s", l->name);
					n++;
				}
				if (n % 4 == 0)   //每输出4本著作就换行输出
					printf("\n\t");
			}
			printf("\n");
		}
		printf("\n\t\t如果想退出查找，请输入x(否则按回车):");
		c = getchar();
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}

/*书籍信息*/
void allinformation(Book *L)
{
	int LOOP = 0,i;   //判断书籍链表中有无所要查阅的书籍和输出最近到期的借阅者信息
	char c='a',d;
	Book *l;   //遍历书籍链表
	Borrow *q;   //输出最近到期的借阅者信息
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	char bookinf[100];   //暂存输入的书号
	while (c != 'x')
	{
		printf("\n\t\t请输入你想要查阅的书籍的书号/书名/作者:");
		scanf_s("%s", bookinf, 100);
		scanf_s("%c", &c, 1);
		for (l = L->next; l != NULL; l = l->next)   //遍历书籍链表
		{
			if (strcmp(l->ISBN, bookinf) == 0 || strcmp(l->name, bookinf) == 0 || strcmp(l->author, bookinf) == 0)
				LOOP = 1;   //找到该书号对应的书籍
			if (LOOP == 1) break;
		}
		if (LOOP == 0)   //不存在该书号对应的书籍
			printf("\n\t\t图书馆中不存在这本书\n");
		else   //找到该书号对应的书籍
		{
			systemtime();   //log文件
			fprintf(fp2, "%d-%d-%d %d:%d:%d 查看书籍%s信息", YEAR, MON, DAY, HOUR, MIN, SEC, bookinf);
			putc('\n', fp2);
			for (; l != NULL; l = l->next)
			{
				if (strcmp(l->ISBN, bookinf) == 0 || strcmp(l->name, bookinf) == 0 || strcmp(l->author, bookinf) == 0)
				{
					q = l->borrow;
					if (q->next == NULL)   //该书籍没有借阅者,则只输出书籍信息
					{
						printf("\t\t _________________ \n");
						printf("\t\t|                 |\n");
						printf("\t\t|      书号       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->ISBN);
						printf("\t\t|                 |\n");
						printf("\t\t|      书名       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->name);
						printf("\t\t|                 |\n");
						printf("\t\t|      作者       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->author);
						printf("\t\t|                 |\n");
						printf("\t\t|     可借量      |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->able_borrow);
						printf("\t\t|                 |\n");
						printf("\t\t|     现存量      |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->current_reserves);
						printf("\t\t|                 |\n");
						printf("\t\t|    总库存量     |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->total_reserves);
					}
					else   //该书籍有借阅者
					{
						for (q = l->borrow, i = 1; i <= 1; i++, q = q->next)   //找到最近到期的借阅者信息,并将书籍信息和该借阅者信息一并输出
							;
						printf("\t\t _________________ \n");
						printf("\t\t|                 |\n");
						printf("\t\t|      书号       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->ISBN);
						printf("\t\t|                 |\n");
						printf("\t\t|      书名       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->name);
						printf("\t\t|                 |\n");
						printf("\t\t|      作者       |\n");
						printf("\t\t|_________________|");
						printf("\t%s\n", l->author);
						printf("\t\t|                 |\n");
						printf("\t\t|     可借量      |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->able_borrow);
						printf("\t\t|                 |\n");
						printf("\t\t|     现存量      |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->current_reserves);
						printf("\t\t|                 |\n");
						printf("\t\t|    总库存量     |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", l->total_reserves);
						printf("\t\t|                 |\n");
						printf("\t\t|    借阅证号     |\n");
						printf("\t\t|_________________|");
						printf("\t%u\n", q->library_card);
						printf("\t\t|                 |\n");
						printf("\t\t|    借书日期     |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", q->borrow_date);
						printf("\t\t|                 |\n");
						printf("\t\t|    还书日期     |\n");
						printf("\t\t|_________________|");
						printf("\t%d\n", q->return_date);
					}
					printf("\n");
				}
			}
		}
		printf("\n\t\t如果想退出查找，请输入x(否则按回车):");
		c = getchar();
		if (c == '\n') continue;
		while ((d = getchar()) != '\n')
			;
	}
}
