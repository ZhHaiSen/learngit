#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../head/NoteManagementSystem.h"
#include "../head/prin.h"


extern char rootpath[];//存储用户路径   
extern char currentpath[];//存储当前路径

 /**
 *  @name        :  void PrintCurrentFloder(CurFloder *head)
 *  @description :  打印当前目录下所有笔记和文件夹
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *  @return      : 
 */	
void PrintCurrentFloder(CurFloder *head)
{
   FOF *fofnext;
   int sum = 0;
   fofnext = head->F;
   while(fofnext != NULL)
   {
   	if(fofnext->flag == 1)
		printf("\n  笔记文件名：%s", fofnext->name);
	else
   		printf("\n笔记文件夹名：%s", fofnext->name);
   	sum++;
   	fofnext = fofnext->next;
   }
   printf("\n总文件数为：%d", sum);
}

 /**
 *  @name        :  void PrintPathFloder(char *filepath)
 *  @description :  打印路径下的所有笔记和文件夹
 *  @param       : 	char *filepath  目标路径 
 *  @return      : 
 */	
void PrintPathFloder(char *filepath)
{
    int i, j;
	int length, sum;
	char copypath[400];
	for(i = 0; filepath[i] != '\0'; i++);
	if(filepath[i - 1] == '\\')
	{
		printf("\n路径输入错误！");
		return ; 
	} 
	if(filepath[1] != ':')
	{
		if(filepath[0] != '\\')
		{
			strcpy(copypath, currentpath);
			strcat(copypath, "\\");
			strcat(copypath, filepath);
			filepath = copypath;
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
			strcat(copypath, filepath);
			filepath = copypath;
		}
	}
	else
	{
		length = strlen(rootpath);
		for(i = 0; i < length; i++)//判断目标路径是否在用户目录内 
		{
	 		if(filepath[i] != rootpath[i])
	 		{
	 			printf("\n路径超出用户可操控范围！");
				return ;
			}
		}
	}
	if(RoteExistence(filepath, 0) != SUCCESS)
	{
		printf("\n文件或路径不存在！");
		return ;
	}	
	sum = 0;
	RecursionPrin(filepath, &sum);
	printf("\n文件总数为：%d", sum);
}

 /**
 *  @name        :  void RecursionPrin(char *prinpath, int *sum) ； 
 *  @description :  打印路径下的所有笔记和文件夹(与void PrintPathFloder(char *filepath)连用)
 *  @param       : 	char *prinpath  目标路径 int *sum 总数 
 *  @return      : 
 */	
void RecursionPrin(char *prinpath, int *sum) 
{
	char copypath[400];
	char a[] = "\\";
	CurFloder *head;
	FOF *fofnext;
	head = (CurFloder *)malloc(sizeof(CurFloder));
	Read_Save(head, prinpath);
	fofnext = head->F;
	while(fofnext != NULL)
	{
		if(fofnext->flag == 1)
		{
			printf("\n  文件名:%-20s", fofnext->name);
		}
		else
		{
			printf("\n文件夹名:%-20s", fofnext->name);
		}
		(*sum)++;
		printf("路径：%s",prinpath); 
		fofnext = fofnext->next;
	}
	fofnext = head->F;
	while(fofnext != NULL)//递归 
	{
		if(fofnext->flag == 2)
		{
			strcpy(copypath, prinpath);
			strcat(copypath, a);
			strcat(copypath, fofnext->name);
			RecursionPrin(copypath, sum);
		}
		fofnext = fofnext->next;
	}
	DestroyFof(head);
	free(head);
}
