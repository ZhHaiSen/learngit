#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "../head/NoteManagementSystem.h"
#include "../head/pengweitag.h"
#include "../head/linwenchen.h"
#include "../head/moveFOF.h"
#include "../head/chenyu.h" 
#include "../head/prin.h"

extern char rootpath[];//�洢�û�·��         CurFloder *currentfile
extern char currentpath[];//�洢��ǰ·��

/**
 *  @name        : Status RoteExistence(const char *s, int choice)
 *  @description : ������·�����Ƿ�����ļ��л�txt�ļ� ��Ҳ���������ж�·�������Ƿ���ȷ 
 *  @param       : const char *s ����ľ���·��    choice 0��ʾ�ж��ļ��д������   ��'0'��ʾtxt�ļ��������
 *  @return      : SUCCESS ��ʾ����      ERROR��ʾ������ 
 */
Status RoteExistence(const char *s, int choice)
{
	FILE *w;
	char a[400];
	char b[] = "\\_save.txt";
	strcpy(a, s);
	if(choice == 0)//����������� ���� ���Ŀ¼�Ƿ���� 
	{
		strcat(a, b);//������ļ��У���ô�ļ����ڿ϶����ڱ������ݵ�txt�ļ����Դ˼����Ƿ�����ļ���
	}	//������������if��䣬�����ı��ļ��Ƿ���ڣ������������ 
	w = fopen(a, "r");
	if(w == NULL)
	{
		fclose(w);
		return ERRORS;
	}
	fclose(w);
	return SUCCESS;
}

 /**
 *  @name        : void Input_Save(CurFloder *input)
 *  @description : ���ļ�����Ϣ¼��_save.txt �ļ� 
 *  @param       : CurFloder char *input   �����ļ���Ϣ����ĵĽṹ��
 *                 const char *filerote    Ҫ������Ŀ¼��·�������ü�_save.txt���������Զ�����_save.txt,ֻҪ��Ŀ¼��·���� 
 *  @return      : 
 */
void Input_Save(CurFloder *input, const char *filerote)
{
	FILE *w;
	char copyfilerote[400];
	char a[] = "\\_save.txt";
	FOF *fofnext;
	Tag *tagnext;
	int tagnum;
	fofnext = input->F;
	strcpy(copyfilerote, filerote);//���ƻ�õ�·�� 
	strcat(copyfilerote, a);//��·�������_save.txt����ļ��� 
	w = fopen(copyfilerote, "w");
	if(w == NULL)
	{
		printf("�ļ�<%s>��ʧ��",filerote); 
		getchar(); 
		exit(0);
	}
	while(fofnext != NULL)
	{
		fprintf(w, "%d %s %d \n", fofnext->flag, fofnext->name, fofnext->num);
		tagnum = fofnext->num;
		if(tagnum > 0)
		{
			tagnext = fofnext->taghead;
			while(tagnum > 0)
			{
				fprintf(w, "   %s   ", tagnext->info);
				tagnext = tagnext->next;
				tagnum--;
			}
			fprintf(w, "\n");
		}
		fofnext = fofnext->next;
	}
	fclose(w);
}

/**
 *  @name        : void Read_Save(CurFloder *read, const char *filerote)
 *  @description : ��_save.txt ��ȡ�ļ�����Ϣ
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *                 const char *filerote    Ŀ¼��·�������ü�_save.txt���������Զ�����_save.txt��
 *  @return      : 
 */	
