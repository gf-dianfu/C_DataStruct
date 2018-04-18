#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {		//单链表存储结构 
	int data;
	struct LNode *next;		//结构类型指针 
}LNode, *LinkList;

//函数声明 
void Init_L( LinkList &L );						//初始化带头节点的链表
void Creat_L( LinkList &L );				//尾插法建立单链表
void Print_L( LinkList L );						//打印链表中的元素
int Find_L( LinkList L, int n );				// 单链表中查找给定值，并返回位置
void Delete_L( LinkList &L, int n );			//删除给定元素 
void Insert_L( LinkList &L, int i, int e );		//在指定位置插入一个值
void Reverse_L( LinkList &L ); 					//逆序输出链表 

int main()
{
	LinkList L;
	int choice;
	
	printf("\t\t1.初始化带头节点的链表.\t\t\n");
	printf("\t\t2.尾插法建立单链表.\t\t\n");
	printf("\t\t3.在单链表中查找给定值，并返回位置.\t\t\n");
	printf("\t\t4.删除给定元素.\t\t\n");
	printf("\t\t5.在指定位置插入一个值.\t\t\n");
	printf("\t\t6.链表逆序输出.\t\t\n");
	printf("\t\t0.退出.\t\t\n");
	
	printf("请选择："); 
	
	while( scanf("%d", &choice) != EOF ) {
		switch(choice) {
			case 0:
				return 0; 
			case 1:
				Init_L(L);
				break;
			case 2:
				printf("请输入要插入元素的值num(EOF结束)："); 
				Creat_L(L);
				Print_L(L);
				break;
			case 3:
				printf("请输入要查找的元素的值digit_find："); 
				int digit_find;							//要查找的元素
				scanf("%d", &digit_find);
				Find_L(L, digit_find);
				break;
			case 4:
				printf("请输入要删除的元素的值digit_dl：");
				int digit_dl;							//要查找的元素
				scanf("%d", &digit_dl);
				Delete_L(L, digit_dl);
				Print_L(L);
				break;
			case 5:
				printf("输入要插入的元素的位置pos和值digit:");
				int pos, digit;
				pos = 0;
				scanf("%d%d", &pos, &digit);
				Insert_L(L, pos, digit);
				Print_L(L);
				break;
			case 6:
//				printf("当前链表逆序输出为:");
				Reverse_L(L); 
				Print_L(L);
				break;
			default:
				printf("输入有误！");
				break;
		}
		printf("请选择："); 
	}
	
	return 0;
} 

//初始化带头节点的链表
void Init_L( LinkList &L )
{
	L = (LinkList)malloc(sizeof(LNode));	//头结点 
	L->next = NULL;
	printf("初始化成功.\n"); 
} 

//尾插法建立单链表
void Creat_L( LinkList &L )
{
	int num; 
	LNode *p, *r;	//p为新节点 
	r = L;			//r始终指向最后一个节点 
	
	while(scanf("%d", &num) != EOF) {
		p = (LinkList)malloc(sizeof(LNode));	//为新节点分配空间
		p->data = num; 
		p->next = r->next; 
		r->next = p;
		r = p;
	}

	r->next = NULL;		//最后记得置空 
	return; 
} 

// 单链表中查找给定值，并返回位置
int a[10];		//使用数组记录出现的多个位置 

int Find_L( LinkList L, int n )
{
	LNode *p;	//遍历所用指针
	int i, j;		//i为位置计数器, j为找到数目计数器 
	i = j = 0;
	
	p = L->next;
	while( p ) {
		i++;
		if( p->data == n ) {
			a[j++] = i;		//找到之后先把位置放在数组，再加1	
		} 
		p = p->next;
	}
	if( j == 0 ) {			//没找到 
		printf("该链表中没有值为%d的数\n", n);
	} 
	else {
		printf("值为%d的数在链表中的位置为：", n);
		for( int i=0; i<j; i++ )
			printf("%d ", a[i]); 
		printf("\n");
	} 
	return j;
}

//删除给定元素 
void Delete_L( LinkList &L, int n ) 
{
	int size;	//数组的长度
	LNode *r;	//被删除的元素 
	size = Find_L(L, n);
	for( int i=0; i<size;  ) {
		LNode *p;
		p = L;
		int j;		//计数器
		j = 0; 
		if(a[i] == 1) {		//若删除的元素为第一个 
			r = p->next; 
			L->next = r->next ;
			free(r);			//记住删除之后要释放r的空间 
		} else {
			while( j < a[i]-1 ) {	//找到要删除位置的前一个元素 
				j++;
				p = p->next;
			}
			r = p->next;
			p->next = r->next; 
			free(r);			//记住删除之后要释放r的空间 
		}
		Print_L(L);					//打印当前的链表数据 
		size = Find_L(L, n);		//更新size值，以及更新要删除数据的位置 
	}
	return;
}

//在指定位置插入一个值
void Insert_L( LinkList &L, int i, int e ) 
{
	LNode *p, *q;	//p要插入的节点, q为遍历节点 
	int j=0; 	//计数器
	p = (LinkList)malloc(sizeof(LNode));
	p->data = e;
	q = L;
	if( i==1 ) {			//如果在表头插入 
		p->next = q->next;
		L->next = p;
		return;
	} 
	while( q && j < i-1 ) {		//在其他位置插入，遍历到插入位置前一个节点 
		j++;
		q = q->next;
	} 
	if(!q || j > i-1) {		//插入位置有误 
		printf("i值不合法！\n");
		return;
	}
	p->next = q->next;		//插入p节点 
	q->next = p;
	return;
}

//逆序输出链表 
void Reverse_L( LinkList &L ) 
{
	LNode *Lr, *p, *q;					//p为遍历节点，q为新链表的新节点 
	Lr = (LinkList)malloc(sizeof(LNode));	//新链表表头 
	Lr->next = NULL;
	p = L->next;
	while( p ) {
		q = (LinkList)malloc(sizeof(LNode));
		q->data = p->data;
		q->next = Lr->next;
		Lr->next = q;
		p = p->next;
	}
	L = Lr; 
	return;
}

//打印链表中的元素
void Print_L( LinkList L )
{
	LNode *p;
	p = L->next;
	printf("当前链表输出为：");
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
 
