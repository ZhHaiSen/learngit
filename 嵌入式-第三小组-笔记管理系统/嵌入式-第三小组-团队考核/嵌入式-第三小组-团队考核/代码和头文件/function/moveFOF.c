#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../head/NoteManagementSystem.h"
#include "../head/moveFOF.h"

extern char rootpath[];//�洢�û�·��         CurFloder *currentfile
extern char currentpath[];//�洢��ǰ·��

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : ʵ�ֽ�һ���ʼ��ļ��ƶ���һ���ʼ��ļ����� 
 *  @param       : char x[]-�ƶ��ıʼ��ļ�������Ϊ����·���������·��    char y[]-����ıʼ��ļ���������Ϊ����·���������·�� 
 *  @return      : SUCCESS ��ʾ�ƶ��ɹ�      ERROR ��ʾ�ƶ�ʧ�� 
 */
Status movefile(char x[],char y[])   //�ƶ��ʼ��ļ� 
{
	char copy[400];
	int LOOP=0,txt=0;   //�жϱ�־λ,�ж��Ƿ�Ϊ�ļ� 
	int exist;   //·������ 
	int i=0,count;            
	char x_entirepath[400],y_entirepath[400];   //����x��y�ľ���·�� 
	for(i=0;x[i]!='\0';i++)
		if(x[i]=='.')
			txt=1;
	if(txt==1)
	{
		if(*x=='C'||*x=='D'||*x=='E'||*x=='F')   //�ж�x�Ƿ�Ϊ����·�� 
		if(*(x+1)==':')
			LOOP=1;
		if(LOOP==0)   //x���Ǿ���·�� 
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
				strcat(x_entirepath,x);   //����·��=��ǰ·��+���·��
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
		else   //xΪ����·�� 
		{
			strcat(x_entirepath,x);
		}	
		count=0;
		LOOP=0;
		if(*y=='C'||*y=='D'||*y=='E'||*y=='F')   //ͬ����y����Ⲣ�õ�����·�� 
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
				strcat(y_entirepath,y);   //����·��=��ǰ·��+���·��
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
		exist=RoteExistence(x_entirepath,1);   //x·���Ƿ���ȷ 
		if(exist==0)
		{
			printf("������ļ�·������\n");
			return ERRORS;
		}
		strcpy(copy, x_entirepath);
		exist=0;
		exist=RoteExistence(y_entirepath,0);   //y·���Ƿ���ȷ 
		if(exist==0)
		{
			printf("������ļ���·������\n");
			return ERRORS;
		}
		exist=0;
		char temp[400];   //�����ļ��� 
		for(i=0;x_entirepath[i]!='\0';i++)
		{
			if(x_entirepath[i]=='\\')   //�õ����һ��/��λ�ã�����Ϊ֮������ļ��� 
				count=i;
		}
		for(i=0;x_entirepath[count+1+i]!='\0';i++)
			temp[i]=x_entirepath[count+1+i];   //��ֵ�ļ��� 
		temp[i] = '\0';                                                            
		char y_judge[400];   //�ж�y���Ƿ��������ļ� 
		strcpy(y_judge,y_entirepath);
		strcat(y_judge, "\\");                                                  
		strcat(y_judge,temp);   //��y�ľ���·��������ļ��� 
		exist=RoteExistence(y_judge, 1);   //����Ƿ������� 
		if(exist==1)
		{
			//rename(y_judge);   //������                                          
			printf("\n�ƶ������ļ��к�ͬ���ļ����ƶ�ʧ�ܣ�");
			return ERRORS; 
		/*�˴�û�к������������*/ 
		}
		exist=0;
		char x_linklist[400];   //�õ�x����һ��Ŀ¼�����ڸ�����save.txt�еļ�¼ 
		for(i=0;i<count;i++)
			x_linklist[i]=x_entirepath[i];   //x�ľ���·����ȥ�ļ���������\\����x����һ��Ŀ¼ 
		x_linklist[i]='\0';
		CurFloder *trans;   //��ȡsave.txt�е����� 
		FOF *p1,*p2,*p;   //�����������ӡ�ɾ���ڵ� 
		trans=(CurFloder *)malloc(sizeof(CurFloder));
		if(trans==NULL)
		{
			printf("\n�ڴ治��");
			return ERRORS;
		}
		trans->F=NULL;
		Read_Save(trans,x_linklist);   //��save.txt�ж�ȡ��Ϣ 
		if(strcmp(trans->F->name,temp)==0)   //save.txt�е�һ��Ԫ�ؾ��Ǵ�ɾ��Ԫ�� 
		{
			p1=trans->F;
			trans->F=p1->next;
			p=p1;
		}
		else   //save.txt�д�ɾ��Ԫ�ز��ǵ�һ�� 
		{
			for(p1=trans->F,p2=trans->F->next;p2!=NULL;)
			{
				if(strcmp(p2->name,temp)==0)
				{
					p1->next=p2->next;
					p=p2;   //������ɾ��Ԫ�ص���Ϣ�Ľڵ� 
					break;
				}
				p1=p2;
				p2=p2->next;
			}
		}
		Input_Save(trans,x_linklist);   //�µ��������x����һ��Ŀ¼��save.txt�� 
		DestroyFof(trans);
		trans->F=NULL;
		Read_Save(trans,y_entirepath);   //��ȡy��save.txt�е���Ϣ 
		p->next=NULL;   //֮ǰҪɾ���Ľڵ�ָ��� 										
		if(trans->F != NULL)
		{
			for(p1=trans->F;p1->next!=NULL;p1=p1->next)   //�õ����һ���ڵ� 
				;
			p1->next=p;   //֮ǰҪɾ���Ľڵ���Ϊ���һ���ڵ� 
		}
		else
			trans->F = p;
		InputLog("���ƶ����ļ���·����", copy, "�ƶ������ļ��е�·����", y_entirepath);
		Input_Save(trans,y_entirepath);   //���µ�������Ϣ����y��save.txt�� 
		DestroyFof(trans);
		char movefile[400]="move ";   //�ļ��ƶ� 
		strcat(movefile,x_entirepath);
		strcat(movefile," ");
		strcat(movefile,y_entirepath);
		system(movefile);
	}
	else
		printf("�������ļ���\n");
	return SUCCESS;
}

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : ʵ�ֽ�һ���ʼ��ļ����ƶ���һ���ʼ��ļ����� 
 *  @param       : char x[]-�ƶ��ıʼ��ļ���������Ϊ����·���������·��    char y[]-����ıʼ��ļ���������Ϊ����·���������·�� 
 *  @return      : SUCCESS ��ʾ�ƶ��ɹ�      ERROR ��ʾ�ƶ�ʧ�� 
 */
