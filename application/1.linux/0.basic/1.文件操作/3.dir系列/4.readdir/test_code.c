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
readdir函数

struct dirent *readdir(DIR *dirp);
*/

/***************************************************
** description：
** parameter：
        ** *dirp opendir成功后返回的DIR值
 ** return：成功：返回一个指向 dirent 结构的指针，该结构表示 dirp 指向的目录流中的下一个目录条目 ， 
            失败或结束：NULL
        ** struct dirent {
            ino_t          d_ino;       //文件对应的inode编号, 定位文件存储在磁盘的那个数据块上 
            off_t          d_off;       // 文件在当前目录中的偏移量 
            unsigned short d_reclen;    // 文件名字的实际长度 
            unsigned char  d_type;      // 文件的类型, linux中有7中文件类型 
            char           d_name[256]; // 文件的名字 
        };

//d_type值：
        DT_BLK：块设备文件
        DT_CHR：字符设备文件
        DT_DIR：目录文件
        DT_FIFO ：管道文件
        DT_LNK：符号链接
        DT_REG ：普通文件
        DT_SOCK：UNIX域套接字文件
        DT_UNKNOWN：无法识别的文件类型

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