#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <conio.h>
#include "../head/linwenchen.h"
#include "../head/NoteManagementSystem.h"
//����ȫ�ֱ�������
extern char currentpath[];
extern char rootpath[];


Status DeleteFOFNode(CurFloder *current, char *name)//ɾ�����
{
	FOF *front = current->F;
	if(!strcmp(front->name,name))//Ҫɾ������ͷ�ڵ�
	{
		current->F = current->F->next;
		//����б�ǩ,ɾ��
		if(front->taghead)
		{
			Tag *temp = front->taghead;
			Tag *ne = temp->next;
			while(temp)
			{
				free(temp);
				temp = ne;
				if(temp == NULL)break;
				ne = ne->next;
			}
		}
		free(front);
	}
	else
	{
		while(strcmp((front->next->name),name))
			front = front->next;
		FOF *temp = front->next;
		//��Ŀ��ڵ��Ƴ�����
		front->next = front->next->next;
		if(temp->taghead)
		{
			Tag *st = temp->taghead;//��һ��
			Tag *ne = st->next;//��һ��
			while(st)
			{
				free(st);
				st = ne;
				if(st == NULL)break;
				ne = ne->next;
			}
		}
		free(temp);
	}
	return SUCCESS;
}
//�ڵ�ǰĿ¼��
void DeleteFOF(CurFloder *current, char *s)			//ɾ���ļ����ļ���
{
	int index = 0;
	int flag = 0;//floder
	int len = strlen(s);
	char copy[400]; 
	char del[400] = {"del "};//ɾ���ļ�
	char rd[400] = {"rd /s "};//ɾ���ļ���
	char path[400] = {'\0'};

	strcat(path,currentpath);//��ǰ·��
	strcat(path,"\\");
	for(int i = 0;i<len;i++)
	{
		if(s[i] == '\\')
			index = i+1;//'\'���������
		if(s[i] == '.')
			flag = 1;//file
	}
	strcat(path,s+index);//�ļ������ļ�������
	strcpy(copy,path);//���ڼ�¼���β��� 
	if(RoteExistence(path,flag))
	{
		if(flag)
			strcat(del,path);
		else
			strcat(rd,path);
		FOF *temp = current->F;
		if(!strcmp(s+index,temp->name))//��ͷ�ڵ�
		{
			int a;
			if(flag)a = system(del);
			else a = system(rd);
			if(!a)//�����ɾ���Ͳ�����
			{
				current->F = current->F->next;
				free(temp);
			}
		}
		else
		{
			while(temp->next)
			{
				if(!strcmp(s+index,temp->next->name))
				{
					int a;
					if(flag)a = system(del);
					else a = system(rd);
					if(a)break;//�����ɾ���Ͳ�����
					FOF *delelenode = temp->next;
					temp->next = temp->next->next;
					free(delelenode);
					break;
				}
				temp = temp->next;
			}
		}
		InputLog("ɾ�����ļ�/�ļ��е�·����", copy,"    ", "·������ . ��Ϊ���ļ����ļ�");
		Input_Save(current,currentpath);
	}
	else
	{
		if(flag)printf("\nfile \"%s\" not exist!\n",s+index);
		else printf("\nfloder \"%s\" not exist!\n",s+index);
	}
}

