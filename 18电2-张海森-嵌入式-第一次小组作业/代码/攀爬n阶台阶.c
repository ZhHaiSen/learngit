#include <stdio.h>
int main()
{
	int stairs(int n);
	char c;
	int stair;
	printf("按x退出程序，按任意键开始运行\n");
	printf("上%d阶台阶有%d种方式\n", 10,stairs(10));
	for (; c = getchar() != 'x';)
	{
		printf("你想上几阶台阶:");
		scanf_s("%d", &stair);
		printf("上%d阶台阶有%d种方法\n", stair, stairs(stair));
	}
	return 0;
}
int stairs(int n)
{
	if (n == 1)
		n = 1;
	else if (n == 2)
		n = 2;
	else
		n = stairs(n - 2) + stairs(n - 1);
	return n;
}