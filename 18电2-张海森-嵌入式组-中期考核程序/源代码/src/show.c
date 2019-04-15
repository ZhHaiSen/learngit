#include <stdio.h>
#include <time.h>

/*获取当前的年、月、日、时、分、秒的变量*/
int YEAR;
int MON;
int DAY;
int HOUR;
int MIN;
int SEC;

/*将欢迎、时间打印、菜单选项合在一起打印在主界面*/
void message()
{
	void Welcome();
	void time_print();
	void menu();
	Welcome();
	time_print();
	menu();
}

/*欢迎光临*/
void Welcome()
{
	printf("\n\t\t欢迎光临图书管理系统!(如果需要，请按x退出)\n");
}

/*主界面菜单选项*/
void menu()
{
	printf("\t\t _________________ __________________ __________________ \n");
	printf("\t\t|                 |                  |                  |\n");
	printf("\t\t|   1.采编入库    |    2.清除库存    |    3.书籍信息    |\n");
	printf("\t\t|_________________|__________________|__________________|\n");
	printf("\t\t|                 |                  |                  |\n");
	printf("\t\t|     4.借阅      |      5.归还      |    6.预约借书    |\n");
	printf("\t\t|_________________|__________________|__________________|\n");
	printf("                                                             \n");
}

/*输入提示*/
void remind()
{
	printf("\t\t请输入你想要进行的操作前的数字:");
}

/*非法输入警告*/
void warn()
{
	printf("\t\t检测到非法输入!\n");
}

/*主界面时间显示*/
void time_print()
{
	void systemtime();
	systemtime();   //获取系统当前时间
	if(HOUR<10&&MIN<10&&SEC<10)   //始终以XX:XX:XX的形式显示时:分:秒
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

/*获取系统当前时间*/
void systemtime()
{
	time_t systemtime;   //当前时间变量
	struct tm systemTime;   //当前时间结构体
	time(&systemtime);   //获取时间
	localtime_s(&systemTime, &systemtime);   //获取当地时间
	YEAR = systemTime.tm_year + 1900;   //当前年、月、日、时、分、秒
	MON = systemTime.tm_mon + 1;
	DAY = systemTime.tm_mday;
	HOUR = systemTime.tm_hour;
	MIN = systemTime.tm_min;
	SEC=systemTime.tm_sec;
}

/*操作提示——查看某著者全部著作名称、查看某书的全部信息*/
void bookinformation()
{
	printf("\t\t _________________ __________________ \n");
	printf("\t\t|                 |                  |\n");
	printf("\t\t|   1.所有著作    |    2.书籍状态    |\n");
	printf("\t\t|_________________|__________________|\n");
}
