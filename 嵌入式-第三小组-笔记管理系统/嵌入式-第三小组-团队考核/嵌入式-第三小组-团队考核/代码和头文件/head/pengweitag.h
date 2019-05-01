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

//��ǩ����
/**
 *  @name        : Status AddTag(FOF *e, char *s)
 *  @description : ��ӱ�ǩ 
 *  @param       : FOF *e �ļ��ڵ�
 				   char *s ��ǩ���� 
 *  @return      : Status 
 */	
Status AddTag(FOF *e, char *s);

/**
 *  @name        : Status DeleteTag(FOF *e, char *s)
 *  @description : ɾ����ǩ
 *  @param       : FOF e �ļ��ڵ�
 				   char *s ��ǩ����
 *  @return      : ɾ���ɹ�����SUCCESS�����򷵻�ERROR
 */	
Status DeleteTag(FOF *e, char *s);

/**
 *  @name        : Status FindTag(FOF *e,char *s)
 *  @description : ����/ƥ���ǩ
 *  @param       : FOF *e �ļ��ڵ�
 				   char *s ��ǩ���� 
 *  @return      : ���ҳɹ�����SUCCESS�����򷵻�ERROR
 */
Status FindTag(FOF *e, char *s);

/**
 *  @name        : void PrintTag(FOF e)
 *  @description : ��ӡ��ǩ
 *  @param       : FOF e �ļ��ڵ�
 *  @return      : void
 */
void PrintTag(FOF e);

//��ʾ��ǩ
/**
 *  @name        : void PrintAppointTag(CurFloder *read, char *name)
 *  @description : ��ʾָ�����ļ����ļ��б�ǩ
 *  @param       :  CurFloder *read ��ǰ�ļ���Ϣ�ṹ�� 
 					char *name �ļ������ļ����� 
 *  @return      : None
 */
void PrintAppointTag(CurFloder *read, char *name);

/**
 *  @name        : void AddAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : Ϊָ�����ļ����ļ��мӱ�ǩ
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *name �ļ������ļ����� 
 				   char *tag  ��ǩ���� 
 *  @return      : None
 */
void AddAppointTag(CurFloder *read, char *name, char *tag);

/**
 *  @name        : void DeleteAppointTag(CurFloder *read, char *name, char *tag)
 *  @description : Ϊɾ��ָ�����ļ����ļ��б�ǩ
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *name �ļ������ļ����� 
 				   char *tag  ��ǩ���� 
 *  @return      : None
 */
void DeleteAppointTag(CurFloder *read, char *name, char *tag);

/**
 *  @name        : void PrintCurFloderTag(CurFloder *read, char *tag)
 *  @description : ���ƥ��tag�ıʼ��ļ���
 *  @param       : CurFloder *read  ��ǰ�ļ���Ϣ�ṹ��  
 				   char *tag  ��ǩ���� 
 *  @return      : None
 */
void PrintCurFloderTag(CurFloder *current, char *tag);


/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/

#endif
