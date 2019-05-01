#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../head/NoteManagementSystem.h"
#include "../head/chenyu.h" 

extern char rootpath[];//存储用户路径         CurFloder *currentfile
extern char currentpath[];//存储当前路径

/**
 *  @name        : Status CdReturn(CurFloder *head)
 *  @description : 返回上一级 
 *  @param       : CurFloder *head  
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *  @return      : 
 */	
 Status CdReturn(CurFloder *head)
 {
 	int num, savenum;
	if(strcmp(rootpath, currentpath) == 0)//判断是否为根目录 
	{
		printf("\n当前为根目录！无法返回！"); 
		return ERRORS;
	}
	DestroyFof(head);//销毁上一次的链表 
	for(num = 0; currentpath[num] != '\0'; num++)
	{
		if(currentpath[num] == '\\')
			savenum = num;
	}
	currentpath[savenum] = '\0';
	Read_Save(head, currentpath);
	return SUCCESS;
 }
 
 /**
 *  @name        :  Status CdSwitch(CurFloder *head, char *targetpath)
 *  @description :  跳转到目标路径 
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *                 char *targetpath    目录的路径 
 *  @return      : 
 */	
Status CdSwitch(CurFloder *head, char *targetpath)
 {
	int i, j;
	int length;
	char copypath[400];
	for(i = 0; targetpath[i] != '\0'; i++);
	if(targetpath[i - 1] == '\\')
	{
		printf("\n路径输入错误！切换路径失败！");
		return ERROR; 
	} 
	if(targetpath[1] != ':')
	{
		if(targetpath[0] != '\\')
		{
			strcpy(copypath, currentpath);
			strcat(copypath, "\\");
			strcat(copypath, targetpath);
			targetpath = copypath;
		}
		else
		{
			strcpy(copypath, rootpath);
			for(i = 0; copypath[i] != '\0'; i++)//找到最后一个斜杆 
			{
				if(copypath[i] == '\\')
					j = i;
			}
			copypath[j] = '\0';
			strcat(copypath, targetpath);
			targetpath = copypath;
		}
	}
	else
	{
		length = strlen(rootpath);
		for(i = 0; i < length; i++)//判断目标路径是否在用户目录内 
		{
	 		if(targetpath[i] != rootpath[i])
	 		{
	 			printf("\n路径超出用户可操控范围！切换路径失败！");
				return ERRORS;
			}
		}
	}
	if(RoteExistence(targetpath, 0) == ERRORS)
	{
		printf("\n路径输入错误！切换路径失败！");
		return ERRORS;
	}
	for(i = 0; targetpath[i] != '\0'; i++);
	if(targetpath[i - 3] == '\\' && targetpath[i - 1] == '.' && targetpath[i - 2] == '.')
	{
		printf("\n路径输入错误！切换路径失败！");
		return ERRORS;
	}
	if(targetpath[i - 2] == '\\' && targetpath[i - 1] == '.')
	{
		printf("\n路径输入错误！切换路径失败！");
		return ERRORS;
	}
	DestroyFof(head);//销毁上一次的链表
	strcpy(currentpath, targetpath);//改变当前路径 
	Read_Save(head, currentpath);
	return SUCCESS;
 }
 
 /**
 *  @name        : void SearchTag(const char *tagname, const char *searchpath)
 *  @description : 根据标签名字查找所有该用户的符合标签的文件 （可模糊查找） 
 *  @param       : const char *tagname  标签名 
 *                 const char *searchpath  查找的路径 
 *  @return      : 
 */	
void SearchTag(const char *tagname, const char *searchpath, int *sum)
{
	char copypath[400];
	char a[] = "\\";
	int i, j, length;
	CurFloder *head;
	Tag *tagnext;
	FOF *fofnext;
	head = (CurFloder *)malloc(sizeof(CurFloder));
	Read_Save(head, searchpath);
	fofnext = head->F;
	while(fofnext != NULL)
	{
		tagnext = fofnext->taghead;
		while(tagnext != NULL)
		{
			j = 0;
			length = strlen(tagname);
			while((tagnext->info)[j + length - 1] != '\0' && (tagnext->info)[j] != '\0') 
			{
				i = 0;
				while(tagname[i] != '\0')
				{
					if(tagname[i] != (tagnext->info)[j + i])
						break;
					i++;
				}
				if(tagname[i] == '\0')
				{
					(*sum)++;
					printf("\n标签为:%-20s", tagnext->info);
					if(fofnext->flag == 1)
						printf("  文件名为:%-20s", fofnext->name);
					else
						printf("文件夹名为:%-20s", fofnext->name);
					printf("所在路径为:%s", searchpath);
					break;
				}
				j++;
			}
			tagnext = tagnext->next;
		}
		fofnext = fofnext->next;
	}
	fofnext = head->F;
	while(fofnext != NULL)//递归 
	{
		if(fofnext->flag == 2)
		{
			strcpy(copypath, searchpath);
			strcat(copypath, a);
			strcat(copypath, fofnext->name);
			SearchTag(tagname, copypath, sum);
		}
		fofnext = fofnext->next;
	}
	DestroyFof(head);
	free(head);
}

 /**
 *  @name        : void FileSort(char *filename, CurFloder *head)
 *  @description : 对目标文件夹进行排序 
 *  @param       : char *filename  目标文件夹的名字，当名字为空，即对当前文件夹进行排序 
 *                 CurFloder *head 保存当前文件信息的结构体
 *  @return      : 
 */	
