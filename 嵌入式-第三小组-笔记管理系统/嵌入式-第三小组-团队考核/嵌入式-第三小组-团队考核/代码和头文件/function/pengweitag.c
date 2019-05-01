#include "../head/NoteManagementSystem.h"
#include "../head/linwenchen.h"
#include "../head/pengweitag.h"

extern char rootpath[200];//�洢�û�·��         CurFloder *currentfile//�洢�ļ���Ϣ 
extern char currentpath[200];//�洢��ǰ·��

/**
 *  @name        : Status AddTag(FOF *e, char *s)
 *  @description : ��ӱ�ǩ 
 *  @param       : FOF *e �ļ��ڵ�
 				   char *s ��ǩ���� 
 *  @return      : Status
 *  @Author		 :����� 
 */	
Status AddTag(FOF *e, char *s)
{
	Tag *tagp, *tagnode;
	
	tagnode = (Tag *)malloc(sizeof(Tag));//�����½ڵ�
	if(tagnode == NULL)
		return ERRORS;
		
	*(tagnode->info) = '\0';		
	strcpy(tagnode->info, s);		
	tagnode->next = NULL;
	if(e->taghead != NULL)
	{
		tagp = e->taghead;
		while(tagp->next != NULL)//�ҵ����һ����ǩ�ڵ� 
			tagp = tagp->next;
		tagp->next = tagnode;
		e->num++;
		return SUCCESS;		
	}
	else
		e->taghead = tagnode;
	e->num++;
	return SUCCESS;		
} 

/**
 *  @name        : Status DeleteTag(FOF *e, char *s)
 *  @description : ɾ����ǩ
 *  @param       : FOF e �ļ��ڵ�
 				   char *s ��ǩ����
 *  @return      : ɾ���ɹ�����SUCCESS�����򷵻�ERROR
 *  @Author		 :����� 
 */	
Status DeleteTag(FOF *e, char *s)
{
	Tag *tagp, *tagnode;
	if(e->taghead == NULL)//�ж�ԭ���Ƿ��б�ǩ 
		return ERRORS;
	else
	{
		tagp = e->taghead;
	}
	
	if(strcmp(tagp->info, s) != 0)
	{
		while(tagp->next!=NULL && strcmp(tagp->next->info, s))//�ж���һ����ǩ�ڵ��Ƿ��Ǹñ�ǩ 
		{
			if(tagp->next == NULL)
				return ERRORS;			
			tagp = tagp->next;
		} 
			
		
		if(tagp->next == NULL)
		{
			printf("\nû���ҵ��ñ�ǩ");
			return ERRORS;
		}
			
		tagnode = tagp->next;
		tagp->next = tagnode->next;
		free(tagnode);
		e->num--;
		printf("\n�ɹ�ɾ���ñ�ǩ\"%s\"", s);
		return SUCCESS; 		
	}
	else
	{
		tagnode = e->taghead;
		e->taghead = tagnode->next;
		e->num--;
		printf("\n�ɹ�ɾ���ñ�ǩ\"%s\"", s);
		free(tagnode);
		return SUCCESS;		
	}

}

/**
 *  @name        : Status FindTag(FOF *e,char *s)
 *  @description : ����/ƥ���ǩ
 *  @param       : FOF *e �ļ��ڵ�
 				   char *s ��ǩ���� 
 *  @return      : ���ҳɹ�����SUCCESS�����򷵻�ERROR
 *  @Author		 :����� 
 */
Status FindTag(FOF *e, char *s)
{
	Tag *tagp;
	if(e->taghead == NULL)//�ж�ԭ���Ƿ��б�ǩ 
		return ERRORS;
	else
		tagp = e->taghead;
	if(strcmp(tagp->info, s) != 0)//�ж�ͷ����ǲ�������Ҫ�ҵı�ǩ 
	{
		while(tagp->next!=NULL && strcmp(tagp->next->info, s))//�ж���һ����ǩ�ڵ��Ƿ��Ǹñ�ǩ 
			tagp = tagp->next;
		if(tagp->next == NULL)
		{
			return ERRORS;
		} 
		else
		{
			return SUCCESS; 
		}		
	}
	else
	{
		return SUCCESS;		
	}	
	
}

/**
 *  @name        : void PrintTag(FOF e)
 *  @description : ��ӡ��ǩ
 *  @param       : FOF e �ļ��ڵ�
 *  @return      : void
 *  @Author		 :����� 
 */
void PrintTag(FOF e)
{
	if(e.num == 0)return;
	Tag *temp = e.taghead;
	int sum = e.num;
	while(sum--)
	{
		printf("   \"%s\"   ",temp->info);
		temp = temp->next;
	}
	
}



