/***************************************************************************************
 *	File Name				:	NodeManagementSystem.h		
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


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef __CONTROL_H
#define __CONTROL_H


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

//�û�
typedef struct  USER
{
	char name[100];//�û�����
	char password[20];//����
	char root[400];//���û����ļ��еĵ�ַ
	struct USER *next;//��һ���û�
} User,*All_User;

//��ǩ
typedef struct TAG
{
	char info[100];//��ǩ
	struct TAG *next;//��һ�����
} Tag;

//�ļ����ļ�����Ϊ���
typedef struct File_Or_Floder
{
	int flag;//���� 1:.txt�ļ� 2:�ļ��� 
	char name[100];//�ļ����ļ�������
	int num;//��ǩ����
	Tag *taghead;//ָ���Ӧ�ļ����ļ��еı�ǩ����ͷָ��
	struct File_Or_Floder *next;//��һ���ļ����ļ���
} FOF;

//��ǰĿ¼
typedef struct CurFloder
{
	FOF *F;//���ݵ�ǰĿ¼����������
} CurFloder;


typedef enum Status
{
	ERRORS = 0,
	SUCCESS = 1
}Status;

/**
 *  @name        : Status RoteExistence(const char *s, int choice)
 *  @description : ������·�����Ƿ�����ļ��л�txt�ļ� ��Ҳ���������ж�·�������Ƿ���ȷ 
 *  @param       : const char *s ����ľ���·��    choice 0��ʾ�ж��ļ��д������   ��'0'��ʾtxt�ļ��������
 *  @return      : SUCCESS ��ʾ����      ERROR��ʾ������ 
 */
 Status RoteExistence(const char *s, int choice);
 
 /**
 *  @name        : void Input_Save(CurFloder *input)
 *  @description : ���ļ�����Ϣ¼��_save.txt �ļ� 
 *  @param       : CurFloder char *input   �����ļ���Ϣ����ĵĽṹ��
 *                 const char *filerote    Ҫ������Ŀ¼��·�������ü�_save.txt���������Զ�����_save.txt,ֻҪ��Ŀ¼��·���� 
 *  @return      : 
 */
void Input_Save(CurFloder *input, const char *filerote);

/**
 *  @name        : void Read_Save(CurFloder *read, const char *filerote)
 *  @description : ��_save.txt ��ȡ�ļ�����Ϣ
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *                 const char *filerote    Ŀ¼��·�������ü�_save.txt���������Զ�����_save.txt��
 *  @return      : 
 */	
 void Read_Save(CurFloder *read, const char *filerote);
 
  /**
 *  @name        : void DestroyFof(CurFloder *des)
 *  @description : �������� 
 *  @param       :  CurFloder *des   �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 */	
void DestroyFof(CurFloder *des);

/**
 *  @name        : vvoid SecondMain()
 *  @description : �൱�ڵڶ��������� 
 *  @param       : 
 */	
void SecondMain(User name);

 /**
 *  @name        :  void TnputLog(char *message1, char *firstmessage, char *message2, *char secondmessage)
 *  @description : ��¼���� 
 *  @param       : 
 *  @return      : 
 */	
void InputLog(char *message1, char *firstmessage, char *message2, char *secondmessage);

 /**
 *  @name        :  void PrinLog()
 *  @description : ������й��Ĳ��� 
 *  @param       : 
 *  @return      : 
 */	
void PrinLog();

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
