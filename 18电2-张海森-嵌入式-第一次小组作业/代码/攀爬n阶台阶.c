#include <stdio.h>
int main()
{
	int stairs(int n);
	char c;
	int stair;
	printf("��x�˳����򣬰��������ʼ����\n");
	printf("��%d��̨����%d�ַ�ʽ\n", 10,stairs(10));
	for (; c = getchar() != 'x';)
	{
		printf("�����ϼ���̨��:");
		scanf_s("%d", &stair);
		printf("��%d��̨����%d�ַ���\n", stair, stairs(stair));
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