void Read_Save(CurFloder *read, const char *filerote)
{										
	FILE *r;
	char rotecopy[400];
	char a[20] = "\\_save.txt";
	FOF *fofnext1, *fofnext2;
	Tag *tagnext1, *tagnext2;
	int tagnum;
	int filesum = 0;
	strcpy(rotecopy, filerote);
	strcat(rotecopy, a);
	r = fopen(rotecopy, "r");
	if(r == NULL)
	{
		printf("�ļ�<%s>��ʧ��",filerote); 
		getchar();
		exit(0);
	}
	fofnext1 = fofnext2 = (FOF *)malloc(sizeof(FOF));
	read->F = fofnext1;
	while(EOF != fscanf(r, "%d%s%d", &fofnext2->flag, fofnext2->name, &fofnext2->num))
	{
		filesum++;
		if(filesum != 1)
		{
			fofnext1->next = fofnext2;
			fofnext1 = fofnext2;
		}
		fofnext2 = (FOF *)malloc(sizeof(FOF));
		if(fofnext1->num > 0)
		{	
			tagnum = 0;
			while(tagnum < fofnext1->num)
			{
				tagnum++;
				tagnext2 = (Tag *)malloc(sizeof(Tag));
				fscanf(r, "%s", tagnext2->info);
				if(tagnum == 1)
				{
					tagnext1 = tagnext2;
					fofnext1->taghead = tagnext1;
				}	
				else
				{
					tagnext1->next = tagnext2;
					tagnext1 = tagnext2;
				}
			}
			tagnext1->next = NULL;
		}
		else
		{
			fofnext1->taghead = NULL;
		}
	}
	free(fofnext2);
	if(filesum == 0)
	{
		read->F = NULL;
	}
	else
	{
		fofnext1->next = NULL;
	}
	fclose(r);
}

/**
 *  @name        : void DestroyFof(CurFloder *des)
 *  @description : �������� 
 *  @param       :  CurFloder *des   �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 */	
void DestroyFof(CurFloder *des)
{
	FOF *fofdes1, *fofdes2;
	Tag *tagdes1, *tagdes2;
	fofdes1 = des->F;
	while(fofdes1 != NULL)
	{
		tagdes1 = fofdes1->taghead;
		while(tagdes1 != NULL)
		{
			tagdes2 = tagdes1->next;
			free(tagdes1);
			tagdes1 =tagdes2;
		}
		fofdes2 = fofdes1->next;
		free(fofdes1);
		fofdes1 = fofdes2;
	} 
	des->F = NULL;
}

/**
 *  @name        : vvoid SecondMain()
 *  @description : �൱�ڵڶ��������� 
 *  @param       : 
 */	
