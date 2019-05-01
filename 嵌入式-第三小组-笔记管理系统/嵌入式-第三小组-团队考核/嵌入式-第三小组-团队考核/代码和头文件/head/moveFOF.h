#ifndef _MOVEFOF_H_
#define _MOVEFOF_H_

/**
 *  @name        : Status movefile(char x[], char y[])
 *  @description : ʵ�ֽ�һ���ʼ��ļ��ƶ���һ���ʼ��ļ����� 
 *  @param       : char x[]-�ƶ��ıʼ��ļ�������Ϊ����·���������·��    char y[]-����ıʼ��ļ���������Ϊ����·���������·�� 
 *  @return      : SUCCESS ��ʾ�ƶ��ɹ�      ERROR ��ʾ�ƶ�ʧ�� 
 */
Status movefile(char x[],char y[]); 

/**
 *  @name        :  Status movefolder(char x[],char y[])
 *  @description : ʵ�ֽ�һ���ʼ��ļ��ƶ���һ���ʼ��ļ����� 
 *  @param       : char x[]-�ƶ��ıʼ��ļ�������Ϊ����·���������·��    char y[]-����ıʼ��ļ���������Ϊ����·���������·�� 
 *  @return      : SUCCESS ��ʾ�ƶ��ɹ�      ERROR ��ʾ�ƶ�ʧ�� 
 */
Status movefolder(char x[],char y[]);

/**
 *  @name        :  void print_help()
 *  @description : ��ӡ�����˵� 
 *  @param       : �� 
 *  @return      : �� 
 */
void print_help();

#endif
