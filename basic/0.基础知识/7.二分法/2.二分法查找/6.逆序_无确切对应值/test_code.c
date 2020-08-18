#include <stdio.h>

int binary_search(int *buf, int len, int key, int* ansl, int* ansr)
{
    int left  = 0, right = len - 1;
    int mid   = 0;
    
    if(key < buf[right])
    {
        *ansl = right;
        *ansr = -1;
    }
    else if(key > buf[left])
    {
        *ansl = -1;
        *ansr = left;
    }
    else
    {
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            
            if (buf[mid] < key)
            {
                right = mid - 1;
            }
            else if(buf[mid] > key)
            {
                left = mid + 1;
            }
            else
            {
                right = left = mid;
                break;
            }
        }
        
        *ansl = right;
        *ansr = left;
    }

    return 0;
}

/****************************/

int main(int argc, char* argv[])
{
    int a[] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    int b[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int c[] = { 5, 15, 25, 35, 45, 55, 65, 75, 85,  95, 105};
    int left, right;
    int i;
    
    for(i = 0; i < sizeof(b)/sizeof(b[0]); i++)
    {
        binary_search(a, sizeof(a)/sizeof(a[0]), b[i], &left, &right);
        printf("val %d, left %d, right %d\n", b[i], left, right);
    }
    
    for(i = 0; i < sizeof(c)/sizeof(c[0]); i++)
    {
        binary_search(a, sizeof(a)/sizeof(a[0]), c[i], &left, &right);
        printf("val %d, left %d, right %d\n", c[i], left, right);
    }
    
    return 0;
}