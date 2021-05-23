#include <stdio.h>
#include <stdlib.h>

/* 顺序查找 */
/* 传入的数组，查找是从下标1开始，不含下标0的数，长度也不包含下标0的数*/
/* 返回0表示没有找到 */

/* 无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a,int n,int key)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if (a[i]==key)
			return i;
	}
	return 0;
}
/* 有哨兵顺序查找 */
/* 会修改数值下标为0的数值 a[0]=key */
int Sequential_Search2(int *a,int n,int key)
{
	int i;
	a[0]=key;
	i=n;
	while(a[i]!=key)
	{
		i--;
	}
	return i;
}

/* 自己修改的版本 */
/* 从下标0开始，比较符合使用习惯 */
/* 返回-1表示没有找到 */
int Sequential_Search_3(int *a,int n,int key)
{
	int i;
	for(i=0;i<n;i++)
	{
		if (a[i]==key)
			return i;
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
        printf("%d\n", Sequential_Search_3(a, sizeof(a)/sizeof(a[0]), b[i]));
    }
    
    printf("\n");
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        printf("%d\n", Sequential_Search(a, sizeof(a)/sizeof(a[0]) - 1, b[i]));
    }
    
    printf("\n");
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        printf("%d\n", Sequential_Search2(a, sizeof(a)/sizeof(a[0]) - 1, b[i]));
    }

    return 0;
}
