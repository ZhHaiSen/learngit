#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <conio.h>
#include "../head/linwenchen.h"
#include "../head/NoteManagementSystem.h"
//引用全局变量声明
extern char currentpath[];
extern char rootpath[];


Status DeleteFOFNode(CurFloder *current, char *name)//删除结点
{
	FOF *front = current->F;
	if(!strcmp(front->name,name))//要删除的是头节点
	{
		current->F = current->F->next;
		//如果有标签,删除
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
		//将目标节点移除链表
		front->next = front->next->next;
		if(temp->taghead)
		{
			Tag *st = temp->taghead;//第一个
			Tag *ne = st->next;//下一个
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
//在当前目录下
void DeleteFOF(CurFloder *current, char *s)			//删除文件或文件夹
{
	int index = 0;
	int flag = 0;//floder
	int len = strlen(s);
	char copy[400]; 
	char del[400] = {"del "};//删除文件
	char rd[400] = {"rd /s "};//删除文件夹
	char path[400] = {'\0'};

	strcat(path,currentpath);//当前路径
	strcat(path,"\\");
	for(int i = 0;i<len;i++)
	{
		if(s[i] == '\\')
			index = i+1;//'\'后面的名字
		if(s[i] == '.')
			flag = 1;//file
	}
	strcat(path,s+index);//文件或者文件夹名字
	strcpy(copy,path);//用于记录本次操作 
	if(RoteExistence(path,flag))
	{
		if(flag)
			strcat(del,path);
		else
			strcat(rd,path);
		FOF *temp = current->F;
		if(!strcmp(s+index,temp->name))//是头节点
		{
			int a;
			if(flag)a = system(del);
			else a = system(rd);
			if(!a)//如果不删除就不操作
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
					if(a)break;//如果不删除就不操作
					FOF *delelenode = temp->next;
					temp->next = temp->next->next;
					free(delelenode);
					break;
				}
				temp = temp->next;
			}
		}
		InputLog("删除的文件/文件夹的路径：", copy,"    ", "路径中有 . 则为非文件夹文件");
		Input_Save(current,currentpath);
	}
	else
	{
		if(flag)printf("\nfile \"%s\" not exist!\n",s+index);
		else printf("\nfloder \"%s\" not exist!\n",s+index);
	}
}

void MakeFOF(CurFloder *current, char *s)			//创建文件或文件夹
{
	int index = 0;
	int flag = 0;//floder
	int len = strlen(s);
	char copy[400]; 
	char md[400] = {"md "};//创建文件或者文件夹
	char path[400] = {'\0'};
	strcat(path,currentpath);//当前路径
	strcat(path,"\\");
	for(int i = 0;i<len;i++)
	{
		if(s[i] == ' ' || s[i] == '\\' || s[i] == '/' || s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == '"' || s[i] == '*' || s[i] == '?' || s[i] == ':')
		{
			printf("\n输入文件名含非法字符！重新输入!\n");
			return;
		}
		if(s[i] == '\\')
			index = i+1;//'\'后面的名字
		if(s[i] == '.' )
			flag = 1;//file
	}
	strcat(path,s+index);//文件或者文件夹名字
	strcpy(copy, path);
	strcat(md,path);
	//新建结点
	FOF e;
	e.flag = flag?1:2;
	e.num = 0;
	e.taghead = NULL;
	e.next = NULL;
	strcpy(e.name,s+index);

	if(RoteExistence(path,flag))//文件或者文件夹已存在
	{
		if(!flag)//文件夹
		{
			printf("have the same name folder\n");
			char rd[150] = "rd /s ";//删除文件夹
			strcat(rd,path);
			int x = system(rd);
			//成功删除返回0
			if(x)return;
			//如果删除文件夹执行以下操作
			DeleteFOFNode(current,s+index);//删除结点
			AddFOFNode(current,e);//增加结点
			system(md);//创建文件夹
			strcat(path,"\\_save.txt");
			FILE *temp = fopen(path,"w");//创建_save.txt文件
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
				DeleteFOFNode(current,s+index);//删除结点
				AddFOFNode(current,e);//增加结点
			}
			else if(ch == 'n' || ch == 'N')return;
			else
			{
				printf("无效输入！\n");
				return;
			}
		}
	}
	else
	{
		if(flag)//文件
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
		InputLog("创建的文件的路径：", copy, "  ", "  ");
		printf("\n创建文件成功！"); 
	}	
	else
	{
		InputLog("创建的文件夹的路径：", copy, "  ", "  ");
		printf("\n创建文件夹成功！");
	}	
	Input_Save(current,currentpath);//保存到当前目录的_save.txt文件
}

