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
    int i, buf[10] = {-7,0,1,2,3,5,6,8,9,12};

    srand48(11);
    
    printf("The orginal data array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]);
    
    printf("\n");
    
    ks_shuffle(int, 10, buf);

    printf("\nThe result of sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n");
    
    return 0;
}