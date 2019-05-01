#ifndef _PRIN_H_
#define _PRIN_H_

 /**
 *  @name        :  void PrintCurrentFloder(CurFloder *head)
 *  @description :  ��ӡ��ǰĿ¼�����бʼǺ��ļ���
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *  @return      : 
 */	
void PrintCurrentFloder(CurFloder *head); 


 /**
 *  @name        :  void PrintPathFloder(char *filepath)
 *  @description :  ��ӡ·���µ����бʼǺ��ļ���
 *  @param       : 	char *filepath  Ŀ��·�� 
 *  @return      : 
 */	
void PrintPathFloder(char *filepath);


 /**
 *  @name        :  void RecursionPrin(char *prinpath, int *sum) �� 
 *  @description :  ��ӡ·���µ����бʼǺ��ļ���(��void PrintPathFloder(char *filepath)����)
 *  @param       : 	char *prinpath  Ŀ��·�� int *sum ���� 
 *  @return      : 
 */	
void RecursionPrin(char *prinpath, int *sum);
 
#endif
