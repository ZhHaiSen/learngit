#include <stdio.h>
#include <time.h>

/*��ȡ��ǰ���ꡢ�¡��ա�ʱ���֡���ı���*/
int YEAR;
int MON;
int DAY;
int HOUR;
int MIN;
int SEC;

/*����ӭ��ʱ���ӡ���˵�ѡ�����һ���ӡ��������*/
void message()
{
	void Welcome();
	void time_print();
	void menu();
	Welcome();
	time_print();
	menu();
}

/*��ӭ����*/
void Welcome()
{
	printf("\n\t\t��ӭ����ͼ�����ϵͳ!(�����Ҫ���밴x�˳�)\n");
}

/*������˵�ѡ��*/
void menu()
{
	printf("\t\t _________________ __________________ __________________ \n");
	printf("\t\t|                 |                  |                  |\n");
	printf("\t\t|   1.�ɱ����    |    2.������    |    3.�鼮��Ϣ    |\n");
	printf("\t\t|_________________|__________________|__________________|\n");
	printf("\t\t|                 |                  |                  |\n");
	printf("\t\t|     4.����      |      5.�黹      |    6.ԤԼ����    |\n");
	printf("\t\t|_________________|__________________|__________________|\n");
	printf("                                                             \n");
}

/*������ʾ*/
void remind()
{
	printf("\t\t����������Ҫ���еĲ���ǰ������:");
}

/*�Ƿ����뾯��*/
void warn()
{
	printf("\t\t��⵽�Ƿ�����!\n");
}

/*������ʱ����ʾ*/
void time_print()
{
	void systemtime();
	systemtime();   //��ȡϵͳ��ǰʱ��
	if(HOUR<10&&MIN<10&&SEC<10)   //ʼ����XX:XX:XX����ʽ��ʾʱ:��:��
		printf("\t\t                         0%d:0%d:0%d\n", HOUR, MIN, SEC);
	if (HOUR >= 10 && MIN < 10 && SEC < 10)
		printf("\t\t                         %d:0%d:0%d\n", HOUR, MIN, SEC);
	if (HOUR < 10 && MIN >= 10 && SEC < 10)
		printf("\t\t                         0%d:%d:0%d\n", HOUR, MIN, SEC);
	if (HOUR < 10 && MIN < 10 && SEC >= 10)
		printf("\t\t                         0%d:0%d:%d\n", HOUR, MIN, SEC);
	if (HOUR >= 10 && MIN >= 10 && SEC < 10)
		printf("\t\t                         %d:%d:0%d\n", HOUR, MIN, SEC);
	if (HOUR < 10 && MIN >= 10 && SEC >= 10)
		printf("\t\t                         0%d:%d:%d\n", HOUR, MIN, SEC);
	if (HOUR >= 10 && MIN < 10 && SEC >= 10)
		printf("\t\t                         %d:0%d:%d\n", HOUR, MIN, SEC);
	if (HOUR >= 10 && MIN >= 10 && SEC >= 10)
		printf("\t\t                         %d:%d:%d\n", HOUR, MIN, SEC);
}

/*��ȡϵͳ��ǰʱ��*/
void systemtime()
{
	time_t systemtime;   //��ǰʱ�����
	struct tm systemTime;   //��ǰʱ��ṹ��
	time(&systemtime);   //��ȡʱ��
	localtime_s(&systemTime, &systemtime);   //��ȡ����ʱ��
	YEAR = systemTime.tm_year + 1900;   //��ǰ�ꡢ�¡��ա�ʱ���֡���
	MON = systemTime.tm_mon + 1;
	DAY = systemTime.tm_mday;
	HOUR = systemTime.tm_hour;
	MIN = systemTime.tm_min;
	SEC=systemTime.tm_sec;
}

/*������ʾ�����鿴ĳ����ȫ���������ơ��鿴ĳ���ȫ����Ϣ*/
void bookinformation()
{
	printf("\t\t _________________ __________________ \n");
	printf("\t\t|                 |                  |\n");
	printf("\t\t|   1.��������    |    2.�鼮״̬    |\n");
	printf("\t\t|_________________|__________________|\n");
}
