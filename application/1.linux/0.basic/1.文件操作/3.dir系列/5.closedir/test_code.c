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
closedir 函数

int closedir(DIR *dirp);
*/

/***************************************************
** description：关闭由opendir打开的目录
** parameter：
        ** *dirp：调用opendir成功后返回的DIR信息地址
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