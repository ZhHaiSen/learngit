#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../head/NoteManagementSystem.h"
#include "../head/moveFOF.h"

extern char rootpath[];//存储用户路径         CurFloder *currentfile
extern char currentpath[];//存储当前路径

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : 实现将一个笔记文件移动到一个笔记文件夹中 
 *  @param       : char x[]-移动的笔记文件名，可为绝对路径或者相对路径    char y[]-移向的笔记文件夹名，可为绝对路径或者相对路径 
 *  @return      : SUCCESS 表示移动成功      ERROR 表示移动失败 
 */
Status movefile(char x[],char y[])   //移动笔记文件 
{
	char copy[400];
	int LOOP=0,txt=0;   //判断标志位,判断是否为文件 
	int exist;   //路径存在 
	int i=0,count;            
	char x_entirepath[400],y_entirepath[400];   //保存x和y的绝对路径 
	for(i=0;x[i]!='\0';i++)
		if(x[i]=='.')
			txt=1;
	if(txt==1)
	{
		if(*x=='C'||*x=='D'||*x=='E'||*x=='F')   //判断x是否为绝对路径 
		if(*(x+1)==':')
			LOOP=1;
		if(LOOP==0)   //x不是绝对路径 
		{
			for(i=0;rootpath[i]!='\0';i++)
			{
				if(rootpath[i]=='\\')
					count=i;
			}
			char root[100],rootcmp[100];
			for(i=0;rootpath[count+i+1]!='\0';i++)
				root[i]=rootpath[count+i+1];
			root[i]='\0';
			for(i=0;x[i]!='\\'&&x[i]!='\0';i++)
				rootcmp[i]=x[i];
			rootcmp[i]='\0';
			if(strcmp(root,rootcmp)==0)
				LOOP=1;
			if(LOOP==0)
			{
				strcpy(x_entirepath,currentpath);
				strcat(x_entirepath, "\\");                  
				strcat(x_entirepath,x);   //绝对路径=当前路径+相对路径
			}
			else
			{
				for(i=0;rootpath[i]!='\0';i++)
				{
					if(rootpath[i]=='\\')
						count=i;
				}
				strncpy(x_entirepath,rootpath,count);
				strcat(x_entirepath,"\\");
				strcat(x_entirepath,x);
			}
		}
		else   //x为绝对路径 
		{
			strcat(x_entirepath,x);
		}	
		count=0;
		LOOP=0;
		if(*y=='C'||*y=='D'||*y=='E'||*y=='F')   //同理，对y做检测并得到绝对路径 
			if(*(y+1)==':')
				LOOP=1;
		if(LOOP==0)
		{
		   	for(i=0;rootpath[i]!='\0';i++)
			{
				if(rootpath[i]=='\\')
					count=i;
			}
			char root[100],rootcmp[100];
			for(i=0;rootpath[count+i+1]!='\0';i++)
				root[i]=rootpath[count+i+1];
			root[i]='\0';
			for(i=0;y[i]!='\\'&&y[i]!='\0';i++)
				rootcmp[i]=y[i];
			rootcmp[i]='\0';
			if(strcmp(root,rootcmp)==0)
				LOOP=1;
			if(LOOP==0)
			{
				strcpy(y_entirepath,currentpath);
				strcat(y_entirepath, "\\");                  
				strcat(y_entirepath,y);   //绝对路径=当前路径+相对路径
			}
			else
			{
				for(i=0;rootpath[i]!='\0';i++)
				{
					if(rootpath[i]=='\\')
						count=i;
				}
				strncpy(y_entirepath,rootpath,count);
				strcat(y_entirepath,"\\");
				strcat(y_entirepath,y);
			}
		}
		else
		{
			strcat(y_entirepath,y);
		}
		count=0;
		LOOP=0;
		exist=RoteExistence(x_entirepath,1);   //x路径是否正确 
		if(exist==0)
		{
			printf("输入的文件路径有误\n");
			return ERRORS;
		}
		strcpy(copy, x_entirepath);
		exist=0;
		exist=RoteExistence(y_entirepath,0);   //y路径是否正确 
		if(exist==0)
		{
			printf("输入的文件夹路径有误\n");
			return ERRORS;
		}
		exist=0;
		char temp[400];   //保存文件名 
		for(i=0;x_entirepath[i]!='\0';i++)
		{
			if(x_entirepath[i]=='\\')   //得到最后一个/的位置，并认为之后就是文件名 
				count=i;
		}
		for(i=0;x_entirepath[count+1+i]!='\0';i++)
			temp[i]=x_entirepath[count+1+i];   //赋值文件名 
		temp[i] = '\0';                                                            
		char y_judge[400];   //判断y中是否有重名文件 
		strcpy(y_judge,y_entirepath);
		strcat(y_judge, "\\");                                                  
		strcat(y_judge,temp);   //在y的绝对路径后加上文件名 
		exist=RoteExistence(y_judge, 1);   //检测是否有重名 
		if(exist==1)
		{
			//rename(y_judge);   //有重名                                          
			printf("\n移动到的文件夹含同名文件！移动失败！");
			return ERRORS; 
		/*此处没有函数，不好完成*/ 
		}
		exist=0;
		char x_linklist[400];   //得到x的上一级目录，用于更改其save.txt中的记录 
		for(i=0;i<count;i++)
			x_linklist[i]=x_entirepath[i];   //x的绝对路径除去文件名及两个\\就是x的上一级目录 
		x_linklist[i]='\0';
		CurFloder *trans;   //获取save.txt中的内容 
		FOF *p1,*p2,*p;   //在链表中增加、删除节点 
		trans=(CurFloder *)malloc(sizeof(CurFloder));
		if(trans==NULL)
		{
			printf("\n内存不足");
			return ERRORS;
		}
		trans->F=NULL;
		Read_Save(trans,x_linklist);   //从save.txt中读取信息 
		if(strcmp(trans->F->name,temp)==0)   //save.txt中第一个元素就是待删除元素 
		{
			p1=trans->F;
			trans->F=p1->next;
			p=p1;
		}
		else   //save.txt中待删除元素不是第一个 
		{
			for(p1=trans->F,p2=trans->F->next;p2!=NULL;)
			{
				if(strcmp(p2->name,temp)==0)
				{
					p1->next=p2->next;
					p=p2;   //保留待删除元素的信息的节点 
					break;
				}
				p1=p2;
				p2=p2->next;
			}
		}
		Input_Save(trans,x_linklist);   //新的链表存入x的上一级目录的save.txt中 
		DestroyFof(trans);
		trans->F=NULL;
		Read_Save(trans,y_entirepath);   //读取y的save.txt中的信息 
		p->next=NULL;   //之前要删除的节点指向空 										
		if(trans->F != NULL)
		{
			for(p1=trans->F;p1->next!=NULL;p1=p1->next)   //得到最后一个节点 
				;
			p1->next=p;   //之前要删除的节点作为最后一个节点 
		}
		else
			trans->F = p;
		InputLog("被移动的文件的路径：", copy, "移动到的文件夹的路径：", y_entirepath);
		Input_Save(trans,y_entirepath);   //将新的链表信息存入y的save.txt中 
		DestroyFof(trans);
		char movefile[400]="move ";   //文件移动 
		strcat(movefile,x_entirepath);
		strcat(movefile," ");
		strcat(movefile,y_entirepath);
		system(movefile);
	}
	else
		printf("请输入文件名\n");
	return SUCCESS;
}

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : 实现将一个笔记文件夹移动到一个笔记文件夹中 
 *  @param       : char x[]-移动的笔记文件夹名，可为绝对路径或者相对路径    char y[]-移向的笔记文件夹名，可为绝对路径或者相对路径 
 *  @return      : SUCCESS 表示移动成功      ERROR 表示移动失败 
 */
