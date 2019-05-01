
#ifndef _LINWENCHEN_
#define _LINWENCHEN_

#include "NoteManagementSystem.h"
/**
 *  @name        : All_User InitSystem(void)
 *  @description : 读入用户文件，建立用户链表
 *  @param       : void
 *  @return      : All_User(链表头指针)
 */
All_User InitSystem(void);
/**
 *  @name        : void MenuAdmin(All_User *L)
 *  @description : 登陆界面，进行用户登陆操作
 *  @param       : All_User *L 指向用户链表头节点指针的指针
 *  @return      : void
 */
 void MenuAdmin(All_User *L);
 /**
 *  @name        :  void UserLogin(All_User *L)
 *  @description : 登陆或注册操作，进行用户信息设置并进入工作区
 *  @param       : All_User *L 指向用户链表头节点指针的指针
 *  @return      : void
 */
 void UserLogin(All_User *L);
 /**
 *  @name        : void SetPassword(char *password)
 *  @description : 设置用户密码，将用户输入的密码放到参数password并返回
 *  @param       : char *password 存放用户密码的字符数组
 *  @return      : void
 */
 void SetPassword(char *password);
 /**
 *  @name        : void SetRoot(char *root,All_User L)
 *  @description : 设置用户的工作路径,将用户输入的工作区名字放入参数root并返回
 *  @param       : char *root(存放用户工作区名字的字符数组) All_User L(用户链表头节点指针)
 *  @return      : void
 */
 void SetRoot(char *root,All_User L);
 /**
 *  @name        :  void SaveUser(All_User L)
 *  @description : 将用户链表信息保存到用户信息的二进制文件中
 *  @param       : All_User L 用户链表头节点指针
 *  @return      : void
 */
 void SaveUser(All_User L);
 /**
 *  @name        : void AddUser(All_User *user,User e)
 *  @description : 新增用户链表结点
 *  @param       : All_User *user(指向用户链表头节点指针的指针) User e(新用户结点)
 *  @return      : 
 */
void AddUser(All_User *user,User e);
  /**
 *  @name        : void MakeFOF(CurFloder *current, char *s)
 *  @description : 创建文件或文件夹
 *  @param       : CurFloder *current(当前路径下的文件链表头指针) char *s(当前路径或相对路径)
 *  @return      : void
 */
 void MakeFOF(CurFloder *current, char *s);
  /**
 *  @name        : void DeleteFOF(CurFloder *current, char *s)
 *  @description : 删除文件或文件夹
 *  @param       : CurFloder *current(当前路径下的文件链表头指针) char *s(当前路径或相对路径)
 *  @return      : void
 */
 void DeleteFOF(CurFloder *current, char *s);
  /**
 *  @name        :  Status AddFOFNode(CurFloder *current, FOF e)
 *  @description : 增加新的文件或文件夹结点到当前文件链表
 *  @param       : CurFloder *current(当前路径下的文件链表头指针) FOF e(增加的文件结点)
 *  @return      : Status
 */
 Status AddFOFNode(CurFloder *current, FOF e);
 /**
 *  @name        :  Status AddFOFNode(CurFloder *current, FOF e)
 *  @description : 从当前文件链表删除新的文件或文件夹结点
 *  @param       : CurFloder *current(当前路径下的文件链表头指针) FOF e(删除的文件结点)
 *  @return      : Status
 */
 Status DeteleFOFNode(CurFloder *current, char *name);
   /**
 *  @name        :  void LsGrep(char *path, char *Find)
 *  @description : 查找当前路径下的所有的文件或文件夹，输出带搜索信息的文件或文件夹名以及绝对路径
 *  @param       : path 查找路径 Find 搜索信息字符串
 *  @return      : void
 */
 void LsGrep(char *path, char *Find);
   /**
 *  @name        : void PrintGrep(FOF *current, char *path, char *Find)
 *  @description : 打印带搜索信息的文件或文件夹名以及绝对路径
 *  @param       : FOF *current(文件结点指针) char *path(查找路径) char *Find(查找信息)
 *  @return      : void
 */
 void PrintGrep(FOF *current, char *path, char *Find);
   /**
 *  @name        : int Checkstr(const char *s,const char *t)
 *  @description : //字符串模糊匹配,匹配成功返回非0值，失败返回0
 *  @param       : const char *s(字符串1) const char *t(字符串2)
 *  @return      : int
 */
 int Checkstr(const char *s,const char *t);
   /**
 *  @name        : int CheckRoot(char *buf,int len)
 *  @description : 检查传入的路径命名是否正确，正确返回1,错误返回0
 *  @param       : char *buf(路径字符串) int len(字符串长度)
 *  @return      : 
 */
 int CheckRoot(char *buf,int len);
    /**
 *  @name        : void toxy(int x, int y)
 *  @description : 移动屏幕光标到坐标(x,y)
 *  @param       : (x,y)坐标
 *  @return      : void
 */
 void toxy(int x, int y);
    /**
 *  @name        :  void color(short x)
 *  @description : 更改当前显示颜色
 *  @param       : x(范围1~15)
 *  @return      : void
 */
 void color(short x);
    /**
 *  @name        : void HideCursor()
 *  @description : 隐藏光标
 *  @param       : void
 *  @return      : void
 */
void HideCursor();

#endif
