#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "bget.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
char membuf[10240];

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    bufsize cural, totfree, maxfree;
    long nget, nfree;
    
    char  *ptr;
    char  *ptr2;
    
    //初始化
    bpool((void *) membuf, (bufsize) sizeof(membuf));
    
    //查看状态
    bstats(&cural, &totfree, &maxfree, &nget, &nfree);
    printf("info: %ld gets, %ld releases.  %ld in use, %ld free, largest = %ld\n",
            nget, nfree, (long) cural, (long) totfree, (long) maxfree);
    
    //申请buff
    ptr = (char *) bget(1024);
    
    //查看申请buff之后的状态
    bstats(&cural, &totfree, &maxfree, &nget, &nfree);
    printf("info: %ld gets, %ld releases.  %ld in use, %ld free, largest = %ld\n",
            nget, nfree, (long) cural, (long) totfree, (long) maxfree);
            
    //申请buff
    ptr2 = (char *) bget(4096);
    
    //查看申请buff之后的状态
    bstats(&cural, &totfree, &maxfree, &nget, &nfree);
    printf("info: %ld gets, %ld releases.  %ld in use, %ld free, largest = %ld\n",
            nget, nfree, (long) cural, (long) totfree, (long) maxfree);
    
    //释放buff
    brel((void *) ptr);
    
    //查看释放buff之后的状态
    bstats(&cural, &totfree, &maxfree, &nget, &nfree);
    printf("info: %ld gets, %ld releases.  %ld in use, %ld free, largest = %ld\n",
            nget, nfree, (long) cural, (long) totfree, (long) maxfree);
    
    //释放buff
    brel((void *) ptr2);
    
    //查看释放buff之后的状态
    bstats(&cural, &totfree, &maxfree, &nget, &nfree);
    printf("info: %ld gets, %ld releases.  %ld in use, %ld free, largest = %ld\n",
            nget, nfree, (long) cural, (long) totfree, (long) maxfree);
    
    return 0;
}