void MakeFOF(CurFloder *current, char *s)			//�����ļ����ļ���
{
	int index = 0;
	int flag = 0;//floder
	int len = strlen(s);
	char copy[400]; 
	char md[400] = {"md "};//�����ļ������ļ���
	char path[400] = {'\0'};
	strcat(path,currentpath);//��ǰ·��
	strcat(path,"\\");
	for(int i = 0;i<len;i++)
	{
		if(s[i] == ' ' || s[i] == '\\' || s[i] == '/' || s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == '"' || s[i] == '*' || s[i] == '?' || s[i] == ':')
		{
			printf("\n�����ļ������Ƿ��ַ�����������!\n");
			return;
		}
		if(s[i] == '\\')
			index = i+1;//'\'���������
		if(s[i] == '.' )
			flag = 1;//file
	}
	strcat(path,s+index);//�ļ������ļ�������
	strcpy(copy, path);
	strcat(md,path);
	//�½����
	FOF e;
	e.flag = flag?1:2;
	e.num = 0;
	e.taghead = NULL;
	e.next = NULL;
	strcpy(e.name,s+index);

	if(RoteExistence(path,flag))//�ļ������ļ����Ѵ���
	{
		if(!flag)//�ļ���
		{
			printf("have the same name folder\n");
			char rd[150] = "rd /s ";//ɾ���ļ���
			strcat(rd,path);
			int x = system(rd);
			//�ɹ�ɾ������0
			if(x)return;
			//���ɾ���ļ���ִ�����²���
			DeleteFOFNode(current,s+index);//ɾ�����
			AddFOFNode(current,e);//���ӽ��
			system(md);//�����ļ���
			strcat(path,"\\_save.txt");
			FILE *temp = fopen(path,"w");//����_save.txt�ļ�
			fclose(temp);
			printf("cover successed!\n");
		}
		else
		{
			printf("have the same name file\n");
			printf("do you want to cover it? y/n?");
			char ch;
			if((ch = getchar()) && (ch == 'y' || ch == 'Y'))
			{
				FILE *temp = fopen(path,"w");
				fclose(temp);
				DeleteFOFNode(current,s+index);//ɾ�����
				AddFOFNode(current,e);//���ӽ��
			}
			else if(ch == 'n' || ch == 'N')return;
			else
			{
				printf("��Ч���룡\n");
				return;
			}
		}
	}
	else
	{
		if(flag)//�ļ�
		{
			FILE *temp = fopen(path,"w");
			fclose(temp);
			AddFOFNode(current,e);
		}
		else
		{
			system(md);
			strcat(path,"\\_save.txt");
			FILE *temp = fopen(path,"w");
			fclose(temp);
			AddFOFNode(current,e);
		}
	}
	if(flag == 1)
	{
		InputLog("�������ļ���·����", copy, "  ", "  ");
		printf("\n�����ļ��ɹ���"); 
	}	
	else
	{
		InputLog("�������ļ��е�·����", copy, "  ", "  ");
		printf("\n�����ļ��гɹ���");
	}	
	Input_Save(current,currentpath);//���浽��ǰĿ¼��_save.txt�ļ�
}

Status AddFOFNode(CurFloder *current, FOF e)		//���ӽ��
{
	FOF *temp = (FOF *)malloc(sizeof(FOF));
	if(temp == NULL)return ERRORS;
	temp->flag = e.flag;
	temp->num = e.num;
	temp->taghead = NULL;//��ʼʱû�б�ǩ
	strcpy((temp->name),e.name);
	temp->next = NULL;
	if(current->F == NULL)
		current->F = temp;
	else
	{
		FOF *front = current->F;
		while(front->next)
			front = front->next;
		front->next = temp;
	}
	return SUCCESS;
}

void LsGrep(char *path,char *Find)					//����
{
	CurFloder Now;//��������
	Read_Save(&Now,path);
	FOF *temp = Now.F;
	while(temp)
	{
		PrintGrep(temp,path,Find);
		//������ļ��У��ݹ�����
		if(temp->flag == 2)
		{
			char nextpath[150] = {'\0'};
			strcpy(nextpath,path);
			strcat(nextpath,"\\");
			strcat(nextpath,temp->name);
			LsGrep(nextpath,Find);
		}
		temp = temp->next;//��һ���ļ�
	}
	DestroyFof(&Now);//ɾ������
}

void PrintGrep(FOF *current, char *path, char *Find)//��ӡ�ļ��������ļ�������
{

	if(Checkstr(current->name,Find))
	{
		char temp[150] = {'\0'};
		strcat(temp,path);
		strcat(temp,"\\");
		strcat(temp,current->name);
		printf("\t%s\n",temp);
	}
}


