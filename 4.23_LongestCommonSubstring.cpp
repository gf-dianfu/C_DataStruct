#include <stdio.h>
#include <string.h> 

//求最长公共子串
/*
公共子串要求必须连续 
经典DP（dynamic programming）问题，主要找到状态方程，之后就好求解  
maxLen[i][j] 表示 此位置的最长的长度 , 
若str1[i] == str2[j] 则 maxLen[i][j] = maxLen[i-1][j-1] + 1; 
*/ 

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
	
	int result = 0;				//记录最终结果 
	int end_index = 0;			//记录匹配最长子串的结尾位置 
	int maxLen[len1+1][len2+1];
	
	for( int i=0; i<=len1; i++) {
		for( int j=0; j<=len2; j++ ) {
			if( i==0 || j==0 )		//初始化 
				maxLen[i][j] = 0;
			else if( str1[i-1] == str2[j-1] ) {		//若比较相等，则长度+1，并将result取目前的较大值 
				maxLen[i][j] = maxLen[i-1][j-1] + 1;
				if( maxLen[i][j] > result ) {
					end_index = i;		//满足条件之后再更新 end_index 的值 
					result = maxLen[i][j];
				}
			}
			else
				maxLen[i][j] = 0;	//若比较不等，则将长度置为0 
		}
	}
//	for( int i=0; i<=len1; i++ ) {		//状态矩阵 
//		for( int j=0; j<len2; j++ )	
//			printf("%d ", maxLen[i][j]);
//		printf("\n");
//	}
	printf("str1和str2的最长公共子串长度为%d，最长公共子串为：", result);
	for( int i= end_index-result; i<end_index; i++) {	//反推出最长公共子串的起始位置，打印 
		printf("%c", str1[i]);
	}
	return 0; 
} 

