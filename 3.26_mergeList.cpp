#include <iostream>
using namespace std;

int a[] = {3, 5, 8, 11};
int b[] = {2, 6, 8, 9, 11, 15, 20};

//合并两个有序数组 
void MergeList(int La[], int Lb[], int Lc[])
{
	int i, j, k;
	int lenA, lenB;
	i = j = k = 0;
	lenA = sizeof(a)/sizeof(int);
	lenB = sizeof(b)/sizeof(int);
	
	while( (i < lenA ) && (j < lenB ) ) {	//La和Lb均非空 
		if( La[i] <= Lb[j]) 	
			Lc[k++] = La[i++];	//将La[i] 赋值给 Lc[k] 
		else
			Lc[k++] = Lb[j++];  //将Lb[j] 赋值给 Lc[k] 
	}
	
	while( i < lenA ) 		//La数组有剩余 
		Lc[k++] = La[i++];
		
	while( j < lenB )		//Lb数组有剩余 
		Lc[k++] = Lb[j++];
}

int main()
{
	
	int lenA, lenB, lenC;
	lenA = sizeof(a)/sizeof(int);
	lenB = sizeof(b)/sizeof(int);
	lenC = lenA + lenB;
	int c[lenC];	//c数组的长度为a和b之和 
	
	MergeList(a, b, c);		//合并 
	
	for(int i=0; i<lenC; i++)
		cout << c[i] << " ";	//打印输出 
		
	return 0;
}
