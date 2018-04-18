#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {	//单链表存储结构 
	int data;
	struct LNode *next;	//结构类型的指针 
}LNode, *LinkList;

void Create_L( LinkList &L, int n );		//输入n个值 建立单链表 
void Print_L( LinkList L );					//打印链表的值


int main() 
{
	LinkList L;
	int n, num;
	printf("\t\t1.输入n个值 建立单链表 \t\t\n");
	printf("\t\t2.打印链表的值 \t\t");
	while( scanf("%d", n) != EOF ) {
		switch(n) {
			case 1:
				printf("请输入要插入值的数目num：\n");
				scanf("%d", &num);
				Create_L(L, num);
				Print_L(L);
		}
	}
}

//输入n个值 建立单链表 
void Create_L( LinkList &L, int n )
{
	L = (LinkList)malloc(sizeof(LNode)); //	新建头结点
	L->next = NULL;
	LNode *p;
	int i;
	for(i=0; i<n; i++) {
		p = (LinkList)malloc(sizeof(LNode));	//生成一个新节点
		scanf("%d ", &p->data);
		p->next = L->next;
		L->next = p;
	} 
}

//打印链表的值
void Print_L( LinkList L )
{
	LNode *p;
	p = L->next;
	while( p ) {
		printf("%d ", p->data);
		p = p->next;
	} 
} 
