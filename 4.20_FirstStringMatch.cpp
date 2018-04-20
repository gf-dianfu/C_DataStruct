#include <stdio.h>
#include <string.h>
 
// s1=aabcc  s2=aabcceeaabdd
// 返回字符串s1在s2中第一次出现的位置

int main()
{
	 
	char str1[20];					//字符串str1 
	char str2[20];					//字符串str2 
	printf("请输入子串str1：");
	scanf("%s", &str1); 
	printf("请输入母串str2：");
	scanf("%s", &str2);
	
	//1、使用strstr()函数直接实现。 
	//找出str2字符串在str1字符串中第一次出现的位置(不包括str2的串结束符) 
	//返回该位置的指针,如找不到,返回空指针  
	
/*	char* ptr;		//定义一个指针，指明位置
	ptr = strstr(str2, str1);
	if( ptr )  
		printf("%d", ptr-str2+1);
	else 
		printf("没有找到."); 
*/	

	//2、手动实现第一次字符匹配 
	 
	int flag = 0;							//设置一个寻找标记，若匹配成功，则 flag = 1； 
	
	for( int i=0; i<strlen(str2);  ) {			//i记录每一次匹配的初始位置 
		
		int mid = i;							//mid为中间变量，与子串匹配使用 
		
		for( int j=0; j<strlen(str1);  ) {		//j为子串的位置变量 
			if( str1[j] == str2[mid] ) {
				mid++;							//若能够匹配，则 mid 和 j 都++ 
				j++;
				if( j == strlen(str1) ) {		//子串匹配成功 
					flag = 1; 
					printf("子串第一次出现从第%d个位置开始.\n", i+1);
					return 0;
				}
			}
			else{								//其中有一个字符不匹配，则 i 位置更新，跳出子串的循环 
				i++;
				break; 
			}
		}
	}
	
	if( !flag )							//标志仍为 0 ，说明匹配失败 
		printf("没有找到.\n");
	
	return 0;
} 
