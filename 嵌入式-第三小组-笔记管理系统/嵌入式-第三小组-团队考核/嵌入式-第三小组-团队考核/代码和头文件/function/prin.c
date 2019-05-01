#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../head/NoteManagementSystem.h"
#include "../head/prin.h"


extern char rootpath[];//�洢�û�·��   
extern char currentpath[];//�洢��ǰ·��

 /**
 *  @name        :  void PrintCurrentFloder(CurFloder *head)
 *  @description :  ��ӡ��ǰĿ¼�����бʼǺ��ļ���
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
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
		printf("\n  �ʼ��ļ�����%s", fofnext->name);
	else
   		printf("\n�ʼ��ļ�������%s", fofnext->name);
   	sum++;
   	fofnext = fofnext->next;
   }
   printf("\n���ļ���Ϊ��%d", sum);
}

 /**
 *  @name        :  void PrintPathFloder(char *filepath)
 *  @description :  ��ӡ·���µ����бʼǺ��ļ���
 *  @param       : 	char *filepath  Ŀ��·�� 
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
		printf("\n·���������");
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
			for(i = 0; copypath[i] != '\0'; i++)//�ҵ����һ��б�� 
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
		for(i = 0; i < length; i++)//�ж�Ŀ��·���Ƿ����û�Ŀ¼�� 
		{
	 		if(filepath[i] != rootpath[i])
	 		{
	 			printf("\n·�������û��ɲٿط�Χ��");
				return ;
			}
		}
	}
	if(RoteExistence(filepath, 0) != SUCCESS)
	{
		printf("\n�ļ���·�������ڣ�");
		return ;
	}	
	sum = 0;
	RecursionPrin(filepath, &sum);
	printf("\n�ļ�����Ϊ��%d", sum);
}

 /**
 *  @name        :  void RecursionPrin(char *prinpath, int *sum) �� 
 *  @description :  ��ӡ·���µ����бʼǺ��ļ���(��void PrintPathFloder(char *filepath)����)
 *  @param       : 	char *prinpath  Ŀ��·�� int *sum ���� 
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
			printf("\n  �ļ���:%-20s", fofnext->name);
		}
		else
		{
			printf("\n�ļ�����:%-20s", fofnext->name);
		}
		(*sum)++;
		printf("·����%s",prinpath); 
		fofnext = fofnext->next;
	}
	fofnext = head->F;
	while(fofnext != NULL)//�ݹ� 
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
