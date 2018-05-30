#include <stdio.h>
#include <stdlib.h>

//二叉树 递归遍历 

typedef struct BiTNode {
	char data;				//数据类型 
	struct BiTNode *lchild, *rchild;	//左右节点 
}BiTNode, *BiTree;



void CreateBiTree( BiTree &T ) {	//先序建立二叉树 
	char ch;
	scanf("%c", &ch);
	if( ch == '#' )				//遇到 # 号 表示该节点为空 
		T = NULL;
	else {
		if( !( T = (BiTNode *)malloc(sizeof(BiTNode)) ) ) {	//分配内存 
			printf("内存分配失败！");
			return;
		}
		T->data = ch;				//存储根 
		CreateBiTree(T->lchild);	//左子树 
		CreateBiTree(T->rchild);	//右子树 
	}
	return;
}

void PreOrderTraverse( BiTree T ) {			//先序遍历 
	if(T) {						//树不为空 
		printf("%c ", T->data);		//输出 
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse( BiTree T ) {			//中序遍历 
	if(T) {
		InOrderTraverse(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse(T->rchild); 
	}
} 

void PostOrderTraverse( BiTree T ) {		//后序遍历 
	if(T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->data);
	}
} 

int main()
{
	BiTree T;
	CreateBiTree(T);
	printf("二叉树建立成功！");
	printf("\n");
	printf("先序遍历：");
	PreOrderTraverse(T); 
	printf("\n");
	printf("中序遍历：");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历：");
	PostOrderTraverse(T);
	printf("\n");
	return 0;
} 
