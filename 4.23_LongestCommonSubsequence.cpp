#include <stdio.h> 
#include <string.h>

//求最长公共子序列 
/*
在母串中不要求连续，只要出现顺序一致就行 
经典DP（dynamic programming）问题，主要找到状态方程，之后就好求解  
maxLen[i][j] 表示 此位置的最长的长度 , 
若str1[i] == str2[j] 则 maxLen[i][j] = maxLen[i-1][j-1] + 1; 

回溯指针找出最长公共子序列时 ，采用一个标记函数Flag[i,j]，当

C[i,j] = C[i-1,j-1]+1 时 标记Flag[i,j]="1";    left_up（左上方箭头）
C[i-1,j] >= C[i,j-1] 时 标记Flag[i,j]="0";         left （左箭头）
C[i-1,j] < C[i,j-1] 时 标记Flag[i,j]="-1";            up（上箭头） 

*/

char res[20];			//存放最长公共子序列 
int flag[20][20];		//标记数组，指出状态的变化，方便回溯 

void PrintSubSequence( int i, int j, int len, char str1[] );  //打印最长公共子序列 

int main()
{
	char str1[20], str2[20];	//定义母串1，2 
	printf("请输入母串1：");
	scanf("%s", &str1);
	printf("请输入母串2：");
	scanf("%s", &str2);
	int len1, len2;				//求得两个母串的长度
	len1 = strlen(str1);
	len2 = strlen(str2);
	
	int maxLen[len1+1][len2+1];		//使用二维数组存储中间的个各种状态
	
	for( int i=0; i<=len1; i++ ) {
		for( int j=0; j<=len2; j++ ) {
			if( i==0 || j==0 )
				maxLen[i][j] = 0;		//初始化一些 0 的位置 
			else if( str1[i-1] == str2[j-1] ) { 	//使用 i-1 和 j-1 从第一个字符开始比较 
				maxLen[i][j] = maxLen[i-1][j-1] + 1;	//相同就将长度加1 
				flag[i][j] = 1;		//说明此处数据来自左上方+1 
			}
			else {										//不同的话就取目前长度的较大值 
				if(maxLen[i-1][j] > maxLen[i][j-1] ) {
					maxLen[i][j] = maxLen[i-1][j];		
					flag[i][j] = -1;		//说明 此处数据来自上方 
				} else {
					maxLen[i][j] = maxLen[i][j-1];
					flag[i][j] = 0;			//说明 此处数据来自作坊 
				}
			} 
		}
	}
	
	for( int i=0; i<=len1; i++ ) {		//状态矩阵 
		for( int j=0; j<=len2; j++ )	
			printf("%d ", maxLen[i][j]);
		printf("\n");
	}
	
	printf("str1和str2的最长公共子序列长度为%d\n", maxLen[len1][len2]);		//打印LCS长度 
	
	PrintSubSequence( len1, len2, maxLen[len1][len2], str1 );
	
	printf("最长公共子序列为%s", res);
	
	return 0; 
}

void PrintSubSequence( int i, int j, int len, char str1[] )		 //打印最长公共子序列
{
	if( i==0 || j==0 )		//如果到矩阵的 0 位置 ，说明没有公共的，结束。 
		return;
	if( flag[i][j] == 1 ) {	//此位置数据来自左上方 
		res[len-1] = str1[i-1];	 //由于数组原因，减去1 然后将该位置字符放进结果数组中 
		i--;		//控制各个标记减 1 
		j--;
		len--;
		PrintSubSequence( i, j, len, str1 );	//继续递归回溯 
	} else if( flag[i][j] == -1 ) {	//说明此位置的数据来自上方 
		i--;		//回退上一行 
		PrintSubSequence( i, j, len, str1 );
	} else {			//说明此位置的数据来自左方
		j--;		 //回退到左边一下 
		PrintSubSequence( i, j, len, str1 );
	}
} 