Status AddFOFNode(CurFloder *current, FOF e)		//增加结点
{
	FOF *temp = (FOF *)malloc(sizeof(FOF));
	if(temp == NULL)return ERRORS;
	temp->flag = e.flag;
	temp->num = e.num;
	temp->taghead = NULL;//初始时没有标签
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

void LsGrep(char *path,char *Find)					//搜索
{
	CurFloder Now;//创建链表
	Read_Save(&Now,path);
	FOF *temp = Now.F;
	while(temp)
	{
		PrintGrep(temp,path,Find);
		//如果是文件夹，递归搜索
		if(temp->flag == 2)
		{
			char nextpath[150] = {'\0'};
			strcpy(nextpath,path);
			strcat(nextpath,"\\");
			strcat(nextpath,temp->name);
			LsGrep(nextpath,Find);
		}
		temp = temp->next;//下一个文件
	}
	DestroyFof(&Now);//删除链表
}

void PrintGrep(FOF *current, char *path, char *Find)//打印文件名或者文件夹名字
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


int Checkstr(const char *s,const char *t)			//判断s字符串是否包含t字符串 是返回1否则返回0
{
	int lens = strlen(s);
	int lent = strlen(t);
	if(lent <= 0)return ERRORS;
	for(int i = 0;i<lens;i++)
	{
		if(s[i] == t[0])//头字符相同，进入比对
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

void MenuAdmin(All_User *L)			//登陆菜单
{
	do
	{
		system("cls");
		HideCursor();
		color(3);
		char t;
		toxy(49,10);
		printf("笔记管理系统");
		toxy(50,13);
		printf("1.用户登陆");
		toxy(50,15);
		printf("2.退出系统");
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

void UserLogin(All_User *L)			//登录账户
{
	fflush(stdin);
	User *user = *L;
	system("cls");
	char name[100] = {'\0'};
	char password[20] = {'\0'};
	char root[200] = {'\0'};
	User newuser;
	CONSOLE_CURSOR_INFO cursor_info = {1, 1};//将光标显示 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	*(newuser.root) = '\0';
	if(user == NULL)//如果目前没有用户
	{

		printf("你是首位用户,请输入你的用户名(长度不要超过80字符)：");
		fgets(name,80,stdin);
		int len = strlen(name);
		if(len <= 1)
		{
			printf("输入错误！\n");
			printf("按任意键返回...\n");
			getch();
			fflush(stdin);
			return;
		}
		name[len-1] = '\0';//fgets会在后面加空格
		SetPassword(password);
		SetRoot(newuser.root,user);
	}
	else
	{
		printf("请输入您的用户名(长度不要超过80字符)：");
		fgets(name,80,stdin);
		int len = strlen(name);
		if(len <= 1)
		{
			printf("输入错误！\n");
			printf("按任意键返回...\n");
			getch();
			fflush(stdin);
			return;
		}
		name[len-1] = '\0';//fgets会在后面加空格
		User *temp = user;
		while(temp)
		{
			if(!strcmp(name,temp->name))
			{
				printf("请输入您的密码：");
				fgets(password,20,stdin);
				int len1 = strlen(password);
				password[len1-1] = '\0';
				if(!strcmp(temp->password,password))//密码正确
				{
					SecondMain(*temp);
					return;
				}
				else
				{
					printf("密码错误！请重新登陆!");
					printf("按任意键返回...\n");
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
	//新用户结点
	strcpy(newuser.name,name);
	strcpy(newuser.password,password);
	//创建路径
	strcpy(root,rootpath);
	strcat(root,"\\");
	strcat(root,newuser.root);
	//输出
	printf("%s %s %s\n",name,password,root);
	getc(stdin);
	//创建链表结点、创建文件、并保存到user文件
	newuser.next =NULL;
	AddUser(L,newuser);
	SaveUser(*L);
	_mkdir(root);
	//创建文件_save.txt
	char t[150] = {'\0'};
	strcpy(t,root);
	strcat(t,"\\_save.txt");
	FILE *file = fopen(t,"w");
	fclose(file);
	SecondMain(newuser);
	fflush(stdin);

}

All_User InitSystem(void)			//初始化
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
	if(feof(user))//检查是否非空
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
		//向内存申请一段空间
		p=(User *)malloc(len);
		//将user所指向的文件中的内容赋给p
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

void SetPassword(char *password)	//设置密码
{
	printf("\n请输入密码(不要超过16位)(支持数字和字母混合)：");
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
			printf("您的输入有误！请重新输入！");
			fflush(stdin);
			SetPassword(password);
			return;
		}
	}
	s[len] = '\0';
	strcpy(password,s);
}

void AddUser(All_User *user,User e)	//增加用户
{
	User *current = *user;
	if(current == NULL)//没有用户结点
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

void SaveUser(All_User L)			//保存用户信息
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

void SetRoot(char *root,All_User L)	//设置路径
{
	char buf[20];
	printf("请输入你要创建的工作区的名字(无需路径,不超过10个字符长度):");
	fgets(buf,10,stdin);
	fflush(stdin);
	int len = strlen(buf);
	if(len <= 1)
	{
		SetRoot(root,L);
		return;
	}
	else if(CheckRoot(buf,len))//合法命名
	{

		buf[len-1] = '\0';
		User *temp = L;
		while(temp)
		{
			if(!strcmp(buf,temp->root))
			{
				printf("工作区已存在！请重命名！");
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

int CheckRoot(char *buf,int len)	//检查命名
{
	for(int i = 0;i<len;i++)
	{
		if(buf[i] == '.' || buf[i] == ' ' || buf[i] == '\\' || buf[i] == '/' || buf[i] == '<' || buf[i] == '>' || buf[i] == '|' || buf[i] == '"' || buf[i] == '*' || buf[i] == '?' || buf[i] == ':')
		{
			printf("\n输入文件名含非法字符！重新输入!\n");
			return ERRORS;
		}
	}
	return SUCCESS;
}
