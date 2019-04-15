/**************************************************************
*	Struct Define Section
**************************************************************/

// define struct of linked lists
typedef struct Book   //�鱾
{ 
	char ISBN[50];   //���
	char name[100];   //����
	char author[100];   //����
	struct Borrow *borrow;   //ָ���������������ָ��
	int able_borrow;   //�ɽ���
	int current_reserves;   //�ִ���
	int total_reserves;   //�������
	int borrower;   //����������
  	struct Book *next;   //ָ����һ�����ָ��
} Book;

typedef struct Borrower   //������
{
	unsigned int library_card;   //����֤��
	int borrow_date;   //��������
	int return_date;   //��������
	struct Borrower *next;   //ָ����һλ�����ߵ�ָ��
}Borrow;

// define Status
typedef enum Status { 
	ERROR,   //ʧ��
	SUCCESS   //�ɹ�
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