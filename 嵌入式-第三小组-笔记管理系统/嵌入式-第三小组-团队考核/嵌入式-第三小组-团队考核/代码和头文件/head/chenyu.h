#ifndef _CHENYU_
#define _CHENYU_

/**
 *  @name        : Status CdReturn(CurFloder *head)
 *  @description : ������һ�� 
 *  @param       : CurFloder *head  
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *  @return      : 
 */	
 Status CdReturn(CurFloder *head);
 
  /**
 *  @name        :  Status CdSwitch(CurFloder *head, char *targetpath)
 *  @description :  ��ת��Ŀ��·�� 
 *  @param       : CurFloder *read   
 *                  �����ļ���Ϣ�Ľṹ�壨Ҫ�ں���ǰ��malloc������ڴ�����ã�
 *                 char *targetpath    Ŀ¼��·�� 
 *  @return      : 
 */	
Status CdSwitch(CurFloder *head, char *targetpath);

 /**
 *  @name        : void SearchTag(const char *tagname, const char *searchpath)
 *  @description : ���ݱ�ǩ���ֲ������и��û��ķ��ϱ�ǩ���ļ� ����ģ�����ң� 
 *  @param       : const char *tagname  ��ǩ�� 
 *                 const char *searchpath  ���ҵ�·�� 
 *  @return      : 
 */	
void SearchTag(const char *tagname, const char *searchpath, int *sum);

 /**
 *  @name        : void FileSort(char *filename, CurFloder *head)
 *  @description : ��Ŀ���ļ��н������� 
 *  @param       : char *filename  Ŀ���ļ��е����֣�������Ϊ�գ����Ե�ǰ�ļ��н������� 
 *                 CurFloder *head ���浱ǰ�ļ���Ϣ�Ľṹ��
 *  @return      : 
 */	
void FileSort(char *filename, CurFloder *head);

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : ��Ŀ���ļ��������  ��������  �� FileSort �������� 
 *  @param       : CurFloder *head ����Ŀ���ļ����ļ���Ϣ�Ľṹ��
 *  @return      : 
 */	
void LinkSort(CurFloder *head);

 /**
 *  @name        : void LinkSort(CurFloder *head)
 *  @description : �������ļ� 
 *  @param       : CurFloder *head ����Ŀ���ļ����ļ���Ϣ�Ľṹ��
 *  @return      : 
 */	
void MVRename(CurFloder *head, char *oldname, char *newname);

/**
 *  @name         void setColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
 *	@description        �ı��ֵ���ɫ 
 *	@param		   ForeColorǰ����ɫ  BackGroundColor ������ɫ 
 *	@return		none
 *  @notice  none
 */
void setColor(unsigned short ForeColor,unsigned short BackGroundColor);

 /**
 *  @name        :  void PrintWorkFloder()
 *  @description : ��״��ӡ�����ļ����Լ��ʼ��ļ�
 *  @param       : 
 *  @return      : 
 */	
void PrintTree(const char *prinpath, int choice, const char *form);

 
#endif