/**
 *  @name        : void PrintAppointTag(CurFloder *read, char *name)
 *  @description : ��ʾָ�����ļ����ļ��б�ǩ
 *  @param       :  CurFloder *read ��ǰ�ļ���Ϣ�ṹ�� 
 					char *name �ļ������ļ����� 
 *  @return      : None
 *  @Author		 :����� 
 */
void PrintAppointTag(CurFloder *read, char *name)
{	
	FOF *fofnode; 
	int judge = 0;//�ж��Ƿ��ҵ����ļ� 
	
    fofnode = read->F;

	while(fofnode != NULL)//�����ǰ�ļ��ı�ǩ��Ϣ 
	{
		if(strcmp(name, fofnode->name) == 0)//�ж��Ƿ���ļ������ļ��� 
		{
			printf("\n�ļ�<%s>�ı�ǩΪ��",name);
			PrintTag(*fofnode);
			judge = 1;		
			break;
		} 
		fofnode = fofnode->next;
	}
	if(judge == 0)
	{
		printf("\n<%s>���ļ�������", name);
	} 
	
}

/**
 *  @name        : void AddAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : Ϊָ�����ļ����ļ��мӱ�ǩ
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *name �ļ������ļ����� 
 				   char *tag  ��ǩ���� 
 *  @return      : None
 *  @Author		 :����� 
 */
void AddAppointTag(CurFloder *read, char *name, char *tag)
{ 
	FOF *fofnode;
	char copy[400];
	fofnode = read->F;
	
	while(fofnode != NULL)//�жϵ�ǰ�ļ��ı�ǩ��Ϣ 
	{
		if(strcmp(name, fofnode->name) == 0)//�ж��Ƿ���ļ������ļ��� 
		{
			if(FindTag(fofnode,tag)==SUCCESS)
			{
				printf("\n��ǩ�Ѵ��ڣ�");
				return ;
			}
			else
			{
				AddTag(fofnode, tag);//��ӱ�ǩ	
				printf("\n��ǩ��ӳɹ���");
				break;
			} 
			
		} 
		fofnode = fofnode->next;
	}
	if(fofnode == NULL)
	{
		printf("\n������ļ������ڣ�");
		return; 
	 } 
	strcpy(copy, currentpath);
	strcat(copy, "\\");
	strcat(copy, name);
	InputLog("��ӱ�ǩ���ļ�/�ļ��е�·����", copy,"��ӵı�ǩ����",tag);
	Input_Save(read, currentpath);	//������� 
}


/**
 *  @name        : void DeleteAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : Ϊɾ��ָ�����ļ����ļ��б�ǩ
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *name �ļ������ļ����� 
 				   char *tag  ��ǩ���� 
 *  @return      : None
 *  @Author		 :����� 
 */
void DeleteAppointTag(CurFloder *read, char *name, char *tag)
{
	FOF *fofnode; 
	char copy[400];
	fofnode = read->F;
	
	while(fofnode != NULL)//�����ǰ�ļ��ı�ǩ��Ϣ 
	{
		if(strcmp(name, fofnode->name) == 0)//�ж��Ƿ���ļ������ļ��� 
		{
			if(DeleteTag(fofnode, tag)==SUCCESS)
				break;
			else
			{
				printf("\n��ǩ�����ڣ�");
				return;
			}
		} 
		fofnode = fofnode->next;
	}
	if(fofnode == NULL)
	{
		printf("\n������ļ������ڣ�");
		return; 
	} 
	strcpy(copy, currentpath);
	strcat(copy, "\\");
	strcat(copy, name);
	InputLog("ɾ����ǩ���ļ�/�ļ��е�·����", copy,"ɾ���ı�ǩ����",tag);
	Input_Save(read, currentpath);	//������� 
}

/**
 *  @name        : void PrintCurFloderTag(CurFloder *read, char *tag)
 *  @description : ���ƥ��tag�ıʼ��ļ���
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *tag  ��ǩ���� 
 *  @return      : None
 *  @Author		 :����� 
 */
void PrintCurFloderTag(CurFloder *current, char *tag)//���ƥ��tag�ıʼ��ļ���
{
	FOF *fofnode = current->F;
	Tag *ptag;
	int flag;
	flag = 0;
	while(fofnode!=NULL)
	{		
		ptag = fofnode->taghead;
		while(ptag!=NULL)
		{
			if(Checkstr(ptag->info,tag)==SUCCESS)//�������
			{
				flag = 1;
				if(fofnode->flag == 1) 
					printf("\n  �ʼ��ļ�����%s",fofnode->name);//����ļ���
				else
					printf("\n�ʼ��ļ�������%s",fofnode->name);//����ļ���
				break;
			}
			ptag = ptag->next;
		}
		fofnode = fofnode->next;
	}
	if(!flag)
		printf("\n�ļ������ڣ�");
}
