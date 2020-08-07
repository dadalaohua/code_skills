#include <stdio.h>

int binary_search(int *buf, int len, int key, int* ansl, int* ansr)
{
    int left  = 0, right = len - 1;
    int mid   = 0;
    
    *ansl = -1;
    *ansr = -1;
    
    //先计算区间的左边界
    left  = 0;
    right = len - 1;
    
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        
        if (buf[mid] > key)
        {
            right = mid - 1;
        }
        else if(buf[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            *ansl = mid;
            right = mid - 1;
        }
    }
    
    //再计算区间的右边界
    left  = 0;
    right = len - 1;
    
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        
        if (buf[mid] > key)
        {
            right = mid - 1;
        }
        else if(buf[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            *ansr = mid;
            left = mid + 1;
        }
    }

    return 0;
}

/****************************/

int main(int argc, char* argv[])
{
    int a[] = {1, 1, 2, 2, 2, 3, 3, 5, 5, 5};
    int b[] = {0, 1, 2, 3, 4, 5, 6};
    int left, right;
    int i;
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        binary_search(a, sizeof(a)/sizeof(a[0]), b[i], &left, &right);
        printf("val %d, left %d, right %d\n", b[i], left, right);
    }
    
    return 0;
}