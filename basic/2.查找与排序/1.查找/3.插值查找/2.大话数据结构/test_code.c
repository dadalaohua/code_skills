#include <stdio.h>
#include <stdlib.h>

/* 插值查找 */
/* 传入的数组，查找是从下标1开始，不含下标0的数，长度也不包含下标0的数*/
/* 返回0表示没有找到 */
int Interpolation_Search(int *a,int n,int key)
{
	int low,high,mid;
	low=1;	/* 定义最低下标为记录首位 */
	high=n;	/* 定义最高下标为记录末位 */
	while(low<=high)
	{
		mid=low+ (high-low)*(key-a[low])/(a[high]-a[low]); /* 插值 */
		if (key<a[mid])		/* 若查找值比插值小 */
			high=mid-1;		/* 最高下标调整到插值下标小一位 */
		else if (key>a[mid])/* 若查找值比插值大 */
			low=mid+1;		/* 最低下标调整到插值下标大一位 */
		else
			return mid;		/* 若相等则说明mid即为查找到的位置 */
	}
	return 0;
}

/* 自己修改的版本 */
/* 从下标0开始，比较符合使用习惯 */
/* 返回-1表示没有找到 */
int Interpolation_Search_2(int *a,int n,int key)
{
	int low,high,mid;
	low=0;	/* 定义最低下标为记录首位 */
	high=n-1;	/* 定义最高下标为记录末位 */
	while(low<=high)
	{
		mid=low+ (high-low)*(key-a[low])/(a[high]-a[low]); /* 插值 */
		if (key<a[mid])		/* 若查找值比插值小 */
			high=mid-1;		/* 最高下标调整到插值下标小一位 */
		else if (key>a[mid])/* 若查找值比插值大 */
			low=mid+1;		/* 最低下标调整到插值下标大一位 */
		else
			return mid;		/* 若相等则说明mid即为查找到的位置 */
	}
	return -1;
}

/****************************/

int main(int argc, char* argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,12,13,45,67,89,99,101,111,123,134,565,677};
    int b[] = {677, 1, 7, 11, 67, 99, 1, 680};

    int i;
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        printf("%d\n", Interpolation_Search(a, sizeof(a)/sizeof(a[0]) - 1, b[i]));
    }
    
    printf("\n");
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        printf("%d\n", Interpolation_Search_2(a, sizeof(a)/sizeof(a[0]), b[i]));
    }
    
    return 0;
}