int Checkstr(const char *s,const char *t)			//�ж�s�ַ����Ƿ����t�ַ��� �Ƿ���1���򷵻�0
{
	int lens = strlen(s);
	int lent = strlen(t);
	if(lent <= 0)return ERRORS;
	for(int i = 0;i<lens;i++)
	{
		if(s[i] == t[0])//ͷ�ַ���ͬ������ȶ�
		{
			int flag = 0;
			int j = 0;
			while(j+i<lens && j<lent)//
			{
				if(s[j+i] != t[j])flag = 1;
				if(flag)break;
				j++;
			}
			if(flag)continue;
			return SUCCESS;
		}
	}
	return ERRORS;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x)
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
}

void toxy(int x, int y)
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}

void MenuAdmin(All_User *L)			//��½�˵�
{
	do
	{
		system("cls");
		HideCursor();
		color(3);
		char t;
		toxy(49,10);
		printf("�ʼǹ���ϵͳ");
		toxy(50,13);
		printf("1.�û���½");
		toxy(50,15);
		printf("2.�˳�ϵͳ");
		t=getch();
		fflush(stdin);
		switch(t)
		{
			case '1':
				{
					UserLogin(L);
					break;
				}
			case '2':
				{
					return;
				}
			default :break;
		}
	}while(1);
}

void UserLogin(All_User *L)			//��¼�˻�
{
	fflush(stdin);
	User *user = *L;
	system("cls");
	char name[100] = {'\0'};
	char password[20] = {'\0'};
	char root[200] = {'\0'};
	User newuser;
	CONSOLE_CURSOR_INFO cursor_info = {1, 1};//�������ʾ 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	*(newuser.root) = '\0';
	if(user == NULL)//���Ŀǰû���û�
	{

		printf("������λ�û�,����������û���(���Ȳ�Ҫ����80�ַ�)��");
		fgets(name,80,stdin);
		int len = strlen(name);
		if(len <= 1)
		{
			printf("�������\n");
			printf("�����������...\n");
			getch();
			fflush(stdin);
			return;
		}
		name[len-1] = '\0';//fgets���ں���ӿո�
		SetPassword(password);
		SetRoot(newuser.root,user);
	}
	else
	{
		printf("�����������û���(���Ȳ�Ҫ����80�ַ�)��");
		fgets(name,80,stdin);
		int len = strlen(name);
		if(len <= 1)
		{
			printf("�������\n");
			printf("�����������...\n");
			getch();
			fflush(stdin);
			return;
		}
		name[len-1] = '\0';//fgets���ں���ӿո�
		User *temp = user;
		while(temp)
		{
			if(!strcmp(name,temp->name))
			{
				printf("�������������룺");
				fgets(password,20,stdin);
				int len1 = strlen(password);
				password[len1-1] = '\0';
				if(!strcmp(temp->password,password))//������ȷ
				{
					SecondMain(*temp);
					return;
				}
				else
				{
					printf("������������µ�½!");
					printf("�����������...\n");
					getch();
					fflush(stdin);
					return;
				}
			}
			temp = temp->next;
		}
		SetPassword(password);
		SetRoot(newuser.root,user);
	}
	//���û����
	strcpy(newuser.name,name);
	strcpy(newuser.password,password);
	//����·��
	strcpy(root,rootpath);
	strcat(root,"\\");
	strcat(root,newuser.root);
	//���
	printf("%s %s %s\n",name,password,root);
	getc(stdin);
	//���������㡢�����ļ��������浽user�ļ�
	newuser.next =NULL;
	AddUser(L,newuser);
	SaveUser(*L);
	_mkdir(root);
	//�����ļ�_save.txt
	char t[150] = {'\0'};
	strcpy(t,root);
	strcat(t,"\\_save.txt");
	FILE *file = fopen(t,"w");
	fclose(file);
	SecondMain(newuser);
	fflush(stdin);

}