void SecondMain(User name)
{
	CurFloder *head;
	char copychar[400];
	char inputmessage[400], copymessage[400];
	char firstmessage[400], secondmessage[400];
	int savesum, userchoice, length;
	int i, j;
	CONSOLE_CURSOR_INFO cursor_info = {1, 1};//�������ʾ 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	system("cls");
	PrinLog();
	InputLog("  ", "  ", "  ", "  ");
	system("pause"); 
	system("cls");
	strcat(rootpath, "\\");
	strcat(rootpath, name.root);
	strcpy(currentpath, rootpath);
	head = (CurFloder *)malloc(sizeof(CurFloder));
	for(i = 0; rootpath[i] != '\0'; i++)//�ҵ����һ��б�� 
	{
		if(rootpath[i] == '\\')
			length = i;
	}
	while(1)
	{	
		Read_Save(head, currentpath);
		setColor(3,0);
		printf("\n%s   ", name.name);
		setColor(12,0);
		for(i = 0; i < length; i++)
			printf("%c", currentpath[i]);
		setColor(14,0);
		for(i; currentpath[i] != '\0'; i++)
			printf("%c", currentpath[i]);
		setColor(15,0);
		printf("\n�� ");
		gets(inputmessage);
		if(!strcmp(inputmessage, "Close"))//�رճ��� 
		{
			system("cls");
			setColor(14,0);
			printf("\n\n\n\n\t\t\t\t\t*********************************\n");
			printf("\t\t\t\t\t*                               *\n"); 
			printf("\t\t\t\t\t*          Good Bye��           *\n"); 
			printf("\t\t\t\t\t*                               *\n");
			printf("\t\t\t\t\t*********************************\n");
			printf("\t\t\t\t\t");
			system("pause");
			exit(0);
		}	
		if(!strcmp(inputmessage, "Return"))//���ص�½���� 
		{
			rootpath[length] = '\0';
			break;
		}
		if(!strcmp(inputmessage, "help"))//����������� 
		{
			print_help(); 
			continue;
		}
		for(i = 0; inputmessage[i] == ' ' && inputmessage[i] != '\0'; i++);
			savesum = i;
		for(i = savesum; inputmessage[i] != '\0'; i++)
			copychar[i - savesum] = inputmessage[i];
		copychar[i - savesum] = '\0';
		if(copychar[0] == 'l' && copychar[1] == 's')//ls
		{
			for(i = 2; copychar[i] == ' ' && copychar[i] != '\0'; i++);
			if(copychar[i] != '\0')
			{
				if(copychar[i] == '-' && copychar[i + 1] == 'a' && (copychar[i + 2] == ' ' || copychar[i + 2] == '\0' || copychar[i + 2] == '1'))
				{
					j = i;
					for(i += 2; copychar[i] == ' ' && copychar[i] != '\0'; i++);
					if(copychar[i] == '\0')
					{
						userchoice = 2;
					}	
					else
					{
						i = j;
						if(copychar[i + 2] == '1')
						{
							j += 3;
							for(i = j; copychar[i] == ' ' && copychar[i] != '\0'; i++);
							if(copychar[i] == '\0')
							{
								userchoice = 19;
							}
							else
							{
								printf("\n����ָ�����");
								continue;
							}	
						}
						else
						{
							printf("\n����ָ�����");
							continue;
						}
						
					}
				}
				else
				{
					j = i;
					for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
					{
						firstmessage[i - j] = copychar[i];
					}
					firstmessage[i - j] = '\0';
					for(i; copychar[i] == ' ' && copychar[i] != '\0'; i++);
					if(copychar[i] == '\0')
					{
						userchoice = 3;
					}
					else
					{
						if(copychar[i] == 'g' && copychar[i + 1] == 'r' && copychar[i + 2] == 'e' && copychar[i + 3] == 'p' && copychar[i + 4] == ' ')
						{
							for(i += 5; copychar[i] == ' ' && copychar[i] != '\0'; i++);
							j = i;
							if(copychar[i] != '\0')
							{
								for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
								{
									secondmessage[i - j] = copychar[i];
								}
								secondmessage[i - j] = '\0';
								if(copychar[i] != ' ')
									userchoice = 4;
								else
								{
									printf("\n����ָ�����");
									continue;
								}
							}
							else
							{
								printf("\n����ָ�����");
								continue;
							}
						}
						else
						{
							printf("\n����ָ�����");
							continue;
						}
					}
				}
			}
			else
			{
				userchoice = 1;
			}	
		}
		else
			if(copychar[0] == 'c' && copychar[1] == 'd')//cd
			{
				if(copychar[2] == '.' && copychar[3] == '.')
				{
					for(i = 4; copychar[i] != '\0' && copychar[i] == ' '; i++);
					if(copychar[i] == '\0')
						userchoice = 5;
					else
					{
						printf("\n����ָ�����");
						continue;
					}
				}
				else
				{
					for(i = 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
					if(i == 2)
					{
						printf("\n����ָ�����");
						continue;
					}
					if(copychar[i] != '\0')
					{
						j = i;
						for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
							firstmessage[i - j] = copychar[i];
						firstmessage[i - j] = '\0';
						for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);	
						if(copychar[i] == '\0')
							userchoice = 6;
						else
						{
							printf("\n����ָ�����");
							continue;
						}
					}
					else
					{
						printf("\n����ָ�����");
						continue;
					}
				}
			}
			else
				if(copychar[0] == 'm' && copychar[1] == 'v' && copychar[2] == ' ')//mv
				{
					for(i = 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
					if(copychar[i] == '-' && copychar[i + 1] == 'r' && (copychar[i + 2] == ' ' || copychar[i + 2] == '\0'))
					{
						for(i += 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
						j = i;
						for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
							firstmessage[i - j] = copychar[i];
						firstmessage[i - j] = '\0';
						for(i; copychar[i] == ' ' && copychar[i] != '\0'; i++);
						j = i;
						for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
							secondmessage[i - j] = copychar[i];
						secondmessage[i - j] = '\0';
						if(i == j)
						{
							printf("\n����ָ�����");
							continue;
						}
						for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
						if(copychar[i] == '\0')
							userchoice = 9;
						else
						{
							printf("\n����ָ�����");
							continue;
						}
					}
					else
					{
						if(copychar[i] != '\0')
						{
							j = i;
							for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
								firstmessage[i - j] = copychar[i];
							firstmessage[i - j] = '\0';
							for(i; copychar[i] == ' ' && copychar[i] != '\0'; i++);
							j = i;
							for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
								secondmessage[i - j] = copychar[i];
							secondmessage[i - j] = '\0';
							if(i == j)
							{
								printf("\n����ָ�����");
								continue;
							}
							for(i; copychar[i] == ' ' && copychar[i] != '\0'; i++);
							if(copychar[i] == '\0')
							{
								j = 0;
								for(i = 0; secondmessage[i] != '\0'; i++)
									if(secondmessage[i] == '\\')
										j = i;
								for(i = j; secondmessage[i] != '\0'; i++)
									if(secondmessage[i] == '.')
										break;
								if(secondmessage[i] == '.')
								{
									userchoice = 8;
								}
								else
									userchoice = 7;
							}
							else
							{
								printf("\n����ָ�����");
								continue;
							}
						}
						else
						{
							printf("\n����ָ�����");
							continue;
						}
					}
				}
				else 
					if(copychar[0] == 'r' && copychar[1] == 'm' && copychar[2] == ' ' )//rm
					{
						for(i = 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
						if(copychar[i] == '-' && copychar[i + 1] == 'r' && (copychar[i + 2] == ' ' || copychar[i + 2] == '\0'))
						{
							for(i += 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
							j = i;
							for(i; copychar[i] != ' ' && copychar[i] != '\0'; i++)
								firstmessage[i - j] = copychar[i];
							firstmessage[i - j] = '\0';
							if(i == j)
							{
								printf("\n����ָ�����");
								continue;
							}
							for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
							if(copychar[i] == '\0')
								userchoice = 11;
							else
							{
								printf("\n����ָ�����");
								continue;
							}
						}
						else
						{
							j = i;
							for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
							{
								firstmessage[i - j] = copychar[i];
							}
							firstmessage[i - j] = '\0';
							if(i == j)
							{
								printf("\n����ָ�����");
								continue;
							}
							for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
							if(copychar[i] == '\0')
								userchoice = 10;
							else
							{
								printf("\n����ָ�����");
								continue;
							}
						}
					}
					else
						if(copychar[0] == 't' && copychar[1] == 'a' && copychar[2] == 'g' && copychar[3] == ' ')//tag
						{
							for(i = 3; copychar[i] != '\0' && copychar[i] == ' '; i++);
							if(copychar[i] != '\0')
							{
								for(j = i; copychar[j] != '\0' && copychar[j] != ' '; j++);
								for(j = i; copychar[j] != '\0' && copychar[j] == ' '; j++);
								if(copychar[j] == '\0')
								{
									printf("\n����ָ�����");
									continue;
								}
								if(copychar[i] == '-' && copychar[i + 1] == 'a' && copychar[i+ 2] == 'd' && copychar[i + 3] == 'd' && copychar[i + 4] == ' ' )
								{
									for(i += 4; copychar[i] != '\0' && copychar[i] == ' '; i++);
									j = i;
									for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
										firstmessage[i - j] = copychar[i];
									firstmessage[i - j] = '\0';
									for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
									j = i;
									for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
										secondmessage[i - j] = copychar[i];
									secondmessage[i - j] = '\0';
									if(i == j)
									{
										printf("\n����ָ�����");
										continue;
									}
									for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
									if(copychar[i] == '\0')
										userchoice = 13;
									else
									{
										printf("\n����ָ�����");
										continue;
									}
									
								}
								else
									if(copychar[i] == '-' && copychar[i + 1] == 'd' && copychar[i+ 2] == 'e' && copychar[i + 3] == 'l' && copychar[i + 4] == ' ' )
									{
										for(i += 4; copychar[i] != '\0' && copychar[i] == ' '; i++);
										j = i;
										for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
											firstmessage[i - j] = copychar[i];
										firstmessage[i - j] = '\0';
										for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
										j = i;
										for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
											secondmessage[i - j] = copychar[i];
										secondmessage[i - j] = '\0';
										if(i == j)
										{
											printf("\n����ָ�����");
											continue;
										}
										for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
										if(copychar[i] == '\0')
											userchoice = 14;
										else
										{
											printf("\n����ָ�����");
											continue;
										}
									}
									else
										if(copychar[i] == '-' && copychar[i + 1] == 's' && copychar[i + 2] == ' ' )
										{
											for(i += 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
											j = i;
											for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
												firstmessage[i - j] = copychar[i];
											firstmessage[i - j] = '\0';
											for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
											if(copychar[i] == '\0')
												userchoice = 15;
											else
											{
												printf("\n����ָ�����");
												continue;
											}
										}
										else
											if(copychar[i] == '-' && copychar[i + 1] == 's' && copychar[i + 2] == 'a' && copychar[i + 3] == ' ')
											{
												for(i += 3; copychar[i] != '\0' && copychar[i] == ' '; i++);
												j = i;
												for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
													firstmessage[i - j] = copychar[i];
												firstmessage[i - j] = '\0';
												for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
												if(copychar[i] == '\0')
													userchoice = 16;
												else
												{
													printf("\n����ָ�����");
													continue;
												}
											}
											else
											{
												j = i;
												for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
													firstmessage[i - j] = copychar[i];
												firstmessage[i - j] = '\0';
												for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
												if(copychar[i] == '\0')
													userchoice = 12;
												else
												{
													printf("\n����ָ�����");
													continue;
												}
											}
							}
							else
							{
								printf("\n����ָ�����");
								continue;	
							}
							
						}
						else
							if(copychar[0] == 'm' && copychar[1] == 'd' && copychar[2] == ' ')//md 
							{
								for(i = 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
								j = i;
								for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
									firstmessage[i - j] = copychar[i];
								firstmessage[i - j] = '\0';
								if(i == j)
								{
									printf("\n����ָ�����");
									continue;
								}
								for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
								if(copychar[i] == '\0')
								{
									userchoice = 17;
								}
								else
								{
									printf("\n����ָ�����");
									continue;
								}
							}
							else
								if(copychar[0] == 's' && copychar[1] == 'o' && copychar[2] == 'r' && copychar[3] == 't' && copychar[4] == ' ')//sort
								{
									
									for(i = 4; copychar[i] == ' ' && copychar[i] != '\0'; i++);
									j = i;
									for(i; copychar[i] != '\0' && copychar[i] != ' '; i++)
										firstmessage[i - j] = copychar[i];
									firstmessage[i - j] = '\0';
									for(i; copychar[i] == ' ' && copychar[i] != '\0'; i++);
									if(copychar[i] == '\0')
										userchoice = 18;
									else
									{
										printf("\n����ָ�����");
										continue;
									}
								}
								else
								{
									printf("\n����ָ�����");
									continue;
								}
		switch(userchoice)
		{
			case 1://��ʾ��ǰĿ¼�µ��ļ����ļ��� 
				PrintCurrentFloder(head);
				break;
			case 2://��״��ʾ�����ļ����ļ����ļ��У� 
				printf("��Ŀ¼Ϊ��%s", rootpath);
				printf("\n__");
				PrintTree(rootpath , 1, " ");
				printf("\n");
				break;
			case 3:// ������·��  ���·��  ��ǰĿ¼   ��ʾ�����ļ��������ļ� 
				PrintPathFloder(firstmessage);
				break;
			case 4://ģ�������ļ���   �ɾ���·��  ���·�� ��ǰĿ¼ 
				if(firstmessage[1] != ':')
				{
					if(firstmessage[0] != '\\')
					{
						strcpy(copymessage, currentpath);
						strcat(copymessage, "\\");
						strcat(copymessage, firstmessage);
						strcpy(firstmessage, copymessage);
					}
					else
					{
						strcpy(copymessage, rootpath);
						copymessage[length] = '\0';
						strcat(copymessage, firstmessage);
						strcpy(firstmessage, copymessage);
					}
				}
				if(RoteExistence(firstmessage, 0) == ERRORS)
				{
					printf("\n����·������");
					break; 
				}
				LsGrep(firstmessage,secondmessage);
				break;
			case 5://������һ�� 
				CdReturn(head);
				break;
			case 6://����Ŀ��·�� �ɵ�ǰĿ¼ ����·��  ���·�� 
				CdSwitch(head, firstmessage);
				break;
			case 7://�ƶ��ļ�  �ɵ�ǰĿ¼ ����·��  ���·��  
				movefile(firstmessage, secondmessage);
				break;
			case 8://������ֻ�ܵ�ǰĿ¼�²��� 
				MVRename(head, firstmessage, secondmessage);
				break;
			case 9://�ƶ��ļ���  �ɵ�ǰĿ¼ ����·��  ���·�� 
				movefolder(firstmessage, secondmessage);
				break;
			case 10://ɾ���ļ� ֻ�ܵ�ǰĿ¼�²��� 
				for(i = 0; firstmessage[i] != '\0'; i++);
				if(firstmessage[i - 1] != 't' || firstmessage[i - 2] != 'x' || firstmessage[i - 3] != 't' || firstmessage[i - 4] != '.')
				{
					printf("\n����ķǱʼ��ļ���");
					break;
				}
				DeleteFOF(head,firstmessage);
				break;
			case 11://ɾ���ļ��� ֻ�ܵ�ǰĿ¼�²���
				for(i = 0; firstmessage[i] != '\0'; i++);
				if(firstmessage[i - 1] == 't' && firstmessage[i - 2] == 'x' && firstmessage[i - 3] == 't' && firstmessage[i - 4] == '.')
				{
					printf("\n����ķǱʼ��ļ��У�");
					break;
				}
				DeleteFOF(head,firstmessage);
				break;
			case 12://�����ǰĿ¼�µ��ļ����ļ��еı�ǩ 
				PrintAppointTag(head, firstmessage);
				break;
			case 13://Ϊ��ǰĿ¼��ָ���ļ����ļ������ָ����ǩ 
				AddAppointTag(head, firstmessage, secondmessage);
				break;
			case 14://Ϊ��ǰĿ¼��ָ���ļ����ļ���ɾ��ָ����ǩ 
				DeleteAppointTag(head, firstmessage, secondmessage);
				break;
			case 15://ģ�����ҵ�ǰĿ¼�±�ǩ�����������ļ����ļ��� 
				PrintCurFloderTag(head, firstmessage);
				break;
			case 16:// ģ���������б�ǩ�����������ļ� 
				savesum = 0;
				SearchTag(firstmessage, rootpath, &savesum);
				printf("\n�����������ļ�����Ϊ��%d",savesum);
				break;
			case 17://�����ļ���  ֻ�ܵ�ǰĿ¼�²��� 
				MakeFOF(head,firstmessage);
				break;
			case 18:// ����·������ �ɵ�ǰĿ¼  ����·��  ���·�� 
				FileSort(firstmessage, head);
				break;
			case 19:// ��״��������ļ��� 
				printf("��Ŀ¼Ϊ��%s", rootpath);
				printf("\n__");
				PrintTree(rootpath , 0, " ");
				printf("\n");
				break;
			default : ;
		}
	}

}
