#include <stdio.h>
/*
输入
	每组数据两行。第一行是整数 m ，表示有 m 个加号要放( 0<=m<=50) 以及 整数位数 n 
	第二行是若干个数字。数字总数 n 不超过50,且 m <= n-1
输出
	对每组数据，输出最小加法表达式的值

V( m, n ) = min{ V(m-1, i) + Num( i+1, n ) } 
V(m-1, i) 表示从前 i 位， 放入 m-1 个加号 的最小值
Num(i, j) 表示第 i 位到 第j位 所组成的数，从 第 1 位开始算。 

*/
#define INF 99999999	//定义为无穷 

int a[1000];		//定义整数串 以及 整数组成的结果数组 
int num[1000][1000]; 

int V( int m, int n )			//求 在 n个整数中放入m个加号的最小加法表达式的值 
{
	if( m == 0 )			//没有加号，则返回该整数串组成的整数值 
		return num[1][n];
	else if( n < m+1 )		//加号过多，返回无穷
		return INF;
	else {
		int min = INF;		//初始一个最小值 
		for( int i=m; i<=n-1; i++ ) {
			if( V( m-1, i ) < min )		//比较 V(m-1, i) 与min 的较小值 
				min = V( m-1, i ) + num[i+1][n];
			else
				min += num[i+1][n];
		} 
		return min;
	} 
}

int main()
{
	int m, n;					//定义加号数量以及整数位数 
	printf("请输入加号的数量以及整数位数："); 
	
	while( scanf("%d %d", &m, &n) ) {	//录入加号数量和整数位数 
		for( int i=1; i<=n; i++ ) 
			scanf("%d", &a[i]);
		for( int i=1; i<=n; i++ ) {
			num[i][i] = a[i];		//只有一个数字的时候
			for( int j=i+1; j<=n; j++ )
				num[i][j] = num[i][j-1]*10 + a[j]; //不止一个数字时这样计算组成的数字 
		}
		printf("最小加法表达式的值为：%d\n", V( m, n ));
		printf("请输入加号的数量以及整数位数："); 
	}
	
	return 0;
}
