#include <stdio.h>
#include "library.h"

Book *L;   //书本
Borrow *Q;   //借阅者
FILE *fp1, *fp2;   //书籍及借阅者、log

int main()
{
	Init();   //初始化
	choose();   //相应选项导向不同操作
	Finish();   //收尾
	return 0;
}

/*以输入的信息为选项，导向不同的功能*/
void choose()
{
	char c;
	c = ROM();
	while (c != 'x')
	{
		switch (c)
		{
		case '1':
			inrepository(L);   //采编入库
			break;
		case '2':
			outrepository(L);   //清除出库
			break;
		case '3':
			bookInfor();   //书籍信息
			break;
		case '4':
			bookborrow(L);   //借阅
			break;
		case '5':
			bookreturn(L);   //归还
			break;
		case '6':
			reservebook(L);   //预约借书
			break;
		default:
			warn();   //非法输入
		}
		c = ROM();
	}
}

/*初始化一个存储书籍信息的链表*/
void Init()
{
	int finish;   //判断是否读到文档结尾
	int i = 0;   //在刚开始读文档的时候回到文档开头
	errno_t err;   //打开文件
	Book *l;   //得到新的书籍节点
	Borrow *q;   //得到新的借阅者节点
	L = (Book *)malloc(sizeof(Book));   //书本
	l = (Book *)malloc(sizeof(Book));
	q = (Borrow *)malloc(sizeof(Borrow));
	if (L == NULL)
		printf("内存空间不足!");   //内存不足
	InitBook(L);   //初始化存储书籍信息的链表
	err = fopen_s(&fp1, "library", "r+");   //打开书籍及借阅者文档
	if (err != 0)
		printf("Can't open \"library\" file.");   //打开失败
	err = fopen_s(&fp2, "log", "a");   //打开log文档
	if (err != 0)
		printf("Can't open \"log\" file.");   //打开失败
	finish = getc(fp1);   //判断是否读到文档结尾
	while (finish != EOF)
	{
		int count;   //存入的借阅者数量
		Borrow *p;   //得到新的可以插入的借阅者节点
		if (i == 0) rewind(fp1);
		if (getc(fp1) == '$')   //新的书籍节点开始的标志
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
			InsertBook(L, l);   //插入新的书籍节点
		}
		l = (Book *)malloc(sizeof(Book));
		i++;
		finish = getc(fp1);
	}
	fclose(fp1);   //关闭书籍及借阅者文档
}

/*得到输入的选项以执行对应操作,同时发现非法输入*/
char ROM()
{
	int i = 0;   //记录输入字符串长度
	char c, d;   //得到所要字符，并清除多余字符
	while (1)   //直到得到单个字符才退出循环
	{
		message();
		remind();   //提示信息
		c = getchar();   //获取字符
		while ((d = getchar()) != '\n')
			i++;   //清除多余字符并记录字符串长度
		if (i == 0) break;   //只有为1个字符时才进行判断
		else
			warn();   //警告
		i = 0;   //i重新赋值
	}
	return c;
}

void Finish()
{
	Book *l;   //读取书籍信息
	Borrow *q;   //读取借阅者信息
	errno_t err;   //打开文件
	err = fopen_s(&fp1, "library", "w");   //打开书籍及借阅者文档
	if (err != 0)
		printf("Can't open \"library\" file.");    //打开失败
	int i;    //循环输入所有借阅者信息
	for (l = L->next; l != NULL; l = l->next)
	{
		fprintf(fp1, "%c", '$');   //新的书籍节点开始的标志
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
		fprintf(fp1, "%c", '\n');   //下一行接着输入
	}
	fclose(fp1);   //关闭书籍及借阅者文档
	fclose(fp2);   //关闭log文档
}