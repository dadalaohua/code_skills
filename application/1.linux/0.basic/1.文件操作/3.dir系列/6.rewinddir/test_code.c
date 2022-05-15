#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
rewinddir 函数

void rewinddir(DIR *dirp);
*/

/***************************************************
** description：rewinddir()用来设置参数dir 目录流目前的读取位置为原来开头的读取位置.
** parameter：
        ** *dirp
 ** return：没有返回值
****************************************************/



/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    DIR* dir = opendir("./hello");
    if(dir == NULL) {
        perror("opendir:");
        return -1;
    }
    
    struct dirent *read_dir = NULL;
    while((read_dir = readdir(dir)) != NULL) {
        printf("d_name:%s\n", read_dir->d_name);
    }
    printf("\n");
    rewinddir(dir);
    while((read_dir = readdir(dir)) != NULL) {
        printf("d_name:%s\n", read_dir->d_name);
    }
    closedir(dir);
    
    return 0;
}