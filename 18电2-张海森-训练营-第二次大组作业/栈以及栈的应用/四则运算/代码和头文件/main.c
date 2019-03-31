#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

LinkStack *S;   //包含栈信息的节点
ElemType StackTop, *e = &StackTop;   //栈顶元素
ElemType topdata, *Tdata = &topdata;   //得到栈顶元素并让栈顶元素出栈
char current = 0, expression[100];   //current用于输入当前字符，expression用于暂存当前字符串，c用于退出程序,d用于消除回车
int i, j;   //i用于将字符串存入暂存数组中,j用于中缀表达式转后缀表达式
float first, second, sum = 0;   //first用于存放栈顶第一个数字，second用于存放栈顶第二个数字，sum用于存放运算结果

int main()
{
	void middle_toward_behind(char *x);
	float behind_toward_sum(char *x);
	S = (LinkStack *)malloc(sizeof(LinkStack));   //为包含栈信息的节点分配内存
	char c;   //输入菜单选项
	printf("\t\t\t按回车继续计算，按x退出程序\n");
	while (1)   
	{
		printf("请输入计算表达式并按回车:");
		for (i=0; current != '\n';i++)   //循环读入字符串
		{
			scanf_s("%c", &current);
			expression[i] = current;
		}
		current = 0;   //重新赋值，再次进入循环
		middle_toward_behind(expression[100]);   //后缀变中缀
		sum = behind_toward_sum(expression[100]);   //中缀求结果
		for (j = 0; expression[j] != '\0'; j++)   //输出后缀表达式
			printf("%c", expression[j]);
		printf("=%f", sum);   //输出结果
		printf("\n");
		c = getchar();   //输入决定走向
		if (c == 'x') break;
	}
	return 0;
}

void middle_toward_behind(char *x)   //中缀变后缀
{
	initLStack(S);   //新建空栈
	for (i = 0, j = 0; expression[i] != '\n'; i++)   //读入每一个字符
	{
		if (expression[i] >= 48 && expression[i] <= 57)   //数字
		{
			expression[j] = expression[i];   //直接输出
			j++;
		}
		if (expression[i] == 40)  //（
		{
			pushLStack(S, expression[i]);   //入栈
		}
		if (expression[i] == 43 || expression[i] == 45 || expression[i] == 42 || expression[i] == 47)   //+  -  *  /
		{
			if (S->count > 0)   //非空栈
			{
				if (expression[i] == 43 || expression[i] == 45)   //+  -
				{
					getTopLStack(S, e);
					if (*e == 40)   //(
						pushLStack(S, expression[i]);   //压栈
					if (*e == 43 || *e == 45 || *e == 42 || *e == 47)   //+  -  *  /
					{
						for (; *e != 40 && S->count > 0;)   //比该运算符优先级大的或相等的都出栈
						{
							popLStack(S, Tdata);
							expression[j] = *Tdata;
							j++;
							if (S->count > 0)
							{
								getTopLStack(S, e);
							}
						}
						pushLStack(S, expression[i]);   //该运算符压栈
					}
				}
				if (expression[i] == 42 || expression[i] == 47)   //*  /
				{
					getTopLStack(S, e);
					if (*e == 40 || *e == 43 || *e == 45)   //(  +  -
						pushLStack(S, expression[i]);   //压栈
					if (*e == 42 || *e == 47)   //*  /
					{
						for (; *e == 40 || *e == 43 || *e == 45 || S->count == 0;)   //比该运算符优先级大的或者相等的出栈
						{
							popLStack(S, Tdata);
							expression[j] = *Tdata;
							j++;
							getTopLStack(S, e);
						}
						pushLStack(S, expression[i]);   //该运算符入栈
					}
				}
			}
			if (S->count == 0)   //空栈
				pushLStack(S, expression[i]);   //直接压栈
		}
		if (expression[i] == 41)   //）
		{
			getTopLStack(S, e);
			while (*e != 40)   //直到遇到左括号，否则出栈
			{
				popLStack(S, Tdata);
				expression[j] = *Tdata;
				j++;
				getTopLStack(S, e);
			}
			popLStack(S, Tdata);
		}
	}
	if (S->count > 0)   //还有运算符
	{
		for (; S->count != 0;)   //全部出栈
		{
			popLStack(S, Tdata);
			expression[j] = *Tdata;
			j++;
		}
	}
	expression[j] = '\0';   //设置标志位
	destroyLStack(S);    //销毁栈
}

float behind_toward_sum(char *x)   //后缀求结果
{
	initLStack(S);   //初始化栈
	for (j = 0; expression[j] != '\0'; j++)   //从左到右扫描
	{
		if (expression[j] >= 48 && expression[j] <= 57)   //数值
			pushLStack(S, expression[j] - 48);   //已数值的数字形式压栈
		if (expression[j] == 43)   //+
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = first + second;   //栈顶的两个元素相加为一个数
			pushLStack(S, sum);   //该数压栈
		}
		if (expression[j] == 45)   //-
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = second - first;   //栈顶第二个元素减第一个元素为一个数
			pushLStack(S, sum);   //该数压栈
		}
		if (expression[j] == 42)   //*
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = first * second;   //栈顶两个元素相乘为一个数
			pushLStack(S, sum);   //该数压栈
		}
		if (expression[j] == 47)   //    /
		{
			popLStack(S, Tdata);
			first = *Tdata;
			popLStack(S, Tdata);
			second = *Tdata;
			sum = second / first;//栈顶第二个数除以第一个数为一个数
			pushLStack(S, sum);   //该数压栈
		}
	}
	popLStack(S, Tdata);   //最终结果出栈
	sum = *Tdata;   //sum=最终结果
	destroyLStack(S);   //销毁栈
	return sum;
}