Status movefolder(char x[],char y[])   //移动笔记文件 
{
	char copy[400];
	int LOOP=0,txt=1;   //判断标志位,判断是否为文件夹 
	int exist;   //路径存在 
	int i=0,count;                          
	char x_entirepath[400],y_entirepath[400];   //保存x和y的绝对路径 
	for(i=0;x[i]!='\0';i++)
		if(x[i]=='.')
			txt=0;
	if(txt==1)
	{
		if(*x=='C'||*x=='D'||*x=='E'||*x=='F')   //判断x是否为绝对路径 
			if(*(x+1)==':')
				LOOP=1;
		if(LOOP==0)   //x是相对路径 
		{
			for(i=0;rootpath[i]!='\0';i++)
			{
				if(rootpath[i]=='\\')
					count=i;
			}
			char root[100],rootcmp[100];
			for(i=0;rootpath[count+i+1]!='\0';i++)
				root[i]=rootpath[count+i+1];
			root[i]='\0';
			for(i=0;x[i]!='\\'&&x[i]!='\0';i++)
				rootcmp[i]=x[i];
			rootcmp[i]='\0';
			if(strcmp(root,rootcmp)==0)
				LOOP=1;
			if(LOOP==0)
			{
				strcpy(x_entirepath,currentpath);
				strcat(x_entirepath, "\\");                  
				strcat(x_entirepath,x);   //绝对路径=当前路径+相对路径
			}
			else
			{
				for(i=0;rootpath[i]!='\0';i++)
				{
					if(rootpath[i]=='\\')
						count=i;
				}
				strncpy(x_entirepath,rootpath,count);
				strcat(x_entirepath,"\\");
				strcat(x_entirepath,x);
			} 
		}
		else   //x为绝对路径 
		{
			strcat(x_entirepath,x);
		}
		count=0;
		LOOP=0;
		if(*y=='C'||*y=='D'||*y=='E'||*y=='F')   //同理，对y做检测并得到绝对路径 
			if(*(y+1)==':')
				LOOP=1;
		if(LOOP==0)
		{
		   	for(i=0;rootpath[i]!='\0';i++)
			{
				if(rootpath[i]=='\\')
					count=i;
			}
			char root[100],rootcmp[100];
			for(i=0;rootpath[count+i+1]!='\0';i++)
				root[i]=rootpath[count+i+1];
			root[i]='\0';
			for(i=0;y[i]!='\\'&&y[i]!='\0';i++)
				rootcmp[i]=y[i];
			rootcmp[i]='\0';
			if(strcmp(root,rootcmp)==0)
				LOOP=1;
			if(LOOP==0)
			{
				strcpy(y_entirepath,currentpath);
				strcat(y_entirepath, "\\");                  
				strcat(y_entirepath,y);   //绝对路径=当前路径+相对路径
			}
			else
			{
				for(i=0;rootpath[i]!='\0';i++)
				{
					if(rootpath[i]=='\\')
						count=i;
				}
				strncpy(y_entirepath,rootpath,count);
				strcat(y_entirepath,"\\");
				strcat(y_entirepath,y);
			}
		}
		else
		{
			strcat(y_entirepath,y);
		}
		count=0;
		LOOP=0;	
		exist=RoteExistence(x_entirepath,0);   //x路径是否正确 
		if(exist==0)
		{
			printf("输入的文件路径有误\n");
			return ERRORS;
		}
		exist=0;
		exist=RoteExistence(y_entirepath,0);   //y路径是否正确 
		if(exist==0)
		{
			printf("输入的文件夹路径有误\n");
			return ERRORS;
		}
		exist=0;
		char temp[400];   //保存文件名 
		for(i=0;x_entirepath[i]!='\0';i++)
		{
			if(x_entirepath[i]=='\\')   //得到最后一个/的位置，并认为之后就是文件名 
				count=i;
		}
		strcpy(copy, x_entirepath);
		for(i=0;x_entirepath[count+1+i]!='\0';i++)
			temp[i]=x_entirepath[count+1+i];   //赋值文件名 
		temp[i] = '\0';                          
		char y_judge[400];   //判断y中是否有重名文件 
		strcpy(y_judge,y_entirepath);
		strcat(y_judge, "\\");                           
		strcat(y_judge,temp);   //在y的绝对路径后加上文件名 
		exist=RoteExistence(y_judge, 0);   //检测是否有重名 
		if(exist==1)
		{
			//rename(y_judge);   //有重名                             
			printf("\n移动到的文件夹含同名文件！移动失败！");
			return ERRORS; 
			/*此处没有函数，不好完成*/ 
		}
		exist=0;
		char x_linklist[400];   //得到x的上一级目录，用于更改其save.txt中的记录 
		for(i=0;i<count;i++)
			x_linklist[i]=x_entirepath[i];   //x的绝对路径除去文件名及两个\\就是x的上一级目录 
		x_linklist[i]='\0';
		CurFloder *trans;   //获取save.txt中的内容 
		FOF *p1,*p2,*p;   //在链表中增加、删除节点 
		trans=(CurFloder *)malloc(sizeof(CurFloder));
		if(trans==NULL)
		{
			printf("\n内存不足");
			return ERRORS;
		}
		trans->F=NULL;
		Read_Save(trans,x_linklist);   //从save.txt中读取信息 
		if(strcmp(trans->F->name,temp)==0)   //save.txt中第一个元素就是待删除元素 
		{
			p1=trans->F;
			trans->F=p1->next;
			p=p1;
		}
		else   //save.txt中待删除元素不是第一个 
		{
			for(p1=trans->F,p2=trans->F->next;p2!=NULL;)
			{
				if(strcmp(p2->name,temp)==0)
				{
					p1->next=p2->next;
					p=p2;   //保留待删除元素的信息的节点 
					break;
				}
				p1=p2;
				p2=p2->next;
			}
		}
		Input_Save(trans,x_linklist);   //新的链表存入x的上一级目录的save.txt中 
		DestroyFof(trans);
		trans->F=NULL;
		Read_Save(trans,y_entirepath);   //读取y的save.txt中的信息 
		p->next=NULL;   //之前要删除的节点指向空 						
		if(trans->F != NULL)
		{
			for(p1=trans->F;p1->next!=NULL;p1=p1->next)   //得到最后一个节点 
				;
			p1->next=p;   //之前要删除的节点作为最后一个节点 
		}
		else
			trans->F = p;
		
		InputLog("被移动的文件夹的路径：", copy, "移动到的文件夹的路径：", y_entirepath);
		Input_Save(trans,y_entirepath);   //将新的链表信息存入y的save.txt中 
		DestroyFof(trans);
		char movefile[400]="move ";   //文件移动 
		strcat(movefile,x_entirepath);
		strcat(movefile," ");
		strcat(movefile,y_entirepath);
		system(movefile);
	}
	else
		printf("请输入文件夹名\n");
	return SUCCESS;
}

