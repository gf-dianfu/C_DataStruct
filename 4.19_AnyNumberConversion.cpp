#include <stdio.h>
#include <stdlib.h>

//使用栈来实现十进制转换为任意进制的数制转换

#define INIT_STACK_SIZE 100			//初始容量 
#define STACKINCREMENT 10			//增量 

typedef struct {
	int *base;		//栈底指针 
	int *top;		//栈顶指针 
	int stacksize;	//当前栈的最大容量 
} SqStack;	 

void InitStack( SqStack &s );				//初始化栈 
void Push( SqStack &s, int e );				// 入栈, 考虑地址分配问题 
void Pop( SqStack &s);						//出栈，考虑栈空问题
bool StackEmpty( SqStack s );				//判栈空 				
void conversion(int num, int jinzhi); 		//进制转换函数


int main()
{
	int num, digital;	//数字和进制 
	printf("请输入要转换的数字（非负十进制）：");
	scanf("%d", &num);
	printf("请输入要转换为几进制（2、8、16）：");
	scanf("%d", &digital);
	
	//进制转换主函数 
	conversion(num, digital);
	
	return 0; 
}

//进制转换函数
void conversion(int num, int jinzhi)
{
	SqStack s;
	InitStack( s );
	
	while( num ) {
		Push(s, num%jinzhi);		//入栈 
		num /= jinzhi; 	//更新num 
	}
	
	printf("转换之后的结果为：");
	while( !StackEmpty(s) ) 
		Pop(s);		//出栈 
} 

//初始化栈 
void InitStack( SqStack &s )
{
	s.base = (int *)malloc( INIT_STACK_SIZE * sizeof(int) );	//分配初始内存 
	if( !s.base ) {
		printf("内存分配失败！");
		return; 
	}
	
	//ps：写的时候这个地方写反了，一直找不到错误 = = ，大大的教训， 多踩坑 
	s.top = s.base;			//初始化栈顶和栈底指针 			
	
	s.stacksize = INIT_STACK_SIZE;	//初始化栈的最大容量
}

// 入栈, 考虑地址分配问题 
void Push( SqStack &s, int e )
{
	if(s.top - s.base >= s.stacksize ) {	//栈满，则重新分配空间 
		s.base = (int *)realloc( s.base, (s.stacksize + STACKINCREMENT) * sizeof(int) );
		if(!s.base) {
			printf("内存分配失败！\n"); 
			return; 					//内存分配失败 
		}
		s.top = s.base + s.stacksize;	//如果基址改变，则可以使 s.top 正确得到栈顶指针 
		s.stacksize += STACKINCREMENT;	//当前最大容量加增量 
	}
	
	*s.top++ = e;		//赋值 
}

//出栈，考虑栈空问题
void Pop( SqStack &s)
{
	if( s.top == s.base ) {
		printf("栈内为空！\n");
		return; 
	}
	
	int re =  *--s.top;			//取栈顶元素 
	char z = 'A';				//方便16进制计算字母 
	
	if( re >= 10 ) 				//打印结果 
		printf("%c", z+re-10 );	
	else 
		printf("%d", re);		
} 

//判栈空 
bool StackEmpty( SqStack s )
{
	if( s.top == s.base )
		return true;
	else 
		return false;
}
