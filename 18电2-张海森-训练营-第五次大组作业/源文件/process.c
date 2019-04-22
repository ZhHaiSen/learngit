#include <stdio.h>
#include "BinaryTree.h"

extern BiTree *root;
extern char *definition;
extern int i;

void menu()
{
	printf("\t\t ______________________________ \n");
	printf("\t\t|                              |\n");
	printf("\t\t|     a.����ն�����           |\n");
	printf("\t\t|     b.���ٶ�����             |\n");
	printf("\t\t|     c.���ַ������������     |\n");
	printf("\t\t|     d.�����������ӡ         |\n");
	printf("\t\t|     e.�����������ӡ         |\n");
	printf("\t\t|     f.�����������ӡ         |\n");
	printf("\t\t|     x.�˳���������           |\n");
	printf("\t\t|______________________________|\n");
}

void input()
{
	int LOOP = 0;
	char c='a', d;
	while (c != 'x')
	{
		menu();
		printf("\n\t\t���ѡ��:");
		c = getchar();
		while ((d = getchar()) != '\n')
			;
		switch (c)
		{
		case 'A':
		case 'a':
			if (LOOP == 1)
				printf("\t\t�Ѿ�������ն�����\n");
			if (LOOP == 0)
			{
				InitBiTree(root);
				LOOP = 1;
			}
			break;
		case 'B':
		case 'b':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
			if (LOOP == 1)
			{
				DestroyBiTree(root);
				LOOP = 0;
			}
			break;
		case 'C':
		case 'c':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
			if (LOOP == 1)
			{
				printf("\t\t������һ���ַ���(�ɰ����ո�):");
				CreateBiTree(root, definition);
				char d = getchar();
			}
			break;
		case 'D':
		case 'd':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
			if (LOOP == 1)
			{
				PreOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'E':
		case 'e':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
			if (LOOP == 1)
			{
				InOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'F':
		case 'f':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
			if (LOOP == 1)
			{
				PostOrderTraverse(*root, print);
				printf("\n");
			}
			break;
		case 'G':
		case 'g':
			if (LOOP == 0)
				printf("\t\t�����ڶ�����\n");
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
			printf("\t\t��������ȷ��ѡ��!\n");
		}
	}
}
