#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int binary_search(int *buf, int len, int key)
{
    int left = 0, right = len - 1, mid = 0;

    while(left <= right)
    {
        mid = left + (right - left)/2;  //正确写法,避免溢出问题

        if(buf[mid] == key)             //如果中间数下标等于key, 返回
        {        
            return mid;
        }
        else if(buf[mid] > key)         //如果key在中间数左边, 移动right下标
        {
            right = mid - 1;            //因为mid下标已经比较过了，所以减1
        }
        else                            //如果val在中间数右边, 移动left下标
        {
            left = mid + 1;
        }
    }
    
    return -1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,12,13,45,67,89,99,101,111,123,134,565,677};
    int b[] = {677, 1, 7, 11, 67, 99, 1, 680};

    int i;
    
    for(i = 0; i<sizeof(b)/sizeof(b[0]); i++ )
    {
        printf("%d\n", binary_search(a, sizeof(a)/sizeof(a[0]), b[i]));
    }
    
    return 0;
}