#include "../head/NoteManagementSystem.h"
#include "../head/linwenchen.h"
#include "../head/pengweitag.h"

extern char rootpath[200];//存储用户路径         CurFloder *currentfile//存储文件信息 
extern char currentpath[200];//存储当前路径

/**
 *  @name        : Status AddTag(FOF *e, char *s)
 *  @description : 添加标签 
 *  @param       : FOF *e 文件节点
 				   char *s 标签内容 
 *  @return      : Status
 *  @Author		 :陈澎炜 
 */	
Status AddTag(FOF *e, char *s)
{
	Tag *tagp, *tagnode;
	
	tagnode = (Tag *)malloc(sizeof(Tag));//创建新节点
	if(tagnode == NULL)
		return ERRORS;
		
	*(tagnode->info) = '\0';		
	strcpy(tagnode->info, s);		
	tagnode->next = NULL;
	if(e->taghead != NULL)
	{
		tagp = e->taghead;
		while(tagp->next != NULL)//找到最后一个标签节点 
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
 *  @description : 删除标签
 *  @param       : FOF e 文件节点
 				   char *s 标签内容
 *  @return      : 删除成功返回SUCCESS，否则返回ERROR
 *  @Author		 :陈澎炜 
 */	
Status DeleteTag(FOF *e, char *s)
{
	Tag *tagp, *tagnode;
	if(e->taghead == NULL)//判断原来是否有标签 
		return ERRORS;
	else
	{
		tagp = e->taghead;
	}
	
	if(strcmp(tagp->info, s) != 0)
	{
		while(tagp->next!=NULL && strcmp(tagp->next->info, s))//判断下一个标签节点是否是该标签 
		{
			if(tagp->next == NULL)
				return ERRORS;			
			tagp = tagp->next;
		} 
			
		
		if(tagp->next == NULL)
		{
			printf("\n没有找到该标签");
			return ERRORS;
		}
			
		tagnode = tagp->next;
		tagp->next = tagnode->next;
		free(tagnode);
		e->num--;
		printf("\n成功删除该标签\"%s\"", s);
		return SUCCESS; 		
	}
	else
	{
		tagnode = e->taghead;
		e->taghead = tagnode->next;
		e->num--;
		printf("\n成功删除该标签\"%s\"", s);
		free(tagnode);
		return SUCCESS;		
	}

}

/**
 *  @name        : Status FindTag(FOF *e,char *s)
 *  @description : 查找/匹配标签
 *  @param       : FOF *e 文件节点
 				   char *s 标签内容 
 *  @return      : 查找成功返回SUCCESS，否则返回ERROR
 *  @Author		 :陈澎炜 
 */
Status FindTag(FOF *e, char *s)
{
	Tag *tagp;
	if(e->taghead == NULL)//判断原来是否有标签 
		return ERRORS;
	else
		tagp = e->taghead;
	if(strcmp(tagp->info, s) != 0)//判断头结点是不是我们要找的标签 
	{
		while(tagp->next!=NULL && strcmp(tagp->next->info, s))//判断下一个标签节点是否是该标签 
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
 *  @description : 打印标签
 *  @param       : FOF e 文件节点
 *  @return      : void
 *  @Author		 :陈澎炜 
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
 *  @description : 显示指定的文件或文件夹标签
 *  @param       :  CurFloder *read 当前文件信息结构体 
 					char *name 文件名或文件夹名 
 *  @return      : None
 *  @Author		 :陈澎炜 
 */
void PrintAppointTag(CurFloder *read, char *name)
{	
	FOF *fofnode; 
	int judge = 0;//判断是否找到该文件 
	
    fofnode = read->F;

	while(fofnode != NULL)//输出当前文件的标签信息 
	{
		if(strcmp(name, fofnode->name) == 0)//判断是否该文件或是文件夹 
		{
			printf("\n文件<%s>的标签为：",name);
			PrintTag(*fofnode);
			judge = 1;		
			break;
		} 
		fofnode = fofnode->next;
	}
	if(judge == 0)
	{
		printf("\n<%s>该文件不存在", name);
	} 
	
}

/**
 *  @name        : void AddAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : 为指定的文件或文件夹加标签
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *name 文件名或文件夹名 
 				   char *tag  标签内容 
 *  @return      : None
 *  @Author		 :陈澎炜 
 */
void AddAppointTag(CurFloder *read, char *name, char *tag)
{ 
	FOF *fofnode;
	char copy[400];
	fofnode = read->F;
	
	while(fofnode != NULL)//判断当前文件的标签信息 
	{
		if(strcmp(name, fofnode->name) == 0)//判断是否该文件或是文件夹 
		{
			if(FindTag(fofnode,tag)==SUCCESS)
			{
				printf("\n标签已存在！");
				return ;
			}
			else
			{
				AddTag(fofnode, tag);//添加标签	
				printf("\n标签添加成功！");
				break;
			} 
			
		} 
		fofnode = fofnode->next;
	}
	if(fofnode == NULL)
	{
		printf("\n输入的文件不存在！");
		return; 
	 } 
	strcpy(copy, currentpath);
	strcat(copy, "\\");
	strcat(copy, name);
	InputLog("添加标签的文件/文件夹的路径：", copy,"添加的标签名：",tag);
	Input_Save(read, currentpath);	//保存更改 
}


/**
 *  @name        : void DeleteAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : 为删除指定的文件或文件夹标签
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *name 文件名或文件夹名 
 				   char *tag  标签内容 
 *  @return      : None
 *  @Author		 :陈澎炜 
 */
void DeleteAppointTag(CurFloder *read, char *name, char *tag)
{
	FOF *fofnode; 
	char copy[400];
	fofnode = read->F;
	
	while(fofnode != NULL)//输出当前文件的标签信息 
	{
		if(strcmp(name, fofnode->name) == 0)//判断是否该文件或是文件夹 
		{
			if(DeleteTag(fofnode, tag)==SUCCESS)
				break;
			else
			{
				printf("\n标签不存在！");
				return;
			}
		} 
		fofnode = fofnode->next;
	}
	if(fofnode == NULL)
	{
		printf("\n输入的文件不存在！");
		return; 
	} 
	strcpy(copy, currentpath);
	strcat(copy, "\\");
	strcat(copy, name);
	InputLog("删除标签的文件/文件夹的路径：", copy,"删除的标签名：",tag);
	Input_Save(read, currentpath);	//保存更改 
}

/**
 *  @name        : void PrintCurFloderTag(CurFloder *read, char *tag)
 *  @description : 输出匹配tag的笔记文件名
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *tag  标签内容 
 *  @return      : None
 *  @Author		 :陈澎炜 
 */
void PrintCurFloderTag(CurFloder *current, char *tag)//输出匹配tag的笔记文件名
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
			if(Checkstr(ptag->info,tag)==SUCCESS)//如果存在
			{
				flag = 1;
				if(fofnode->flag == 1) 
					printf("\n  笔记文件名：%s",fofnode->name);//输出文件名
				else
					printf("\n笔记文件夹名：%s",fofnode->name);//输出文件名
				break;
			}
			ptag = ptag->next;
		}
		fofnode = fofnode->next;
	}
	if(!flag)
		printf("\n文件不存在！");
}
