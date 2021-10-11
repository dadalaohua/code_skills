#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skiplist.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    skip_list *sl=create_sl();
    int i;
    
    for(i = 1; i < 12345; ++i)
    {
        insert(sl, i, i);
    }
    
    for(i = 11; i < 12345; ++i)
    {
        if(!erase(sl, i))
            printf("Error!\n");
    }
    
    print_sl(sl);
    
    printf("\n");
    
    int *p=search(sl, 10);
    if(p)
        printf("value of key 10 is %d\n", *p);
    
    sl_free(sl);
    
    return 0;
}