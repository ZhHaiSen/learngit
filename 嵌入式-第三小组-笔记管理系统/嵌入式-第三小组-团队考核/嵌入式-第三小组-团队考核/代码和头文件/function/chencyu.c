#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../head/NoteManagementSystem.h"
#include "../head/chenyu.h" 

extern char rootpath[];//�洢�û�·��         CurFloder *currentfile
extern char currentpath[];//�洢��ǰ·��

/**
 *  @name        : Status CdReturn(CurFloder *head)
 *  @description : ������һ�� 
 *  @param       : CurFloder *head  
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *  @return      : 
 */	
 Status CdReturn(CurFloder *head)
 {
 	int num, savenum;
	if(strcmp(rootpath, currentpath) == 0)//�ж��Ƿ�Ϊ��Ŀ¼ 
	{
		printf("\n��ǰΪ��Ŀ¼���޷����أ�"); 
		return ERRORS;
	}
	DestroyFof(head);//������һ�ε����� 
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
 *  @description :  ��ת��Ŀ��·�� 
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *                 char *targetpath    Ŀ¼��·�� 
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
		printf("\n·����������л�·��ʧ�ܣ�");
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
			for(i = 0; copypath[i] != '\0'; i++)//�ҵ����һ��б�� 
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
		for(i = 0; i < length; i++)//�ж�Ŀ��·���Ƿ����û�Ŀ¼�� 
		{
	 		if(targetpath[i] != rootpath[i])
	 		{
	 			printf("\n·�������û��ɲٿط�Χ���л�·��ʧ�ܣ�");
				return ERRORS;
			}
		}
	}
	if(RoteExistence(targetpath, 0) == ERRORS)
	{
		printf("\n·����������л�·��ʧ�ܣ�");
		return ERRORS;
	}
	for(i = 0; targetpath[i] != '\0'; i++);
	if(targetpath[i - 3] == '\\' && targetpath[i - 1] == '.' && targetpath[i - 2] == '.')
	{
		printf("\n·����������л�·��ʧ�ܣ�");
		return ERRORS;
	}
	if(targetpath[i - 2] == '\\' && targetpath[i - 1] == '.')
	{
		printf("\n·����������л�·��ʧ�ܣ�");
		return ERRORS;
	}
	DestroyFof(head);//������һ�ε�����
	strcpy(currentpath, targetpath);//�ı䵱ǰ·�� 
	Read_Save(head, currentpath);
	return SUCCESS;
 }
 
 /**
 *  @name        : void SearchTag(const char *tagname, const char *searchpath)
 *  @description : ���ݱ�ǩ���ֲ������и��û��ķ��ϱ�ǩ���ļ� ����ģ�����ң� 
 *  @param       : const char *tagname  ��ǩ�� 
 *                 const char *searchpath  ���ҵ�·�� 
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
					printf("\n��ǩΪ:%-20s", tagnext->info);
					if(fofnext->flag == 1)
						printf("  �ļ���Ϊ:%-20s", fofnext->name);
					else
						printf("�ļ�����Ϊ:%-20s", fofnext->name);
					printf("����·��Ϊ:%s", searchpath);
					break;
				}
				j++;
			}
			tagnext = tagnext->next;
		}
		fofnext = fofnext->next;
	}
	fofnext = head->F;
	while(fofnext != NULL)//�ݹ� 
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
 *  @description : ��Ŀ���ļ��н������� 
 *  @param       : char *filename  Ŀ���ļ��е����֣�������Ϊ�գ����Ե�ǰ�ļ��н������� 
 *                 CurFloder *head ���浱ǰ�ļ���Ϣ�Ľṹ��
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
				for(i = 0; copypath[i] != '\0'; i++)//�ҵ����һ��б�� 
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
					printf("·�������û��£�����ʧ�ܣ�");
					return ;
				}
			}
			strcpy(copypath, filename);
		}
		if(ERRORS == RoteExistence(copypath, 0))
		{
			printf("���ļ��в����ڣ�����ʧ��!");
			return ;
		}
		ortherhead = (CurFloder *)malloc(sizeof(CurFloder));
		Read_Save(ortherhead, copypath);
		LinkSort(ortherhead);
		Input_Save(ortherhead, copypath);
		free(ortherhead);
	}
	Read_Save(head, currentpath);
	printf("\n����ɹ���"); 
} 

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : ��Ŀ���ļ��������  ��������  �� FileSort �������� 
 *  @param       : CurFloder *head ����Ŀ���ļ����ļ���Ϣ�Ľṹ��
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
 *  @description : �������ļ�
 *  @param       : CurFloder *head ����Ŀ���ļ����ļ���Ϣ�Ľṹ��
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
		printf("\n�ļ������ڣ��޷���������"); 
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
			printf("\n�޷����ļ�������Ϊ�����֣�"); 
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
			printf("\n�޷����ļ���������Ϊ�����֣�"); 
			return ;
		}
	}
	for(i = 0; newname[i] != '\0'; i++)
		if(newname[i] == ' ' || newname[i] == '\\' || newname[i] == '/' || newname[i] == '<' || newname[i] == '>' || newname[i] == '|' || newname[i] == '"' || newname[i] == '*' || newname[i] == '?' || newname[i] == ':')
		{
			printf("\n�����ļ������Ƿ��ַ���������ʧ�ܣ�"); 
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
		printf("\n���ļ���������ͬ���֣��޷���������"); 
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
	InputLog("���������ļ���·����", copycmd, "�µ����֣�", newname);
	printf("\n�������ɹ���"); 
}

/**
 *  @name         void setColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
 *	@description        �ı��ֵ���ɫ 
 *	@param		   ForeColorǰ����ɫ  BackGroundColor ������ɫ 
 *	@return		none
 *  @notice  none
 */
void setColor(unsigned short ForeColor,unsigned short BackGroundColor)

{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}

 /**
 *  @name        :  void PrintWorkFloder()
 *  @description : ��״��ӡ�����ļ����Լ��ʼ��ļ�
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
 *  @description : ��¼���� 
 *  @param       : 
 *  @return      : 
 */	
void InputLog(char *message1, char *firstmessage, char *message2, char *secondmessage)
{
	FILE *a;
	char times[32];//�洢ʱ����ַ���
	time_t save;
	struct tm *T;
	a = fopen("_journal.txt","a");
	if(a == NULL)
	{
		printf("���ļ�ʧ�ܣ�");
		return;
	}
	time(&save);
	T = localtime(&save);
	strftime(times, 32, "%m-%d-%Y %H:%M:%S", T);	//���ʱ����ַ���
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
 *  @description : ������й��Ĳ��� 
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
		printf("���ļ�_journal.txtʧ�ܣ�(�����ǵ�һ�ε�½����Ӵ���ʾ)");
		return;
	}
	while(fgets(prinlog, 800, r) != NULL)
	{
		printf("%s", prinlog);
	}
	fclose(r);
}
