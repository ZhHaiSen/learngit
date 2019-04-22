#include <stdio.h>
#include "BinaryTree.h"

extern BiTree *root;
extern char *definition;
extern int i;

void menu()
{
	printf("\t\t ______________________________ \n");
	printf("\t\t|                              |\n");
	printf("\t\t|     a.构造空二叉树           |\n");
	printf("\t\t|     b.销毁二叉树             |\n");
	printf("\t\t|     c.按字符串构造二叉树     |\n");
	printf("\t\t|     d.先序遍历并打印         |\n");
	printf("\t\t|     e.中序遍历并打印         |\n");
	printf("\t\t|     f.后序遍历并打印         |\n");
	printf("\t\t|     x.退出程序运行           |\n");
	printf("\t\t|______________________________|\n");
}

void input()
{
	int LOOP = 0;
	char c='a', d;
	while (c != 'x')
	{
		menu();
		printf("\n\t\t你的选择:");
		c = getchar();
		while ((d = getchar()) != '\n')
			;
		switch (c)
		{
		case 'A':
		case 'a':
			if (LOOP == 1)
				printf("\t\t已经构造过空二叉树\n");
			if (LOOP == 0)
			{
				InitBiTree(root);
				LOOP = 1;
			}
			break;
		case 'B':
		case 'b':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				DestroyBiTree(root);
				LOOP = 0;
			}
			break;
		case 'C':
		case 'c':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				printf("\t\t请输入一个字符串(可包含空格):");
				CreateBiTree(root, definition);
				char d = getchar();
			}
			break;
		case 'D':
		case 'd':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				PreOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'E':
		case 'e':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				InOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'F':
		case 'f':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				PostOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'G':
		case 'g':
			if (LOOP == 0)
				printf("\t\t不存在二叉树\n");
			if (LOOP == 1)
			{
				LevelOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'X':
		case 'x':
			break;
		default:
			printf("\t\t请输入正确的选项!\n");
		}
	}
}
