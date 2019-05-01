/***************************************************************************************
 *	File Name				:	pengweitag.h		
 *	CopyRight				:
 *	ModuleName				:	
 *
 *	CPU						:
 *	RTOS					:
 *
 *	Create Data				:	
 *	Author/Corportation		:	
 *
 *	Abstract Description	:	this will be used for 
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/
#ifndef __PENGWEITAG_H
#define __PENGWEITAG_H

/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "NoteManagementSystem.h"

/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/


/**************************************************************
*	Macro Define Section
**************************************************************/


/**************************************************************
*	Struct Define Section
**************************************************************/

/**************************************************************
*	Prototype Declare Section
**************************************************************/

//标签链表
/**
 *  @name        : Status AddTag(FOF *e, char *s)
 *  @description : 添加标签 
 *  @param       : FOF *e 文件节点
 				   char *s 标签内容 
 *  @return      : Status 
 */	
Status AddTag(FOF *e, char *s);

/**
 *  @name        : Status DeleteTag(FOF *e, char *s)
 *  @description : 删除标签
 *  @param       : FOF e 文件节点
 				   char *s 标签内容
 *  @return      : 删除成功返回SUCCESS，否则返回ERROR
 */	
Status DeleteTag(FOF *e, char *s);

/**
 *  @name        : Status FindTag(FOF *e,char *s)
 *  @description : 查找/匹配标签
 *  @param       : FOF *e 文件节点
 				   char *s 标签内容 
 *  @return      : 查找成功返回SUCCESS，否则返回ERROR
 */
Status FindTag(FOF *e, char *s);

/**
 *  @name        : void PrintTag(FOF e)
 *  @description : 打印标签
 *  @param       : FOF e 文件节点
 *  @return      : void
 */
void PrintTag(FOF e);

//显示标签
/**
 *  @name        : void PrintAppointTag(CurFloder *read, char *name)
 *  @description : 显示指定的文件或文件夹标签
 *  @param       :  CurFloder *read 当前文件信息结构体 
 					char *name 文件名或文件夹名 
 *  @return      : None
 */
void PrintAppointTag(CurFloder *read, char *name);

/**
 *  @name        : void AddAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : 为指定的文件或文件夹加标签
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *name 文件名或文件夹名 
 				   char *tag  标签内容 
 *  @return      : None
 */
void AddAppointTag(CurFloder *read, char *name, char *tag);

/**
 *  @name        : void DeleteAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : 为删除指定的文件或文件夹标签
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *name 文件名或文件夹名 
 				   char *tag  标签内容 
 *  @return      : None
 */
void DeleteAppointTag(CurFloder *read, char *name, char *tag);

/**
 *  @name        : void PrintCurFloderTag(CurFloder *read, char *tag)
 *  @description : 输出匹配tag的笔记文件名
 *  @param       : CurFloder *read  当前文件信息结构体  
 				   char *tag  标签内容 
 *  @return      : None
 */
void PrintCurFloderTag(CurFloder *current, char *tag);


/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/

#endif