Status movefolder(char x[],char y[])   //�ƶ��ʼ��ļ� 
{
	char copy[400];
	int LOOP=0,txt=1;   //�жϱ�־λ,�ж��Ƿ�Ϊ�ļ��� 
	int exist;   //·������ 
	int i=0,count;                          
	char x_entirepath[400],y_entirepath[400];   //����x��y�ľ���·�� 
	for(i=0;x[i]!='\0';i++)
		if(x[i]=='.')
			txt=0;
	if(txt==1)
	{
		if(*x=='C'||*x=='D'||*x=='E'||*x=='F')   //�ж�x�Ƿ�Ϊ����·�� 
			if(*(x+1)==':')
				LOOP=1;
		if(LOOP==0)   //x�����·�� 
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
				strcat(x_entirepath,x);   //����·��=��ǰ·��+���·��
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
		else   //xΪ����·�� 
		{
			strcat(x_entirepath,x);
		}
		count=0;
		LOOP=0;
		if(*y=='C'||*y=='D'||*y=='E'||*y=='F')   //ͬ����y����Ⲣ�õ�����·�� 
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
				strcat(y_entirepath,y);   //����·��=��ǰ·��+���·��
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
		exist=RoteExistence(x_entirepath,0);   //x·���Ƿ���ȷ 
		if(exist==0)
		{
			printf("������ļ�·������\n");
			return ERRORS;
		}
		exist=0;
		exist=RoteExistence(y_entirepath,0);   //y·���Ƿ���ȷ 
		if(exist==0)
		{
			printf("������ļ���·������\n");
			return ERRORS;
		}
		exist=0;
		char temp[400];   //�����ļ��� 
		for(i=0;x_entirepath[i]!='\0';i++)
		{
			if(x_entirepath[i]=='\\')   //�õ����һ��/��λ�ã�����Ϊ֮������ļ��� 
				count=i;
		}
		strcpy(copy, x_entirepath);
		for(i=0;x_entirepath[count+1+i]!='\0';i++)
			temp[i]=x_entirepath[count+1+i];   //��ֵ�ļ��� 
		temp[i] = '\0';                          
		char y_judge[400];   //�ж�y���Ƿ��������ļ� 
		strcpy(y_judge,y_entirepath);
		strcat(y_judge, "\\");                           
		strcat(y_judge,temp);   //��y�ľ���·��������ļ��� 
		exist=RoteExistence(y_judge, 0);   //����Ƿ������� 
		if(exist==1)
		{
			//rename(y_judge);   //������                             
			printf("\n�ƶ������ļ��к�ͬ���ļ����ƶ�ʧ�ܣ�");
			return ERRORS; 
			/*�˴�û�к������������*/ 
		}
		exist=0;
		char x_linklist[400];   //�õ�x����һ��Ŀ¼�����ڸ�����save.txt�еļ�¼ 
		for(i=0;i<count;i++)
			x_linklist[i]=x_entirepath[i];   //x�ľ���·����ȥ�ļ���������\\����x����һ��Ŀ¼ 
		x_linklist[i]='\0';
		CurFloder *trans;   //��ȡsave.txt�е����� 
		FOF *p1,*p2,*p;   //�����������ӡ�ɾ���ڵ� 
		trans=(CurFloder *)malloc(sizeof(CurFloder));
		if(trans==NULL)
		{
			printf("\n�ڴ治��");
			return ERRORS;
		}
		trans->F=NULL;
		Read_Save(trans,x_linklist);   //��save.txt�ж�ȡ��Ϣ 
		if(strcmp(trans->F->name,temp)==0)   //save.txt�е�һ��Ԫ�ؾ��Ǵ�ɾ��Ԫ�� 
		{
			p1=trans->F;
			trans->F=p1->next;
			p=p1;
		}
		else   //save.txt�д�ɾ��Ԫ�ز��ǵ�һ�� 
		{
			for(p1=trans->F,p2=trans->F->next;p2!=NULL;)
			{
				if(strcmp(p2->name,temp)==0)
				{
					p1->next=p2->next;
					p=p2;   //������ɾ��Ԫ�ص���Ϣ�Ľڵ� 
					break;
				}
				p1=p2;
				p2=p2->next;
			}
		}
		Input_Save(trans,x_linklist);   //�µ��������x����һ��Ŀ¼��save.txt�� 
		DestroyFof(trans);
		trans->F=NULL;
		Read_Save(trans,y_entirepath);   //��ȡy��save.txt�е���Ϣ 
		p->next=NULL;   //֮ǰҪɾ���Ľڵ�ָ��� 						
		if(trans->F != NULL)
		{
			for(p1=trans->F;p1->next!=NULL;p1=p1->next)   //�õ����һ���ڵ� 
				;
			p1->next=p;   //֮ǰҪɾ���Ľڵ���Ϊ���һ���ڵ� 
		}
		else
			trans->F = p;
		
		InputLog("���ƶ����ļ��е�·����", copy, "�ƶ������ļ��е�·����", y_entirepath);
		Input_Save(trans,y_entirepath);   //���µ�������Ϣ����y��save.txt�� 
		DestroyFof(trans);
		char movefile[400]="move ";   //�ļ��ƶ� 
		strcat(movefile,x_entirepath);
		strcat(movefile," ");
		strcat(movefile,y_entirepath);
		system(movefile);
	}
	else
		printf("�������ļ�����\n");
	return SUCCESS;
}

