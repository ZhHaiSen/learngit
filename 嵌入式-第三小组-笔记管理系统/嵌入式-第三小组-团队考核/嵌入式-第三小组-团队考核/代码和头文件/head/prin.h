#ifndef _PRIN_H_
#define _PRIN_H_

 /**
 *  @name        :  void PrintCurrentFloder(CurFloder *head)
 *  @description :  打印当前目录下所有笔记和文件夹
 *  @param       : CurFloder *read   
 *                  保存文件信息的结构体（要在函数前用malloc分配好内存才能用）
 *  @return      : 
 */	
void PrintCurrentFloder(CurFloder *head); 


 /**
 *  @name        :  void PrintPathFloder(char *filepath)
 *  @description :  打印路径下的所有笔记和文件夹
 *  @param       : 	char *filepath  目标路径 
 *  @return      : 
 */	
void PrintPathFloder(char *filepath);


 /**
 *  @name        :  void RecursionPrin(char *prinpath, int *sum) ； 
 *  @description :  打印路径下的所有笔记和文件夹(与void PrintPathFloder(char *filepath)连用)
 *  @param       : 	char *prinpath  目标路径 int *sum 总数 
 *  @return      : 
 */	
void RecursionPrin(char *prinpath, int *sum);
 
#endif
