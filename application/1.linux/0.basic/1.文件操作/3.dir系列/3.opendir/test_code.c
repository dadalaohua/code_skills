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
opendir函数

DIR *opendir(const char *pathname);
*/

/***************************************************
** description：打开指定目录
** parameter：
        ** pathname：需要被打开的目录名字
 ** return：成功：一个指向目录流的指针地址（DIR *）， 失败：NULL，并设置 errno 以指示错误。
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
        printf("\r\n********************************************\n");
        printf("d_ino:%ld\n", read_dir->d_ino);
        printf("d_off:%ld\n", read_dir->d_off);
        printf("d_reclen:%d\n", read_dir->d_reclen);
        printf("d_type:%d\n", read_dir->d_type);
        printf("d_name:%s\n", read_dir->d_name);
        printf("********************************************\r\n");
    }
    closedir(dir);
    
    return 0;
}