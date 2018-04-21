#include <stdio.h> 
#include <string.h>

//使用经典的 KMP 模式匹配算法进行字符串的模式匹配
//如何求 next 数组， 以及如何定位匹配失败之后对子串匹配的下一个位置 是关键
/*
next[]数组只跟模式串有关，进行递推得出相关算法，
该算法为经典算法，要仔细体会 
主要经典在，主串与模式串匹配失败时， 主串的位置标记不回溯，效率高

*/

int main() 
{
	char string[20];				//定义主串长度 
	char pattern[20];				//定义模式串长度 
	printf("请输入主串：");
	scanf("%s", &string);
	printf("请输入模式串：");
	scanf("%s", &pattern);
	
	int lenS, lenP;					//定义串长度 
	lenS = strlen(string);
	lenP = strlen(pattern);
	
	int next[lenP];					//next[] 数组长度定义为模式串长
	
	//求 next 数组的值 
	int pi=1, pj=0; 				//对模式串进行 pi 和 pj 位置标记	
	next[1] = 0;					//将next[1] 初始为0 
	
	while( pi < lenP ) {			//使用串长控制循环次数 
		//进行匹配，位置 -1 
		if( pj == 0 || pattern[pi-1] == pattern[pj-1] )		//pj等于0或者模式中的两个字符相匹配 
			next[++pi] = ++pj;		//填入next数组的值 
		else
			pj = next[pj];			//不匹配则一直将模式串向右滑动，此时模式串自己与自己匹配，与KMP匹配思想一致 
	}
	
//刚开始在next数组内容一直不对，经排查，是由于我将字符串存在数组中，数组从 0 开始匹配
//而书中的思想是字符串从第 1 个位置开始，将每次匹配的时候，标记-1则可正确运行 
	
//	for( int i=1; i<=lenP; i++ ) 
//		printf("%d ", next[i]); 

	//开始进行模式匹配
	int i=1, j=1;					//位置标记，i为主串位置标记， j为模式串位置标记
	while( i <= lenS && j <= lenP ) {	//主串和模式串都没有到末尾 
		//匹配 位置 -1		
		if( string[i-1] == pattern[j-1] || j ==0 ) {	//字符匹配 或者 位置标记 j 的值为0 
			i++;					// j的值为0 说明主串当前位置 不能与 模式串当前的头部匹配 
			j++;					//继续比较后续字符 
		} else 
			j = next[j];			//模式串向右移动 
	}
	if( j > lenP )					//说明匹配成功 
		printf("匹配成功，模式串第一次出现从第%d个位置开始", i-lenP);
	else
		printf("匹配失败！");
	
	return 0; 
}

