#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int data_cmp(void const *lhs, void const *rhs) 
{
    int const *const l = lhs;
    int const *const r = rhs;
 
    if(*l < *r)
        return -1;
    else if(*l > *r)
        return 1;
    else
        return 0;
 
    // return (*l > *r) - (*l < *r); // 可行的简洁写法
    // return *l - *r; // 错误的简洁写法（若给出 INT_MIN 就会失败）
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,12,13,45,67,89,99,101,111,123,134,565,677};
    int b[] = {677, 1, 7, 11, 67, 99, 1, 680};

    int i;
    
    int const *res;
    
    for(i = 0; i<sizeof(b)/sizeof(b[0]); i++ )
    {
        res = (int *)bsearch(&b[i], a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), data_cmp);
        
        if(res)
            printf("%d\n", (res - a));
        else
            printf("%d\n", -1);
    }
    
    return 0;
}