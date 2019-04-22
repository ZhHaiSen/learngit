#include <stdio.h>
#include "BinaryTree.h"
#include ".archivetempLQueue.h"

BiTree *root;
LQueue *n;
char *queue;
char *definition;
int i;

int main()
{
	root = (BiTree *)malloc(sizeof(BiTree));
	n = (LQueue *)malloc(sizeof(LQueue));
	queue = (char *)malloc(sizeof(char));
	definition = (char *)malloc(sizeof(char));
	input();
	return 0;
}
