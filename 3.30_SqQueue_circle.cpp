#include <stdio.h>
#include <stdlib.h> 

#define MAXQSIZE 100	//最大队列长度 

typedef struct {		//队列的顺序存储结构 
	int *base;			//初始化的动态分配存储空间
	int front;			//头指针，队列不空，则指向队列头元素 
	int rear; 			//尾指针，队列不空，则指向队尾元素的下一个位置 
} SqQueue;

//函数声明
void InitQueue( SqQueue &Q );				//初始化队列，构造一个空队列 
int QueueLength( SqQueue Q );				//返回队列的长度
void EnQueue ( SqQueue &Q, int e );			//入队，即插入元素到队尾 
void DeQueue( SqQueue &Q );					//出队，即删除队头元素， 队列不空则返回删除元素 
void FindQueue( SqQueue Q, int n );			//查找元素
void PrintQueue( SqQueue Q );				//遍历输出队列


//循环队列，插入，查找，删除，空判断，满判断，算法实现
int main()
{
	printf("\t\t1.初始化队列.\t\t\n");
	printf("\t\t2.入队，即插入元素到队尾 .\t\t\n");
	printf("\t\t3.出队，即删除队头元素.\t\t\n");
	printf("\t\t4.查找元素.\t\t\n");
	printf("\t\t5.遍历输出队列.\t\t\n");
	printf("\t\t0.退出\t\t\n");
	
	printf("请选择：");
	int choice;			//选项 
	SqQueue Q;
	
	while( scanf("%d", &choice) != EOF ) {
		switch(choice) {
			case 1:
				InitQueue(Q);
				break;
			case 2:
				printf("请输入要入队的元素的值：");
				int in_value;
				scanf("%d", &in_value);
				EnQueue(Q, in_value);
				PrintQueue(Q);
				break;
			case 3:
				DeQueue(Q);
				PrintQueue(Q);
				break;
			case 4:
				printf("请输入查找的元素的值：");
				int find_value;				//要查找的值 
				scanf("%d", &find_value); 
				FindQueue(Q, find_value);
				break;
			case 5:
				PrintQueue(Q);
				break;
			case 0:
				return 0; 
			default:
				printf("输入有误!\n");
				break; 
		}
		printf("请选择：");
	}
	
	return 0;
} 

//初始化队列，构造一个空队列 
void InitQueue( SqQueue &Q )
{
	Q.base = (int *) malloc(MAXQSIZE * sizeof(int));	//初始分配存储空间 
	if( !Q.base ) {					//内存分配失败 
		printf("初始化失败！\n");
		return;
	}
	Q.front = Q.rear = 0;			//初始化头指针和尾指针 
	printf("初始化成功！\n");
	return; 
} 
 
//返回队列的长度
int QueueLength( SqQueue Q )
{
	return ( Q.rear - Q.front + MAXQSIZE ) % MAXQSIZE;	//返回队列中元素的个数 
} 

//入队，即插入元素到队尾 
void EnQueue ( SqQueue &Q, int e )
{
	if( (Q.rear + 1) % MAXQSIZE == Q.front ) {			//队满条件 
		printf("队列已满！\n");
		return;
	} 
	Q.base[Q.rear] = e;						//元素赋值给队尾 
	Q.rear = ( Q.rear + 1 ) % MAXQSIZE;		//队尾加1条件 
	return;
}

//出队，即删除队头元素， 队列不空则返回删除元素 
void DeQueue( SqQueue &Q )
{
	if( Q.rear == Q.front ) {				//队空条件 
		printf("队列为空！\n");
		return;
	}
	
	int out_value;				//出队元素 
	out_value = Q.base[Q.front];
	
	Q.front = ( Q.front + 1 ) % MAXQSIZE;	//队头加1 
	printf("出队的元素的值为：%d\n", out_value);
	return;
}

//查找元素
void FindQueue( SqQueue Q, int n) 
{
	if( Q.rear == Q.front ) {				//队空条件 
		printf("队列为空！\n");
		return;
	}
	
	int a[10];			//存放查找到元素的位置 
 	int i=0;			//计数器，查找元素的个数 
 	
	while( Q.front != Q.rear ) {
		if( Q.base[Q.front] == n ) {
			a[i++] = Q.front+1;		//Q.front 也是从0开始 
		}
		Q.front = ( Q.front + 1 ) % MAXQSIZE; 
	}
	
	if(i == 0) {
		printf("队列中没有值为%d的元素！\n", n);
		return;
	} else {
		printf("队列中值为%d的元素有%d个，位置为：", n, i);
		for(int j=0; j<i; j++)
			printf("%d ", a[j]);
	}
	printf("\n");
	return;
}

//遍历输出队列
void PrintQueue( SqQueue Q )
{
	if( Q.rear == Q.front ) {				//队空条件 
		printf("队列为空！\n");
		return;
	}
	
	int len;
	len =  QueueLength(Q);		//队列长度 
	printf("当前队列长度为%d，数据元素为：",len);
	while( Q.front != Q.rear ) {			//遍历 
		printf( "%d ", Q.base[Q.front] );
		Q.front = ( Q.front + 1 ) % MAXQSIZE; 
	}
	printf("\n");
} 
