#include <stdio.h>
#include <string.h>

//假设有几种硬币，如 1、3、5 ，并且数量无限。请找出能够组成某个数目的找零所使用最少的硬币数。

int main()
{
	int coin[] = { 1, 3, 5 };			//定义三种硬币 
	printf("请输入需要找零的钱数：");
	int change;							//找零的钱 
	scanf("%d", &change);
	
	int sum[change+1]; 					//定义最少需要的硬币数目的数组 
	int coinValue[change+1];			//使用的硬币面值，方面输出 
	memset(sum, 0, change+1);			//将sum初始化为0 
	
	for( int i=1; i<=change; i++ ) {
		int minNum = i; 				//表示当前来说的找零的最少值，并不是所有中最少的，下面开始找更小的
		int needCoin = 0;				//本次需要的硬币的编号 
		for( int j=0; j<=2; j++ ) {
			if( i >= coin[j] ) {		//找零的钱大于硬币的值 
//				printf("%d ",sum[i-coin[j]] + 1 );
				if( sum[i-coin[j]] + 1 <= minNum ) {		//当前最少的个数小于等于定义的硬币个数 
					if( i-coin[j] == 0 || coinValue[i-coin[j]] != 0 ) {
						minNum = sum[i-coin[j]] + 1;		//能找开零钱则更新值 
						needCoin = coin[j];
					}
				}
			}
		}
		
		sum[i] = minNum;				//将当前最少的个数赋值给sum[i] 
		coinValue[i] = needCoin; 		//记录使用的哪个硬币 
//		printf("%d %d", sum[i], coinValue[i]);
//		printf("\n");
	}
	
	if(coinValue[change] == 0) {
		printf("找不开");
	} else {
		printf("最少硬币个数为:%d\n硬币为：", sum[change]);
		while( change > 0 ) {
			printf("%d ", coinValue[change]);
			change -= coinValue[change];	//这里还是很巧妙的，将下标减去合适的值 
		}
	}
	
	return 0;	
} 
 
