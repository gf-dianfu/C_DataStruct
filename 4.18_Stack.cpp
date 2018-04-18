#include <stdio.h> 
#include <stdlib.h>

//栈的顺序存储表示

#define STACK_INIT_SIZE 100		//存储空间初始分配量 
#define STACKINCREMENT  10 		//存储空间分配增量 

typedef struct {
	int *base;	//栈底指针 
	int *top;	//栈顶指针
	int stacksize; //栈当前可使用的最大容量 
}SqStack;

void InitStack( SqStack &s ); 			//初始化一个空栈
int StackLength( SqStack s );			//返回栈的长度 
void GetTop( SqStack s, int &e );		//栈不空，则使用e返回栈顶元素 
void Push( SqStack &s, int e );			//插入元素e为新的栈顶元素 
void Pop( SqStack &s, int &e );			//栈不空，则删除栈顶元素，用e返回其值
void Print( SqStack s );				//遍历栈中元素

int main()
{
	printf("\t\t1.初始化一个空栈\t\t\n");
	printf("\t\t2.返回栈的长度\t\t\n");
	printf("\t\t3.返回栈顶元素\t\t\n");
	printf("\t\t4.插入新的栈顶元素 \t\t\n");
	printf("\t\t5.删除栈顶元素，并返回其值\t\t\n");
	printf("\t\t6.遍历栈中元素\t\t\n");
	printf("\t\t0.退出\t\t\n");
	
	int chocie;
	SqStack s;
	
	printf("请选择：");
	
	while( scanf("%d", &chocie) != EOF ) {
		switch( chocie ) {
			case 1:
				InitStack(s); 
				break;
			case 2:
				printf("当前长度为: %d \n", StackLength(s));
				break;
			case 3:
				int ele;
				GetTop(s, ele);
				break;
			case 4:
				int in;
				printf("请输入插入元素的值：");
				scanf("%d", &in);
				Push(s, in);
				break;
			case 5:
				int out;
				Pop(s, out);
				break;
			case 6:
				Print(s); 
				break;
			case 0:
				return 0;
				break;
			default:
				printf("输入有误！\n");
				break;
		}
		printf("请选择：");
	}
	return 0;
} 

void InitStack( SqStack &s ) 			//初始化一个空栈
{
	s.base = (int *)malloc( STACK_INIT_SIZE*sizeof(int) );	//分配初始内存 
	if(!s.base) {
		printf("内存分配失败！\n"); 
		return; 	//内存分配失败 
	}
	s.top = s.base;			//初始化栈顶指针和栈底指针相同 
	s.stacksize = STACK_INIT_SIZE;		//初始化栈的容量 
	printf("初始化成功！\n"); 
} 

int StackLength( SqStack s )			//返回栈的长度 
{
	return s.top-s.base;
}

void GetTop( SqStack s, int &e )		//栈不空，则使用e返回栈顶元素 
{
	if( s.top == s.base ) {
		printf("栈内为空！\n");
		return; 
	}
	e = *(s.top-1);
	printf("%d \n", e);
} 

void Push( SqStack &s, int e )			//插入元素e为新的栈顶元素 
{
	if(s.top - s.base >= s.stacksize ) {	//栈满，则重新分配空间 
		s.base = (int *)realloc( s.base, (s.stacksize + STACKINCREMENT) * sizeof(int) );
		if(!s.base) {
			printf("内存分配失败！\n"); 
			return; 	//内存分配失败 
		}
		s.top = s.base + s.stacksize;	//如果基址改变，则可以使 s.top 正确得到栈顶指针 
		s.stacksize += STACKINCREMENT;	//当前最大容量加增量 
	}
	*s.top++ = e; 	//e赋值给栈顶指针，栈顶指针 +1 
	printf("插入成功!\n");
}

void Pop( SqStack &s, int &e )			//栈不空，则删除栈顶元素，用e返回其值
{
	if( s.top == s.base ) {
		printf("栈内为空！\n");
		return; 
	}
	e = *--s.top;	//将栈顶值赋值 
	printf("删除元素为：%d\n", e);
} 

void Print( SqStack s )					//遍历栈中元素
{
	if( s.top == s.base ) {
		printf("栈内为空！\n");
		return; 
	}
	for(int i=0; i< s.top-s.base; i++)
		printf("%d ", *(s.base+i)); 
	printf("\n");
}
