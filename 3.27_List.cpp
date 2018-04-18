#include <iostream>
#include <stdlib.h>
using namespace std;

#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量 
#define LISTINCREMENT 10	//线性表存储空间的分配增量
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int ElemType;
typedef int Status;

//构建线性表 
typedef struct {
	ElemType *elem;		//存储空间基址 
	int length;			//当前长度 
	int listsize;		//当前分配的存储容量（以sizeof(ElemType)为单位） 
}Sqlist;

Status InitList_Sq(Sqlist &L);							//线性表的初始化
Status Insert(Sqlist &L, int i);						//向初始线性表中插入一些元素
Status ListInsert_Sq(Sqlist &L, int i, ElemType e);		//在顺序表L中第i个位置之前插入新的元素e 
Status ListDelete_Sq(Sqlist &L, int i, ElemType &e);	//在顺序表L中删除第i个元素，并用e返回删除的值
Status PrintList(Sqlist L);								//遍历线性表 

int main()
{
	Sqlist L;
	InitList_Sq(L);
	int num, i, e, n;
	
//	L.elem[0] = 1;
//	L.length = 1;
	
	cout << "1.初始化线性表" << endl;
	cout << "2.向初始化的表中插入n个元素" << endl;
	cout << "3.在顺序表L中第i个位置之前插入新的元素e" << endl;
	cout << "4.在顺序表L中删除第i个元素，并返回删除的值" << endl;

	while(cin >> num) {
		switch(num) {
			case 1:
				 InitList_Sq(L);
				 break;
			case 2:
				cout << "输入n值：" << endl;
				cin >> n;
				Insert(L, n);
				PrintList(L); 
				cout << endl;
				break;
			case 3:
				cout << "请输入合法的i值和要插入的元素e：";
				cin >> i >> e;
				ListInsert_Sq(L, i, e);
				PrintList(L); 
				cout << endl;
				break;
			case 4:
				cout << "请输入合法的i值：";
				cin  >> i;
				ListDelete_Sq(L, i, e);
				cout << "被删除的元素为：" << e << endl;
				PrintList(L); 
				break;
			default:
				cout << "输入有误";
				break; 
		}
	}
	
	return 0;
}


//线性表的初始化 
Status InitList_Sq(Sqlist &L) 	
{
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));		//动态分配内存 
	if(!L.elem) 
		exit(OVERFLOW);
	L.length = 0;					//初始化当前长度为0 
	L.listsize = LIST_INIT_SIZE;	//当前分配容量 
	return OK; 
}

//向初始线性表中插入一些元素
Status Insert(Sqlist &L, int i)
{
	for(int j=0; j<i; j++) {
		cin >> L.elem[j];
		++L.length;
	}
		
	return OK;		 
} 


//在顺序表L中第i个位置之前插入新的元素e 
Status ListInsert_Sq(Sqlist &L, int i, ElemType e) 
{
	if(i < 1 || i > L.length + 1) 	//i值不合法 
		return ERROR;  
	if(L.length >= L.listsize) {	//当前存储空间已满，增加分配
	 	ElemType *newbase;			//新基址；
		
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)); 
		//指针名=（数据类型*）realloc（要改变内存大小的指针名，新的大小）
		
		if(!newbase)		//存储空间分配失败 
			exit(OVERFLOW);
		L.elem = newbase;				//新基址 
		L.listsize += LISTINCREMENT; 	//增加存储容量 
	}
	ElemType *p, *q;
	q = &(L.elem[i-1]);			//q为插入位置
	p = &(L.elem[L.length-1]);	//p为最后一个位置
	for( p; p>=q; p--) 
		*(p+1) = *p;	//元素向后移位 
	*q = e;			//插入e 
	++L.length;  	//表长加1 
	return OK; 
}

//在顺序表L中删除第i个元素，并用e返回删除的值
Status ListDelete_Sq(Sqlist &L, int i, ElemType &e)
{
	if(i < 1 || i > L.length)	//i值不合法 
		return ERROR;
	ElemType *p, *q;
	q = &(L.elem[i-1]);			//q为删除的位置
	p = &(L.elem[L.length-1]); 	//p为最后一个位置
	e = *q;		//被删除的元素赋值给e 
	for(++q; q <= p; q++ )
		*(q-1) = *q;	//被删除之后的元素前移
	--L.length;		//表长减1
	return OK; 
} 

//遍历顺序表
Status PrintList(Sqlist L)
{
	for(int i=0; i<L.length; i++)
		cout << L.elem[i] << " ";
} 