All_User InitSystem(void)			//��ʼ��
{
	FILE *temp = fopen("_save.txt","w");
	fclose(temp);
	FILE *user = fopen("user","ab+");
	if(user == NULL)
	{
		printf("Can't open \"user\"\n");
		getchar();
		exit(1);
	}
	char ch = getc(user);
	if(feof(user))//����Ƿ�ǿ�
	{
		fclose(user);
		return NULL;
	}
	else ungetc(ch,user);
	User *head = NULL,*current,*p;
	int len = sizeof(User);
	while((ch = fgetc(user)) && (feof(user) == 0))
	{
		ungetc(ch,user);
		//���ڴ�����һ�οռ�
		p=(User *)malloc(len);
		//��user��ָ����ļ��е����ݸ���p
		fread(p,len,1,user);
		if(head == NULL)
			head = current = p;
		else
		{
			current->next = p;
			current = p;
		}
	}
	fclose(user);
	return head;
}

void SetPassword(char *password)	//��������
{
	printf("\n����������(��Ҫ����16λ)(֧�����ֺ���ĸ���)��");
	char ch;
	char s[20];
	int len = 0;
	if((ch = getchar()) && ch != '\n')ungetc(ch,stdin);
	while((ch = getchar()) && ch != '\n' && len <= 16)
	{
		if(ch >= '0' && ch <= '9')
			s[len++] = ch;
		else if(ch >= 'a' && ch <= 'z')
			s[len++] = ch;
		else if(ch >= 'A' && ch <= 'Z')
			s[len++] = ch;
		else
		{
			printf("���������������������룡");
			fflush(stdin);
			SetPassword(password);
			return;
		}
	}
	s[len] = '\0';
	strcpy(password,s);
}

void AddUser(All_User *user,User e)	//�����û�
{
	User *current = *user;
	if(current == NULL)//û���û����
	{
		User *temp = (User *)malloc(sizeof(User));
		*temp = e;
		*user = temp;
	}
	else
	{
		while(current->next)
			current = current->next;
		User *temp = (User *)malloc(sizeof(User));
		*temp = e;
		current->next = temp;
	}
}

void SaveUser(All_User L)			//�����û���Ϣ
{
	FILE *user = fopen("user","wb");
	if(user == NULL)
	{
		printf("Can't open \"user\"\n");
		getchar();
		exit(1);
	}
	while(L)
	{
		fwrite(L,sizeof(User),1,user);
		L = L->next;
	}
	fclose(user);
}

void SetRoot(char *root,All_User L)	//����·��
{
	char buf[20];
	printf("��������Ҫ�����Ĺ�����������(����·��,������10���ַ�����):");
	fgets(buf,10,stdin);
	fflush(stdin);
	int len = strlen(buf);
	if(len <= 1)
	{
		SetRoot(root,L);
		return;
	}
	else if(CheckRoot(buf,len))//�Ϸ�����
	{

		buf[len-1] = '\0';
		User *temp = L;
		while(temp)
		{
			if(!strcmp(buf,temp->root))
			{
				printf("�������Ѵ��ڣ�����������");
				SetRoot(root,L);
				return;
			}
			temp = temp->next;
		}
		strcpy(root,buf);
		return;
	}
	else
	{
		SetRoot(root,L);
		return;
	}
}

int CheckRoot(char *buf,int len)	//�������
{
	for(int i = 0;i<len;i++)
	{
		if(buf[i] == '.' || buf[i] == ' ' || buf[i] == '\\' || buf[i] == '/' || buf[i] == '<' || buf[i] == '>' || buf[i] == '|' || buf[i] == '"' || buf[i] == '*' || buf[i] == '?' || buf[i] == ':')
		{
			printf("\n�����ļ������Ƿ��ַ�����������!\n");
			return ERRORS;
		}
	}
	return SUCCESS;
}
