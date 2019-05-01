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

//用户
typedef struct  USER
{
	char name[100];//用户名字
	char password[20];//密码
	char root[400];//该用户主文件夹的地址
	struct USER *next;//下一个用户
} User,*All_User;

//标签
typedef struct TAG
{
	char info[100];//标签
	struct TAG *next;//下一个结点
} Tag;

//文件或文件夹作为结点
typedef struct File_Or_Floder
{
	int flag;//类型 1:.txt文件 2:文件夹 
	char name[100];//文件或文件夹名字
	int num;//标签数量
	Tag *taghead;//指向对应文件或文件夹的标签链表头指针
	struct File_Or_Floder *next;//下一个文件或文件夹
} FOF;

//当前目录
typedef struct CurFloder
{
	FOF *F;//根据当前目录建立的链表
} CurFloder;


typedef enum Status
{
	ERRORS = 0,
	SUCCESS = 1
}Status;

/**
 *  @name        : Status RoteExistence(const char *s, int choice)
 *  @description : 检查这个路径下是否存在文件夹或txt文件 ，也可以用作判断路径输入是否正确 
 *  @param       : const char *s 输入的绝对路径    choice 0表示判断文件夹存在与否   非'0'表示txt文件存在与否
 *  @return      : SUCCESS 表示存在      ERROR表示不存在 
 */
 Status RoteExistence(const char *s, int choice);
 
 /**
 *  @name        : void Input_Save(CurFloder *input)
 *  @description : 将文件的信息录入_save.txt 文件 
 *  @param       : CurFloder char *input   保存文件信息链表的的结构体
 *                 const char *filerote    要操作的目录的路径（不用加_save.txt，函数会自动加上_save.txt,只要该目录的路径） 
 *  @return      : 
 */
void Input_Save(CurFloder *input, const char *filerote);

/**
 *  @name        : void Read_Save(CurFloder *read, const char *filerote)
 *  @description : 从_save.txt 读取文件的信息
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *                 const char *filerote    目录的路径（不用加_save.txt，函数会自动加上_save.txt）
 *  @return      : 
 */	
 void Read_Save(CurFloder *read, const char *filerote);
 
  /**
 *  @name        : void DestroyFof(CurFloder *des)
 *  @description : 销毁链表 
 *  @param       :  CurFloder *des   保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 */	
void DestroyFof(CurFloder *des);

/**
 *  @name        : vvoid SecondMain()
 *  @description : 相当于第二个主函数 
 *  @param       : 
 */	
void SecondMain(User name);

 /**
 *  @name        :  void TnputLog(char *message1, char *firstmessage, char *message2, *char secondmessage)
 *  @description : 记录操作 
 *  @param       : 
 *  @return      : 
 */	
void InputLog(char *message1, char *firstmessage, char *message2, char *secondmessage);

 /**
 *  @name        :  void PrinLog()
 *  @description : 输出进行过的操作 
 *  @param       : 
 *  @return      : 
 */	
void PrinLog();

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