void print_help()   //答应帮助菜单 
{
	printf("                              ls :\t显示当前目录下所有文件和文件夹\n");
	printf("                           ls -a :\t以树状结构显示所有文件\\文件夹\n");
	printf("                          ls -a1 :\t以树状结构显示所有文件夹\n");
	printf("               ls 笔记文件夹路径 :\t按绝对路径\\相对路径\\当前目录，显示该文件夹下所有内容\n");
	printf(" ls 笔记文件夹路径 grep 搜索内容 :\t按绝对路径\\相对路径\\当前目录，模糊搜索文件名\n");
	printf("                            cd.. :\t返回上一级\n");
	printf("               cd 笔记文件夹路径 :\t按绝对路径\\相对路径\\当前目录，进入目标路径\n");
	printf("    mv 笔记文件名 笔记文件夹目录 :\t按绝对路径\\相对路径\\当前目录，（文件与文件夹均可），笔记文件移动到笔记文件夹目录\n");
	printf("  mv 笔记原文件名 笔记目标文件名 :\t按当前目录，重命名笔记文件\n");
	printf(" mv -r 笔记文件夹 目标笔记文件夹 :\t按绝对路径\\相对路径\\当前目录，笔记文件夹移动到目标笔记文件夹\n");
	printf("                   rm 笔记文件名 :\t按当前目录，删除笔记文件\n");
	printf("              rm -r 笔记文件夹名 :\t按当前目录，删除笔记文件夹及其中所有内容\n");
	printf("     tag 笔记文件名\\笔记文件夹名 :\t按当前目录，输出文件\\文件夹的标签\n");
	printf("tag -add 笔记文件名\\笔记文件夹名 :\t按当前目录，为文件\\文件夹添加指定标签\n");
	printf("tag -del 笔记文件名\\笔记文件夹名 :\t按当前目录，删除文件\\文件夹指定标签\n");
	printf("                 tag -s 标签内容 :\t按当前目录，模糊查找标签符合条件的文件\\文件夹\n");
	printf("                tag -sa 标签内容 :\t对所有文件\\文件夹，模糊查找标签符合条件的文件\\文件夹\n");
    printf("      md 笔记文件名\\笔记文件夹名 :\t按当前目录，创建给定名字的笔记文件\\笔记文件夹\n");
	printf("               sort 笔记文件夹名 :\t按绝对路径\\相对路径\\当前目录，对文件夹内容排序\n");
	printf("                           help  :\t显示帮助界面\n");
	printf("                           Close :\t关闭程序\n");
	printf("                          Return :\t返回登陆界面\n");
}
