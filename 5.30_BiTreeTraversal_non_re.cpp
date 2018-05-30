#include <stdio.h>
#include <stdlib.h>

// 二叉树 非递归遍历

typedef struct BiTNode {	//二叉树结构 
	char data;
	struct BiTNode *lchild, *rchild; //左右节点 
}BiTNode, *BiTree;

typedef BiTNode* ElementType;	//定义元素类型 

typedef struct {		//栈结构 
	ElementType *base;		//栈底指针 
	ElementType *top;		//栈顶指针 
	int stacksize;	//当前可使用最大容量 
}SqStack;

void InitStack( SqStack &s ) {		//初始化栈 
	s.base = (ElementType *)malloc(100 * sizeof(ElementType));
	if(!s.base) {
		printf("内存分配失败");
		return;
	}
	s.top = s.base;			//初始化 
	s.stacksize = 100;
}

void Push( SqStack &s, ElementType e ) {	//将 e 入栈 
	if( s.top - s.base >= s.stacksize ) {
		s.base = (ElementType *)realloc(s.base, ( s.stacksize + 10 )*sizeof(ElementType));
		if(!s.base) {
			printf("内存分配失败");
			return;
		}
		s.top = s.base + s.stacksize;
		s.stacksize += 10;
	}
	*s.top++ = e;
}

int stackEmpty( SqStack s ) {		//判断栈空 
	if( s.top == s.base )
		return 1;
	else 
		return 0;
}

void Pop( SqStack &s, ElementType &e ) {	//出栈 
	if( s.top == s.base ) {
		printf("栈为空");
		return;
	} 
	e = *--s.top;
}

void CreateBiTree( BiTree &T ) {		//先序创建二叉树 
	char ch;
	scanf("%c", &ch);
	if( ch == '#' )
		T = NULL;
	else {
		if( !( T = (BiTNode *)malloc(sizeof(BiTNode)) ) ) {
			printf("内存分配失败");
			return; 
		}
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
} 

void preOrderTraverse(BiTree T) {	//先序遍历   根 > 左 > 右 
	if( !T )
		return ;
	SqStack s;
	InitStack(s);		//初始化栈 
	BiTNode *p = T;
	while( p != NULL || !stackEmpty(s) ) {	//当 p 不为NULL或者栈不为空 
		while( p != NULL ) {
			printf("%c ", p->data);
			Push(s, p);
			p = p->lchild; 
		}
		Pop(s, p);
		p = p->rchild;
	}
}

void inOrderTraverse(BiTree T) {	//中序遍历  左 > 根 > 右 
	if( !T )
		return ;
	SqStack s;
	InitStack(s);
	BiTNode *p = T;
	while( p != NULL || !stackEmpty(s) ) {
		while( p != NULL ) {
			Push(s, p);
			p = p->lchild; 
		}
		Pop(s, p);
		printf("%c ", p->data);
		p = p->rchild;
	}
} 

void postOrderTraverse(BiTree T) {	//后序遍历 
/* 
	若p不存在左孩子和右孩子，则可以直接访问它。
	或者p存在左孩子或者右孩子，但是左孩子和右孩子都已经被访问过了，则可以直接访问该结点。
	若非上述两种情况，则将右孩子和左孩子依次入栈。
	这样可以保证每次取栈顶元素时，左孩子在右孩子前面被访问，根结点在左孩子和右孩子访问之后被访问。
*/ 
	if(!T)
		return ;
	SqStack s;
	InitStack(s);
	
	BiTNode *cur;		//当前节点
	BiTNode *pre = NULL;	//前一次访问节点 
	Push(s, T); 
	
	while( !stackEmpty(s) ) {
		cur = *(s.top-1);
		if( (cur->lchild == NULL && cur->rchild == NULL) || (pre!=NULL && (pre==cur->lchild || pre ==cur->rchild)) ) {
			printf("%c ", cur->data);
			Pop(s, cur);
			pre = cur;
		}
		else {		//先右后左 
			if( cur->rchild != NULL )
				Push(s, cur->rchild);
			if( cur->lchild != NULL )
				Push(s, cur->lchild);
		}
	} 
} 

int main()
{
	BiTree T;		//定义树 
	CreateBiTree( T );
	printf("非递归先序遍历；");
	preOrderTraverse(T);
	printf("\n");
	printf("非递归中序遍历：");
	inOrderTraverse(T);
	printf("\n");
	printf("非递归后序遍历：");
	postOrderTraverse(T);
	return 0;
}