void print_help()   //��Ӧ�����˵� 
{
	printf("                              ls :\t��ʾ��ǰĿ¼�������ļ����ļ���\n");
	printf("                           ls -a :\t����״�ṹ��ʾ�����ļ�\\�ļ���\n");
	printf("                          ls -a1 :\t����״�ṹ��ʾ�����ļ���\n");
	printf("               ls �ʼ��ļ���·�� :\t������·��\\���·��\\��ǰĿ¼����ʾ���ļ�������������\n");
	printf(" ls �ʼ��ļ���·�� grep �������� :\t������·��\\���·��\\��ǰĿ¼��ģ�������ļ���\n");
	printf("                            cd.. :\t������һ��\n");
	printf("               cd �ʼ��ļ���·�� :\t������·��\\���·��\\��ǰĿ¼������Ŀ��·��\n");
	printf("    mv �ʼ��ļ��� �ʼ��ļ���Ŀ¼ :\t������·��\\���·��\\��ǰĿ¼�����ļ����ļ��о��ɣ����ʼ��ļ��ƶ����ʼ��ļ���Ŀ¼\n");
	printf("  mv �ʼ�ԭ�ļ��� �ʼ�Ŀ���ļ��� :\t����ǰĿ¼���������ʼ��ļ�\n");
	printf(" mv -r �ʼ��ļ��� Ŀ��ʼ��ļ��� :\t������·��\\���·��\\��ǰĿ¼���ʼ��ļ����ƶ���Ŀ��ʼ��ļ���\n");
	printf("                   rm �ʼ��ļ��� :\t����ǰĿ¼��ɾ���ʼ��ļ�\n");
	printf("              rm -r �ʼ��ļ����� :\t����ǰĿ¼��ɾ���ʼ��ļ��м�������������\n");
	printf("     tag �ʼ��ļ���\\�ʼ��ļ����� :\t����ǰĿ¼������ļ�\\�ļ��еı�ǩ\n");
	printf("tag -add �ʼ��ļ���\\�ʼ��ļ����� :\t����ǰĿ¼��Ϊ�ļ�\\�ļ������ָ����ǩ\n");
	printf("tag -del �ʼ��ļ���\\�ʼ��ļ����� :\t����ǰĿ¼��ɾ���ļ�\\�ļ���ָ����ǩ\n");
	printf("                 tag -s ��ǩ���� :\t����ǰĿ¼��ģ�����ұ�ǩ�����������ļ�\\�ļ���\n");
	printf("                tag -sa ��ǩ���� :\t�������ļ�\\�ļ��У�ģ�����ұ�ǩ�����������ļ�\\�ļ���\n");
    printf("      md �ʼ��ļ���\\�ʼ��ļ����� :\t����ǰĿ¼�������������ֵıʼ��ļ�\\�ʼ��ļ���\n");
	printf("               sort �ʼ��ļ����� :\t������·��\\���·��\\��ǰĿ¼�����ļ�����������\n");
	printf("                           help  :\t��ʾ��������\n");
	printf("                           Close :\t�رճ���\n");
	printf("                          Return :\t���ص�½����\n");
}
