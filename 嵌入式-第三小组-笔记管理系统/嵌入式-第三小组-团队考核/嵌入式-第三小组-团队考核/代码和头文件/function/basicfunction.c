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

extern char rootpath[];//存储用户路径         CurFloder *currentfile
extern char currentpath[];//存储当前路径

/**
 *  @name        : Status RoteExistence(const char *s, int choice)
 *  @description : 检查这个路径下是否存在文件夹或txt文件 ，也可以用作判断路径输入是否正确 
 *  @param       : const char *s 输入的绝对路径    choice 0表示判断文件夹存在与否   非'0'表示txt文件存在与否
 *  @return      : SUCCESS 表示存在      ERROR表示不存在 
 */
Status RoteExistence(const char *s, int choice)
{
	FILE *w;
	char a[400];
	char b[] = "\\_save.txt";
	strcpy(a, s);
	if(choice == 0)//用作重名检测 或者 检查目录是否存在 
	{
		strcat(a, b);//如果是文件夹，那么文件夹内肯定存在保存数据的txt文件，以此检验是否存在文件夹
	}	//如果不经过这个if语句，则检查文本文件是否存在，用作重名检测 
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
 *  @description : 将文件的信息录入_save.txt 文件 
 *  @param       : CurFloder char *input   保存文件信息链表的的结构体
 *                 const char *filerote    要操作的目录的路径（不用加_save.txt，函数会自动加上_save.txt,只要该目录的路径） 
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
	strcpy(copyfilerote, filerote);//复制获得的路径 
	strcat(copyfilerote, a);//在路径后加上_save.txt这个文件名 
	w = fopen(copyfilerote, "w");
	if(w == NULL)
	{
		printf("文件<%s>打开失败",filerote); 
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
 *  @description : 从_save.txt 读取文件的信息
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *                 const char *filerote    目录的路径（不用加_save.txt，函数会自动加上_save.txt）
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
		printf("文件<%s>打开失败",filerote); 
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
 *  @description : 销毁链表 
 *  @param       :  CurFloder *des   保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
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
 *  @description : 相当于第二个主函数 
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
	CONSOLE_CURSOR_INFO cursor_info = {1, 1};//将光标显示 
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
	for(i = 0; rootpath[i] != '\0'; i++)//找到最后一个斜杆 
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
		printf("\n￥ ");
		gets(inputmessage);
		if(!strcmp(inputmessage, "Close"))//关闭程序 
		{
			system("cls");
			setColor(14,0);
			printf("\n\n\n\n\t\t\t\t\t*********************************\n");
			printf("\t\t\t\t\t*                               *\n"); 
			printf("\t\t\t\t\t*          Good Bye！           *\n"); 
			printf("\t\t\t\t\t*                               *\n");
			printf("\t\t\t\t\t*********************************\n");
			printf("\t\t\t\t\t");
			system("pause");
			exit(0);
		}	
		if(!strcmp(inputmessage, "Return"))//返回登陆界面 
		{
			rootpath[length] = '\0';
			break;
		}
		if(!strcmp(inputmessage, "help"))//输出所有命令 
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
								printf("\n输入指令错误！");
								continue;
							}	
						}
						else
						{
							printf("\n输入指令错误！");
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
									printf("\n输入指令错误！");
									continue;
								}
							}
							else
							{
								printf("\n输入指令错误！");
								continue;
							}
						}
						else
						{
							printf("\n输入指令错误！");
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
						printf("\n输入指令错误！");
						continue;
					}
				}
				else
				{
					for(i = 2; copychar[i] != '\0' && copychar[i] == ' '; i++);
					if(i == 2)
					{
						printf("\n输入指令错误！");
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
							printf("\n输入指令错误！");
							continue;
						}
					}
					else
					{
						printf("\n输入指令错误！");
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
							printf("\n输入指令错误！");
							continue;
						}
						for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
						if(copychar[i] == '\0')
							userchoice = 9;
						else
						{
							printf("\n输入指令错误！");
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
								printf("\n输入指令错误！");
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
								printf("\n输入指令错误！");
								continue;
							}
						}
						else
						{
							printf("\n输入指令错误！");
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
								printf("\n输入指令错误！");
								continue;
							}
							for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
							if(copychar[i] == '\0')
								userchoice = 11;
							else
							{
								printf("\n输入指令错误！");
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
								printf("\n输入指令错误！");
								continue;
							}
							for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
							if(copychar[i] == '\0')
								userchoice = 10;
							else
							{
								printf("\n输入指令错误！");
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
									printf("\n输入指令错误！");
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
										printf("\n输入指令错误！");
										continue;
									}
									for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
									if(copychar[i] == '\0')
										userchoice = 13;
									else
									{
										printf("\n输入指令错误！");
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
											printf("\n输入指令错误！");
											continue;
										}
										for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
										if(copychar[i] == '\0')
											userchoice = 14;
										else
										{
											printf("\n输入指令错误！");
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
												printf("\n输入指令错误！");
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
													printf("\n输入指令错误！");
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
													printf("\n输入指令错误！");
													continue;
												}
											}
							}
							else
							{
								printf("\n输入指令错误！");
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
									printf("\n输入指令错误！");
									continue;
								}
								for(i; copychar[i] != '\0' && copychar[i] == ' '; i++);
								if(copychar[i] == '\0')
								{
									userchoice = 17;
								}
								else
								{
									printf("\n输入指令错误！");
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
										printf("\n输入指令错误！");
										continue;
									}
								}
								else
								{
									printf("\n输入指令错误！");
									continue;
								}
		switch(userchoice)
		{
			case 1://显示当前目录下的文件和文件夹 
				PrintCurrentFloder(head);
				break;
			case 2://树状显示所有文件（文件和文件夹） 
				printf("根目录为：%s", rootpath);
				printf("\n__");
				PrintTree(rootpath , 1, " ");
				printf("\n");
				break;
			case 3:// 按绝对路径  相对路径  当前目录   显示所有文件包括子文件 
				PrintPathFloder(firstmessage);
				break;
			case 4://模糊搜索文件名   可绝对路径  相对路径 当前目录 
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
					printf("\n输入路径错误！");
					break; 
				}
				LsGrep(firstmessage,secondmessage);
				break;
			case 5://返回上一级 
				CdReturn(head);
				break;
			case 6://进入目标路径 可当前目录 绝对路径  相对路径 
				CdSwitch(head, firstmessage);
				break;
			case 7://移动文件  可当前目录 绝对路径  相对路径  
				movefile(firstmessage, secondmessage);
				break;
			case 8://重命名只能当前目录下操作 
				MVRename(head, firstmessage, secondmessage);
				break;
			case 9://移动文件夹  可当前目录 绝对路径  相对路径 
				movefolder(firstmessage, secondmessage);
				break;
			case 10://删除文件 只能当前目录下操作 
				for(i = 0; firstmessage[i] != '\0'; i++);
				if(firstmessage[i - 1] != 't' || firstmessage[i - 2] != 'x' || firstmessage[i - 3] != 't' || firstmessage[i - 4] != '.')
				{
					printf("\n输入的非笔记文件！");
					break;
				}
				DeleteFOF(head,firstmessage);
				break;
			case 11://删除文件夹 只能当前目录下操作
				for(i = 0; firstmessage[i] != '\0'; i++);
				if(firstmessage[i - 1] == 't' && firstmessage[i - 2] == 'x' && firstmessage[i - 3] == 't' && firstmessage[i - 4] == '.')
				{
					printf("\n输入的非笔记文件夹！");
					break;
				}
				DeleteFOF(head,firstmessage);
				break;
			case 12://输出当前目录下的文件或文件夹的标签 
				PrintAppointTag(head, firstmessage);
				break;
			case 13://为当前目录下指定文件或文件夹添加指定标签 
				AddAppointTag(head, firstmessage, secondmessage);
				break;
			case 14://为当前目录下指定文件或文件夹删除指定标签 
				DeleteAppointTag(head, firstmessage, secondmessage);
				break;
			case 15://模糊查找当前目录下标签符合条件的文件或文件夹 
				PrintCurFloderTag(head, firstmessage);
				break;
			case 16:// 模糊查找所有标签符合条件的文件 
				savesum = 0;
				SearchTag(firstmessage, rootpath, &savesum);
				printf("\n符合条件的文件总数为：%d",savesum);
				break;
			case 17://创建文件夹  只能当前目录下操作 
				MakeFOF(head,firstmessage);
				break;
			case 18:// 输入路径排序 可当前目录  绝对路径  相对路径 
				FileSort(firstmessage, head);
				break;
			case 19:// 树状输出所有文件夹 
				printf("根目录为：%s", rootpath);
				printf("\n__");
				PrintTree(rootpath , 0, " ");
				printf("\n");
				break;
			default : ;
		}
	}

}
