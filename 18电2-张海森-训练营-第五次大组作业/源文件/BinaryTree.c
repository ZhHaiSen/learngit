#include <stdio.h>
#include "BinaryTree.h"
#include ".archivetempLQueue.h"

extern LQueue *n;
extern char *queue;

/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : 构造空二叉树T
 *  @param       : 二叉树根结点T
 */
Status InitBiTree(BiTree *T)
{
	if (T == NULL)
	{
		printf("\t\t内存不足\n");
		return ERROR;
	}
	*T = NULL;
	printf("\t\t初始化成功\n");
	return SUCCESS;
}


/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : 摧毁二叉树T
 *  @param       : 二叉树根结点T
 */
Status DestroyBiTree(BiTree *T)
{
	if (*T != NULL)
	{
		DestroyBiTree((*T)->lchild);
		DestroyBiTree((*T)->rchild);
		free(*T);
	}
	printf("\t\t销毁成功\n");
	return SUCCESS;
}

/**
 *  @name        : Status CreateBiTree(BiTree T, char* definition);
 *  @description : 构造二叉树T
 *  @param       : 二叉树根结点T, 二叉树先序遍历字符串definition
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
				printf("\t\t内存不足\n");
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
 *  @description : 先序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 中序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 后序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 层序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
}

/*输出当前节点字符*/
Status print(TElemType e)
{
	printf("\t\t%c", e);
}
