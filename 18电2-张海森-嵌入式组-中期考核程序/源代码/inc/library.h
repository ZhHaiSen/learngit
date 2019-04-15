/**************************************************************
*	Struct Define Section
**************************************************************/

// define struct of linked lists
typedef struct Book   //书本
{ 
	char ISBN[50];   //书号
	char name[100];   //书名
	char author[100];   //作者
	struct Borrow *borrow;   //指向该书借阅者链表的指针
	int able_borrow;   //可借量
	int current_reserves;   //现存量
	int total_reserves;   //库存总量
	int borrower;   //借阅者数量
  	struct Book *next;   //指向下一本书的指针
} Book;

typedef struct Borrower   //借阅者
{
	unsigned int library_card;   //借阅证号
	int borrow_date;   //借书日期
	int return_date;   //还书日期
	struct Borrower *next;   //指向下一位借阅者的指针
}Borrow;

// define Status
typedef enum Status { 
	ERROR,   //失败
	SUCCESS   //成功
} Status;

/**********************************************************
*      function statement
**********************************************************/
Status InitBook(Book *L);
Status InitBorrow(Borrow *Q);
Status DestroyBook(Book *L);
Status DestroyBorrow(Borrow *Q);
Status InsertBook(Book *L, Book *l);
Status InsertBorrow(Borrow *Q,Borrow *q);
Status DeleteBook(Book *L, char x[]);
Status DeleteBorrow(Borrow *Q, unsigned int x);
Status inrepository(Book *L);
Status outrepository(Book *L);
Status bookInfor();
Status bookborrow(Book *L);
Status bookreturn(Book *L);
Status reservebook(Book *L);
void allbooks(Book *L);
void allinformation(Book *L);
void choose();
void Init();
char ROM();
void message();
void Welcome();
void menu();
void remind();
void warn();
void time_print();
void systemtime();
void bookinformation();
void Finish();