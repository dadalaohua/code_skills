#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/statfs.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int getDiskfree(char *pDisk) {
    long long freespace = 0;
    long long totalspace = 0;
    float freeSpacePercent = 0;
    struct statfs disk_statfs;

    if( statfs(pDisk, &disk_statfs) >= 0 ){
        freespace = (((long long)disk_statfs.f_bsize * (long long)disk_statfs.f_bfree)/(long long)1024);
        totalspace = (((long long)disk_statfs.f_bsize * (long long)disk_statfs.f_blocks) /(long long)1024);
        freeSpacePercent = ((float)freespace/(float)totalspace)*100 ;
        
        printf("1K-blocks     Used Available Use%%       Free%%\n");
        printf("%lld %lld %lld  %f %f\n", totalspace, totalspace - freespace, freespace, 100 - freeSpacePercent, freeSpacePercent);
    }

    return freeSpacePercent;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //结果与命令" df / "一样
    printf("%d\n", getDiskfree("/"));
    return 0;
}