#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/

//#include <unistd.h> --> 使用access函数获取文件状态，成功则存在，否则不存在
//#include <sys/stat.h> --> 使用stat函数获取文件状态，成功则存在，否则不存在

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char* filename = "./hello";
    char* filename2 = "./world";
    char* filename3 = "./README.md";
    //access函数用来判断指定的文件或目录是否存在(F_OK)，已存在的文件或目录是否有可读(R_OK)、可写(W_OK)、可执行(X_OK)权限。
    //F_OK、R_OK、W_OK、X_OK这四种方式通过access函数中的第二个参数mode指定。如果指定的方式有效，则此函数返回0，否则返回-1。
    if(access(filename, F_OK ) != -1) {
        printf("%s File exists\n", filename);
    } else {
        printf("%s File inexistence\n", filename);
    }
    
    if(access(filename2, F_OK ) != -1) {
        printf("%s File exists\n", filename2);
    } else {
        printf("%s File inexistence\n", filename2);
    }
    
    if(access(filename3, F_OK ) != -1) {
        printf("%s File exists\n", filename3);
    } else {
        printf("%s File inexistence\n", filename3);
    }
    
    /*
        定义函数:    int stat(const char *file_name, struct stat *buf);
        函数说明:    通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
        返回值:      执行成功则返回0，失败返回-1，错误代码存于errno
        
        struct stat {
            dev_t         st_dev;       //文件的设备编号
            ino_t         st_ino;       //节点
            mode_t        st_mode;      //文件的类型和存取的权限
            nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
            uid_t         st_uid;       //用户ID
            gid_t         st_gid;       //组ID
            dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
            off_t         st_size;      //文件字节数(文件大小)
            unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
            unsigned long st_blocks;    //块数
            time_t        st_atime;     //最后一次访问时间
            time_t        st_mtime;     //最后一次修改时间
            time_t        st_ctime;     //最后一次改变时间(指属性)
        };
    */
    struct stat buffer;
    
    if(stat(filename, &buffer) == 0) {
        printf("%s File exists, file size = %d\n", filename, buffer.st_size);
    } else {
        printf("%s File inexistence\n", filename);
    }
    
    if(stat(filename2, &buffer) == 0) {
        printf("%s File exists, file size = %d\n", filename2, buffer.st_size);
    } else {
        printf("%s File inexistence\n", filename2);
    }
    
    if(stat(filename3, &buffer) == 0) {
        printf("%s File exists, file size = %d\n", filename3, buffer.st_size);
    } else {
        printf("%s File inexistence\n", filename3);
    }
    
    return 0;
}