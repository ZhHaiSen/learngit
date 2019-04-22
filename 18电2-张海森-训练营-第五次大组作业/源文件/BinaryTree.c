#include <stdio.h>
#include "BinaryTree.h"
#include ".archivetempLQueue.h"

extern LQueue *n;
extern char *queue;

/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : ����ն�����T
 *  @param       : �����������T
 */
Status InitBiTree(BiTree *T)
{
	if (T == NULL)
	{
		printf("\t\t�ڴ治��\n");
		return ERROR;
	}
	*T = NULL;
	printf("\t\t��ʼ���ɹ�\n");
	return SUCCESS;
}


/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : �ݻٶ�����T
 *  @param       : �����������T
 */
Status DestroyBiTree(BiTree *T)
{
	if (*T != NULL)
	{
		DestroyBiTree((*T)->lchild);
		DestroyBiTree((*T)->rchild);
		free(*T);
	}
	printf("\t\t���ٳɹ�\n");
	return SUCCESS;
}

/**
 *  @name        : Status CreateBiTree(BiTree T, char* definition);
 *  @description : ���������T
 *  @param       : �����������T, ��������������ַ���definition
 */
Status CreateBiTree(BiTree *T, char* definition)
{
	definition = (char *)malloc(sizeof(char));
	(*definition) = getchar();
	if( *definition != '\n')
	{
		if (*definition == ' ')
			*T = NULL;
		else
		{
			*T = (BiTree)malloc(sizeof(BiTNode));
			if (*T == NULL)
			{
				printf("\t\t�ڴ治��\n");
				return ERROR;
			}
			(*T)->data = *definition;
			CreateBiTree(&((*T)->lchild), definition);
			CreateBiTree(&((*T)->rchild), definition);
		}
	}
	else
	{
		return SUCCESS;
	}
}

/**
 *  @name        : Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T)
	{
		if (visit(T->data))
			if (PreOrderTraverse(T->lchild, visit))
				if (PreOrderTraverse(T->rchild, visit))
					return SUCCESS;
		return ERROR;
	}
	else
		return SUCCESS;
}

/**
 *  @name        : Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T)
	{
		if (PreOrderTraverse(T->lchild, visit))
			if (visit(T->data))
				if (PreOrderTraverse(T->rchild, visit))
					return SUCCESS;
		return ERROR;
	}
	else
		return SUCCESS;
}

/**
 *  @name        : Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T)
	{
		if (PreOrderTraverse(T->lchild, visit))
			if (PreOrderTraverse(T->rchild, visit))
				if (visit(T->data))
					return SUCCESS;
		return ERROR;
	}
	else
		return SUCCESS;
}

/**
 *  @name        : Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
}

/*�����ǰ�ڵ��ַ�*/
Status print(TElemType e)
{
	printf("\t\t%c", e);
}
