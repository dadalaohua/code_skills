#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ksort.h"

KSORT_INIT_GENERIC(int)

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};
    int ret;
    
    printf("The orginal data array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]);
    
    printf("\n");
    
    //寻找第5小的数值
    ret = ks_ksmall(int, 10, buf, 5);
    
    printf("ret = %d\n", ret);
    
    //寻找第0小的数值
    ret = ks_ksmall(int, 10, buf, 0);
    
    printf("ret = %d\n", ret);
    
    printf("\nThe result of sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n");
    
    return 0;
}