#ifndef _CHENYU_
#define _CHENYU_

/**
 *  @name        : Status CdReturn(CurFloder *head)
 *  @description : 返回上一级 
 *  @param       : CurFloder *head  
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *  @return      : 
 */	
 Status CdReturn(CurFloder *head);
 
  /**
 *  @name        :  Status CdSwitch(CurFloder *head, char *targetpath)
 *  @description :  跳转到目标路径 
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *                 char *targetpath    目录的路径 
 *  @return      : 
 */	
Status CdSwitch(CurFloder *head, char *targetpath);

 /**
 *  @name        : void SearchTag(const char *tagname, const char *searchpath)
 *  @description : 根据标签名字查找所有该用户的符合标签的文件 （可模糊查找） 
 *  @param       : const char *tagname  标签名 
 *                 const char *searchpath  查找的路径 
 *  @return      : 
 */	
void SearchTag(const char *tagname, const char *searchpath, int *sum);

 /**
 *  @name        : void FileSort(char *filename, CurFloder *head)
 *  @description : 对目标文件夹进行排序 
 *  @param       : char *filename  目标文件夹的名字，当名字为空，即对当前文件夹进行排序 
 *                 CurFloder *head 保存当前文件信息的结构体
 *  @return      : 
 */	
void FileSort(char *filename, CurFloder *head);

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : 对目标文件链表进行  插入排序  与 FileSort 函数连用 
 *  @param       : CurFloder *head 保存目标文件夹文件信息的结构体
 *  @return      : 
 */	
void LinkSort(CurFloder *head);

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : 重命名文件 
 *  @param       : CurFloder *head 保存目标文件夹文件信息的结构体
 *  @return      : 
 */	
void MVRename(CurFloder *head, char *oldname, char *newname);

/**
 *  @name         void setColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
 *	@description        改变字的颜色 
 *	@param		   ForeColor前景颜色  BackGroundColor 背景颜色 
 *	@return		none
 *  @notice  none
 */
void setColor(unsigned short ForeColor,unsigned short BackGroundColor);

 /**
 *  @name        :  void PrintWorkFloder()
 *  @description : 树状打印所有文件夹以及笔记文件
 *  @param       : 
 *  @return      : 
 */	
void PrintTree(const char *prinpath, int choice, const char *form);

 
#endif
