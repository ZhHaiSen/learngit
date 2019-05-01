#ifndef _MOVEFOF_H_
#define _MOVEFOF_H_

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : 实现将一个笔记文件移动到一个笔记文件夹中 
 *  @param       : char x[]-移动的笔记文件名，可为绝对路径或者相对路径    char y[]-移向的笔记文件夹名，可为绝对路径或者相对路径 
 *  @return      : SUCCESS 表示移动成功      ERROR 表示移动失败 
 */
Status movefile(char x[],char y[]); 

/**
 *  @name        :  Status movefolder(char x[],char y[])
 *  @description : 实现将一个笔记文件移动到一个笔记文件夹中 
 *  @param       : char x[]-移动的笔记文件名，可为绝对路径或者相对路径    char y[]-移向的笔记文件夹名，可为绝对路径或者相对路径 
 *  @return      : SUCCESS 表示移动成功      ERROR 表示移动失败 
 */
Status movefolder(char x[],char y[]);

/**
 *  @name        :  void print_help()
 *  @description : 打印帮助菜单 
 *  @param       : 无 
 *  @return      : 无 
 */
void print_help();

#endif
