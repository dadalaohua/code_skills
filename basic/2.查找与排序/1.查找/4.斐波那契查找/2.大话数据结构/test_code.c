#include <stdio.h>
#include <stdlib.h>

int F[100]; /* 斐波那契数列 */

/* 斐波那契查找 */
/* 传入的数组，查找是从下标1开始，不含下标0的数，长度也不包含下标0的数*/
/* 返回0表示没有找到 */
/* 这个版本需要将数组补齐到斐波那契数的长度，会造成数组越界 */
int Fibonacci_Search(int *a,int n,int key)
{
	int low,high,mid,i,k=0;
	low=1;	/* 定义最低下标为记录首位 */
	high=n;	/* 定义最高下标为记录末位 */
	while(n>F[k]-1)
		k++;
	for (i=n;i<F[k]-1;i++)
		a[i]=a[n];
	
	while(low<=high)
	{
		mid=low+F[k-1]-1;
		if (key<a[mid])
		{
			high=mid-1;		
			k=k-1;
		}
		else if (key>a[mid])
		{
			low=mid+1;		
			k=k-2;
		}
		else
		{
			if (mid<=n)
				return mid;		/* 若相等则说明mid即为查找到的位置 */
			else 
				return n;
		}
		
	}
	return 0;
}

/****************************/

int main(int argc, char* argv[])
{
    int a[100] = {1,2,3,4,5,6,7,8,9,12,13,45,67,89,99,101,111,123,134,565,677};
    int b[] = {677, 1, 7, 11, 67, 99, 1, 680};

    int i;
    
    F[0]=0;
    F[1]=1;
    for(i = 2;i < 100;i++)  
    { 
        F[i] = F[i-1] + F[i-2];  
    } 
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        printf("%d\n", Fibonacci_Search(a, 20, b[i]));
    }
    
    return 0;
}