void FileSort(char *filename, CurFloder *head)
{
	int i, j;
	char a[] = "\\";
	char copypath[400];
	CurFloder *ortherhead;
	if(filename[0] == '\0')
	{
		LinkSort(head);
		Input_Save(head, currentpath);
	}
	else 
	{
		if(filename[1] != ':')
		{
			if(filename[0] != '\\') 
			{
				strcpy(copypath, currentpath);
				strcat(copypath, a);
				strcat(copypath, filename);
			}
			else
			{
				strcpy(copypath, rootpath);
				for(i = 0; copypath[i] != '\0'; i++)//找到最后一个斜杆 
				{
					if(copypath[i] == '\\')
						j = i;
				}
				copypath[j] = '\0';
				strcat(copypath, filename);
				filename = copypath;
			}
			
		}
		else
		{
			for(i = 0; rootpath[i] != '\0'; i++)
			{
				if(rootpath[i] != filename[i])
				{
					printf("路径不在用户下！排序失败！");
					return ;
				}
			}
			strcpy(copypath, filename);
		}
		if(ERRORS == RoteExistence(copypath, 0))
		{
			printf("该文件夹不存在！排序失败!");
			return ;
		}
		ortherhead = (CurFloder *)malloc(sizeof(CurFloder));
		Read_Save(ortherhead, copypath);
		LinkSort(ortherhead);
		Input_Save(ortherhead, copypath);
		free(ortherhead);
	}
	Read_Save(head, currentpath);
	printf("\n排序成功！"); 
} 

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : 对目标文件链表进行  插入排序  与 FileSort 函数连用 
 *  @param       : CurFloder *head 保存目标文件夹文件信息的结构体
 *  @return      : 
 */	
void LinkSort(CurFloder *head)
{
	FOF *fofnext1,*fofsave, **fofstak;
	int i, j, length;
	fofnext1 = head->F;
	for(length = 0; fofnext1 != NULL; fofnext1 = fofnext1->next, length++);
	if(length == 0 || length == 1)
		return ;
	fofstak = (FOF **)malloc(sizeof(FOF *) * length);
	fofnext1 = head->F;
	i = 0;
	while(fofnext1 != NULL)
	{
		fofstak[i++] = fofnext1;
		fofnext1 = fofnext1->next;
	}
	fofstak[i] = NULL;
	for(i = 1; i < length; i++)
	{
		fofsave = fofstak[i];
		j = i - 1;
		while(j > -1 && strcmp(fofstak[j]->name, fofsave->name) > 0)
		{
			fofstak[j + 1] = fofstak[j];
			j--;
		}
		fofstak[j + 1] = fofsave;
	}
	i = 0;
	while(i < length)
	{
		fofstak[i]->next = fofstak[i + 1];
		i++;
	}
	head->F = fofstak[0];
}
 
 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : 重命名文件
 *  @param       : CurFloder *head 保存目标文件夹文件信息的结构体
 *  @return      : 
 */	
