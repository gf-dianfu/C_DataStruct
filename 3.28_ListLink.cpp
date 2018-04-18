#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {	//单链表存储结构 
	int data;
	struct LNode *next;	//结构类型的指针 
}LNode, *LinkList;

void Create_L( LinkList &L, int n );		//输入n个值 建立单链表 
void Print_L( LinkList L );					//打印链表的值
int GetElem_L(LinkList L, int i, int &e);	//取得第i个数据元素 
int ListInsert_L(LinkList &L, int i, int e);//在带头结点的单链表中第i个位置之前插入元素e
int ListDelete_L(LinkList &L, int i, int &e);//在带头结点的单链表中，删除第i个位置，并由e返回其值

int main() 
{
	LinkList L;
	int n, num;		//序号 
	
	printf("\t\t1.输入n个值，建立单链表 \t\t\n");
	printf("\t\t2.取得第i个数据元素 \t\t\n");
	printf("\t\t3.在第i个位置之前插入元素e \t\t\n");
	printf("\t\t4.删除第i个位置的元素，并返回被删除元素 \t\t\n");
	printf("请选择:");
	
	while( scanf("%d", &n) != EOF ) {
		switch(n) {
			case 1:
				printf("请输入要插入值的数目num：\n");
				scanf("%d", &num);			//输入插入数目 
				Create_L(L, num);
				Print_L(L);
				break;
			case 2:
				printf("请输入要取的位置num：\n");
				scanf("%d", &num);			//输入取的位置 
				int numE;
				numE = 0;
				GetElem_L(L, num, numE);
				printf("%d\n", numE);		//将该位置的元素输出 
				break;
			case 3:
				printf("请输入插入的位置num和元素e：\n");
				int e;						//插入元素 
				e = 0;
				scanf("%d%d", &num, &e);
				ListInsert_L(L, num, e);
				Print_L(L);
				break; 
			case 4:
				printf("请输入删除的位置num：\n");
				scanf("%d", &num);
				int r;						//返回结果
				r = 0; 
				ListDelete_L(L, num, r);
				printf("被删除的元素是%d.\n", r);
				Print_L(L);
				break;
			default:
				printf("输入有误！\n");
				break;
		}
		printf("请选择:");
	}
}

//输入n个值 建立单链表 
void Create_L( LinkList &L, int n )
{
	L = (LinkList)malloc(sizeof(LNode)); //	新建头结点
	L->next = NULL;
	LNode *p;
	for(int i=0; i<n; i++) {
		p = (LinkList)malloc(sizeof(LNode));	//生成一个新节点
		scanf("%d", &p->data);
		p->next = L->next;						//头插法建立单链表 
		L->next = p;
	} 
}

//打印链表的值
void Print_L( LinkList L )
{
	LNode *p;
	p = L->next;
	printf("当前链表中的数据：");
	while( p ) {
		printf("%d ", p->data);
		p = p->next;
	} 
	printf("\n"); 
} 

//取得第i个数据元素
int GetElem_L(LinkList L, int i, int &e)
{
	LNode *p;
	int j=1;
	p = L->next;					//p指向第一个节点，j为计数器 
	while(p && j < i) {
		p = p->next;
		j++;
	} 
	if( !p || j > i )	return 0;	//第i个元素不存在 
	e = p->data;					//将值赋给e 
	return 1;
} 

//在带头结点的单链表中第i个位置之前插入元素e
int ListInsert_L(LinkList &L, int i, int e)
{
	LNode *p, *q;					//q为要插入的节点 
	int j=1;
	p = L->next;					//p指向第一个节点，j为计数器 
	
	while(p && j < i-1) {
		p = p->next;
		j++;
	}
	if( !p || j > i-1 )	return 0;	//i小于1或者大于表长加1 
	
	q = (LinkList)malloc(sizeof(LNode));	//为q生成一个新节点 
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}

//在带头结点的单链表中，删除第i个位置，并由e返回其值
int ListDelete_L(LinkList &L, int i, int &e)
{
	LNode *p;					
	int j=1;
	p = L->next;					//p指向第一个节点，j为计数器
	
	while( p && j < i-1 ) {			//查找到第i-1位置的节点 
		p = p->next;
		j++;
	} 
	
	if(!p || j>i-1)	return 0;		//第i小于1或者大于表长加1  
	e = p->next->data;
	p->next = p->next->next;
	return 1;
} 
 

