
#ifndef _LINWENCHEN_
#define _LINWENCHEN_

#include "NoteManagementSystem.h"
/**
 *  @name        : All_User InitSystem(void)
 *  @description : �����û��ļ��������û�����
 *  @param       : void
 *  @return      : All_User(����ͷָ��)
 */
All_User InitSystem(void);
/**
 *  @name        : void MenuAdmin(All_User *L)
 *  @description : ��½���棬�����û���½����
 *  @param       : All_User *L ָ���û�����ͷ�ڵ�ָ���ָ��
 *  @return      : void
 */
 void MenuAdmin(All_User *L);
 /**
 *  @name        :  void UserLogin(All_User *L)
 *  @description : ��½��ע������������û���Ϣ���ò����빤����
 *  @param       : All_User *L ָ���û�����ͷ�ڵ�ָ���ָ��
 *  @return      : void
 */
 void UserLogin(All_User *L);
 /**
 *  @name        : void SetPassword(char *password)
 *  @description : �����û����룬���û����������ŵ�����password������
 *  @param       : char *password ����û�������ַ�����
 *  @return      : void
 */
 void SetPassword(char *password);
 /**
 *  @name        : void SetRoot(char *root,All_User L)
 *  @description : �����û��Ĺ���·��,���û�����Ĺ��������ַ������root������
 *  @param       : char *root(����û����������ֵ��ַ�����) All_User L(�û�����ͷ�ڵ�ָ��)
 *  @return      : void
 */
 void SetRoot(char *root,All_User L);
 /**
 *  @name        :  void SaveUser(All_User L)
 *  @description : ���û�������Ϣ���浽�û���Ϣ�Ķ������ļ���
 *  @param       : All_User L �û�����ͷ�ڵ�ָ��
 *  @return      : void
 */
 void SaveUser(All_User L);
 /**
 *  @name        : void AddUser(All_User *user,User e)
 *  @description : �����û�������
 *  @param       : All_User *user(ָ���û�����ͷ�ڵ�ָ���ָ��) User e(���û����)
 *  @return      : 
 */
void AddUser(All_User *user,User e);
  /**
 *  @name        : void MakeFOF(CurFloder *current, char *s)
 *  @description : �����ļ����ļ���
 *  @param       : CurFloder *current(��ǰ·���µ��ļ�����ͷָ��) char *s(��ǰ·�������·��)
 *  @return      : void
 */
 void MakeFOF(CurFloder *current, char *s);
  /**
 *  @name        : void DeleteFOF(CurFloder *current, char *s)
 *  @description : ɾ���ļ����ļ���
 *  @param       : CurFloder *current(��ǰ·���µ��ļ�����ͷָ��) char *s(��ǰ·�������·��)
 *  @return      : void
 */
 void DeleteFOF(CurFloder *current, char *s);
  /**
 *  @name        :  Status AddFOFNode(CurFloder *current, FOF e)
 *  @description : �����µ��ļ����ļ��н�㵽��ǰ�ļ�����
 *  @param       : CurFloder *current(��ǰ·���µ��ļ�����ͷָ��) FOF e(���ӵ��ļ����)
 *  @return      : Status
 */
 Status AddFOFNode(CurFloder *current, FOF e);
 /**
 *  @name        :  Status AddFOFNode(CurFloder *current, FOF e)
 *  @description : �ӵ�ǰ�ļ�����ɾ���µ��ļ����ļ��н��
 *  @param       : CurFloder *current(��ǰ·���µ��ļ�����ͷָ��) FOF e(ɾ�����ļ����)
 *  @return      : Status
 */
 Status DeteleFOFNode(CurFloder *current, char *name);
   /**
 *  @name        :  void LsGrep(char *path, char *Find)
 *  @description : ���ҵ�ǰ·���µ����е��ļ����ļ��У������������Ϣ���ļ����ļ������Լ�����·��
 *  @param       : path ����·�� Find ������Ϣ�ַ���
 *  @return      : void
 */
 void LsGrep(char *path, char *Find);
   /**
 *  @name        : void PrintGrep(FOF *current, char *path, char *Find)
 *  @description : ��ӡ��������Ϣ���ļ����ļ������Լ�����·��
 *  @param       : FOF *current(�ļ����ָ��) char *path(����·��) char *Find(������Ϣ)
 *  @return      : void
 */
 void PrintGrep(FOF *current, char *path, char *Find);
   /**
 *  @name        : int Checkstr(const char *s,const char *t)
 *  @description : //�ַ���ģ��ƥ��,ƥ��ɹ����ط�0ֵ��ʧ�ܷ���0
 *  @param       : const char *s(�ַ���1) const char *t(�ַ���2)
 *  @return      : int
 */
 int Checkstr(const char *s,const char *t);
   /**
 *  @name        : int CheckRoot(char *buf,int len)
 *  @description : ��鴫���·�������Ƿ���ȷ����ȷ����1,���󷵻�0
 *  @param       : char *buf(·���ַ���) int len(�ַ�������)
 *  @return      : 
 */
 int CheckRoot(char *buf,int len);
    /**
 *  @name        : void toxy(int x, int y)
 *  @description : �ƶ���Ļ��굽����(x,y)
 *  @param       : (x,y)����
 *  @return      : void
 */
 void toxy(int x, int y);
    /**
 *  @name        :  void color(short x)
 *  @description : ���ĵ�ǰ��ʾ��ɫ
 *  @param       : x(��Χ1~15)
 *  @return      : void
 */
 void color(short x);
    /**
 *  @name        : void HideCursor()
 *  @description : ���ع��
 *  @param       : void
 *  @return      : void
 */
void HideCursor();

#endif