void MVRename(CurFloder *head, char *oldname, char *newname) 
{
	int i, judge = 0;
	char a[] = "\\";
	char copycmd[400] = "ren ";
	FOF *fofnext, *fofsave;
	fofnext = head->F;
	while(fofnext != NULL)
	{
		if(strcmp(fofnext->name, oldname) == 0)
			break; 
		fofnext = fofnext->next;
	}
	if(fofnext == NULL)
	{
		printf("\n文件不存在！无法重命名！"); 
		return ; 
	}
	fofsave = fofnext;
	if(fofnext->flag == 1)
	{
		for(i = 0; newname[i] != '\0'; i++)
		{
			if(newname[i] == '.')
			{
				judge = 1; 
				break;
			}
		}
		if(judge == 0)
		{
			printf("\n无法将文件重命名为该名字！"); 
			return ;
		}
	}
	else
	{
		judge = 1;
		for(i = 0; newname[i] != '\0'; i++)
		{
			if(newname[i] == '.')
			{
				judge = 0;
				break;
			}
		}
		if(judge == 0)
		{
			printf("\n无法将文件夹重命名为该名字！"); 
			return ;
		}
	}
	for(i = 0; newname[i] != '\0'; i++)
		if(newname[i] == ' ' || newname[i] == '\\' || newname[i] == '/' || newname[i] == '<' || newname[i] == '>' || newname[i] == '|' || newname[i] == '"' || newname[i] == '*' || newname[i] == '?' || newname[i] == ':')
		{
			printf("\n输入文件名含非法字符！重命名失败！"); 
			return ;
		}
	fofnext = head->F;
	while(fofnext != NULL)
	{
		if(strcmp(fofnext->name, newname) == 0)
			break; 
		fofnext = fofnext->next;
	}
	if(fofnext != NULL)
	{
		printf("\n该文件夹中有相同名字！无法重命名！"); 
		return ; 
	}
	strcpy(fofsave->name, newname);
	Input_Save(head, currentpath);
	strcat(copycmd, currentpath);
	strcat(copycmd, a);
	strcat(copycmd, oldname);
	strcat(copycmd, " ");
	strcat(copycmd, newname);
	system(copycmd);
	strcpy(copycmd, currentpath);
	strcat(copycmd, a);
	strcat(copycmd, oldname);
	InputLog("重命名的文件的路径：", copycmd, "新的名字：", newname);
	printf("\n重命名成功！"); 
}

/**
 *  @name         void setColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
 *	@description        改变字的颜色 
 *	@param		   ForeColor前景颜色  BackGroundColor 背景颜色 
 *	@return		none
 *  @notice  none
 */
void setColor(unsigned short ForeColor,unsigned short BackGroundColor)

{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}

 /**
 *  @name        :  void PrintWorkFloder()
 *  @description : 树状打印所有文件夹以及笔记文件
 *  @param       : 
 *  @return      : 
 */	
void PrintTree(const char *prinpath, int choice, const char *form)
{
	char copyform[400];
	char copypath[400];
	char a[] = "\\", b[] = "\t\t ";
	int i, length;
	CurFloder *head;
	FOF *fofnext;
	head = (CurFloder *)malloc(sizeof(CurFloder));
	Read_Save(head, prinpath);
	fofnext = head->F;
	if(choice == 1)
		while(fofnext != NULL)
		{
			if(fofnext->flag == 1 )
			{
				if(choice == 1)
				{	
					printf("\n%s", form);
					printf("%s", fofnext->name);
				}
			}
			fofnext = fofnext->next;
		}
	fofnext = head->F;
	while(fofnext != NULL)
	{
		if(fofnext->flag == 2)
		{
			printf("\n%s", form);
			printf("%s", fofnext->name);
			for(i = 0; (fofnext->name)[i] != '\0'; i++);
			length = i;
			for(i = 0; i < (17 - length); i++)
				printf("_");
			strcpy(copypath, prinpath);
			strcat(copypath, a);
			strcat(copypath, fofnext->name);
			strcpy(copyform, form);
			strcat(copyform, b);
			PrintTree(copypath, choice, copyform);
		}
		fofnext = fofnext->next;
	}
	DestroyFof(head);
	free(head);
}

 /**
 *  @name        :  void TnputLog(char *message1, char *firstmessage, char *message2, *char secondmessage)
 *  @description : 记录操作 
 *  @param       : 
 *  @return      : 
 */	
void InputLog(char *message1, char *firstmessage, char *message2, char *secondmessage)
{
	FILE *a;
	char times[32];//存储时间的字符串
	time_t save;
	struct tm *T;
	a = fopen("_journal.txt","a");
	if(a == NULL)
	{
		printf("打开文件失败！");
		return;
	}
	time(&save);
	T = localtime(&save);
	strftime(times, 32, "%m-%d-%Y %H:%M:%S", T);	//获得时间的字符串
	fputs(times, a);
	fputs("    ", a);
	fputs(message1, a);
	fputs(firstmessage, a);
	fputs("    ", a);
	fputs(message2, a);
	fputs(secondmessage, a);
	fputs("\n", a);
	fclose(a);
}

 /**
 *  @name        :  void PrinLog()
 *  @description : 输出进行过的操作 
 *  @param       : 
 *  @return      : 
 */	
void PrinLog()
{
	FILE *r;
	char prinlog[800];
	r = fopen("_journal.txt","r");
	printf("\n");
	if(r == NULL)
	{
		printf("打开文件_journal.txt失败！(若您是第一次登陆请忽视此提示)");
		return;
	}
	while(fgets(prinlog, 800, r) != NULL)
	{
		printf("%s", prinlog);
	}
	fclose(r);
}
