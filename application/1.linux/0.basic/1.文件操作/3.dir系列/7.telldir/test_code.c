#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
telldir 函数

long telldir(DIR *dirp);
*/

/***************************************************
** description：telldir()返回参数dir 目录流目前的读取位置. 此返回值代表距离目录文件开头的偏移量返回值返回下个读取位置, 有错误发生时返回-1.
** parameter：
        ** *dirp
 ** return：成功:0,失败:-1，并设置errno以指示错误。
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
     int offset;
    while((read_dir = readdir(dir)) != NULL) {
        offset = telldir(dir);
        printf("d_name:%s offset %d\n", read_dir->d_name, offset);
    }
    closedir(dir);
    
    return 0;
}