#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//利用栈完成括号匹配
//   ({<>})[]
// 思想：遇到 ({<[ 就入栈， 碰到 )}>] 就出栈
//     	 若栈为空，则不匹配。  若出栈的时候不对应，则不匹配。  结束后栈应为空，否则不匹配

#define STACK_INIT_SIZE 100		//栈初始容量 
#define STACKINCREMENT 10 		//分配的增量

typedef struct {	//栈的结构 
	char* base;		//栈底指针 
	char* top;		//栈顶指针 
	int stacksize;	//栈的当前最大容量 
} SqStack;

void InitStack( SqStack &s );			//初始化栈 
bool StackEmpty( SqStack s ); 			//判断栈空
void Push( SqStack &s, char e );		//入栈，考虑地址分配 
char Pop( SqStack &s ); 				//出栈，考虑栈空 
bool match( char a[], int size );		//括号匹配算法 

int main() 
{
	printf("请输入要检验的括号序列："); 
		
	char a[10] = {'\0'};		//定义字符数组 

	while( scanf("%s", &a) != EOF ) {
		int len = strlen(a); 		//求得字符串的长度
		
		if( match(a, len) )			//如果为true，则匹配、 
			printf("匹配\n");
		else 
			printf("不匹配\n");
	}
	
	return 0;
}

//括号匹配算法 
bool match( char a[], int size ) 
{
	SqStack s;		//定义栈 
	InitStack(s);	//栈初始化 
		
	for( int i=0; i<size; i++) {	//根据长度循环 
		//左括号则全部入栈 
		if( (a[i] == '(') || (a[i] == '[') || (a[i] == '{') || (a[i] == '<') )
			Push( s, a[i] );
		else if( a[i] == ')' ) {
			if(StackEmpty(s))		//如果栈为空，则不匹配 
					return false;
			else if( Pop( s ) != '(' )		//出栈，若不是 ( 则不匹配 ,此时栈内元素已更新 
					return false;
		}
		else if( a[i] == ']' ) {
			if(StackEmpty(s))		//如果栈为空，则不匹配 
					return false;
			else if( Pop( s ) != '[' )		//出栈，若不是 [ 则不匹配 
					return false;
		}
		else if( a[i] == '}' ) {
			if(StackEmpty(s))		//如果栈为空，则不匹配 
					return false;
			else if( Pop( s ) != '{' )		//出栈，若不是 { 则不匹配 
					return false;
		}
		else if( a[i] == '>' ) {
			if(StackEmpty(s))		//如果栈为空，则不匹配 
					return false;
			else if( Pop( s ) != '<' )		//出栈，若不是 < 则不匹配 
					return false;
		}
	}
		
	if( StackEmpty(s) )		//栈为空，则完成匹配 
		return true; 
	return false;
}

void InitStack( SqStack &s ) 	//初始化栈 
{
	s.base = (char *) malloc( STACK_INIT_SIZE*sizeof(char) );
	if( !s.base ) {
		printf("内存分配失败！");
		return; 
	}
	s.top = s.base; 	//初始化栈顶和栈底指针
	s.stacksize = STACK_INIT_SIZE; 	//初始化最大容量 
}

bool StackEmpty( SqStack s ) 	//判断栈空
{
	if(s.top == s.base)	//栈顶指针和栈底指针相同 
		return true;
	else
		return false;
} 

void Push( SqStack &s, char e )		//入栈，考虑地址分配 
{	
	if( s.top - s.base >= s.stacksize ) {	//栈满 重新分配空间 
		s.base = (char *)realloc(s.base, (s.stacksize+STACKINCREMENT) * sizeof(char));
		if( !s.base ) {
			printf("内存分配失败！");
			return; 
		}
		s.top = s.base + s.stacksize;		//使 s.top 正确找到位置 
		s.stacksize += STACKINCREMENT; 
	}
	*s.top++ = e; 		//赋值 
}

char Pop( SqStack &s ) 				//出栈，考虑栈空 
{
	if(StackEmpty(s))
		return '0';
	return *(--s.top);			//将栈顶元素出栈，s.top-- 
}


