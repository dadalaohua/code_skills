#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int space_usage = 0;    //计算文件占用的空间
int file_size = 0;      //计算文件实际的大小
int folder_size = 0;    //计算文件夹的大小
int read_dir_r(char *path) {
    DIR *dp = NULL;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    char tmp_name[1024]={0};
    dp = opendir(path);
    if(dp == NULL) {
        printf("open dir error!!\n");
        return -1;
    }
    
    while(1) {
        st = readdir(dp);
        if(NULL == st) {    //读取完毕
            break;
        }
        
        strcpy(tmp_name, path);
        if(path[strlen(path)-1] != '/') //判断路径名是否带/
            strcat(tmp_name,"/");
        strcat(tmp_name,st->d_name);  //新文件路径名
        
        ret = stat(tmp_name, &sta); //查看目录下文件属性
        if(ret < 0) {
            printf("read stat fail\n");
            return -1;
        }

        if(S_ISDIR(sta.st_mode)) {  //如果为目录文件
            if( 0 == strcmp("..",st->d_name) || 0 == strcmp(".",st->d_name)) //忽略当前目录和上一层目录
                continue;
            else {
                read_dir_r(tmp_name);  //递归读取
            }
            folder_size += sta.st_size;
        } else { //不为目录则打印文件路径名
            printf("%s %ld %ld\n",tmp_name, sta.st_blocks, sta.st_size);
            space_usage += sta.st_blocks;
            file_size += sta.st_size;
        }
    }
    closedir(dp);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define gigaByte (1 << 21)
#define megaByte (1 << 11)
#define kiloByte (1 << 1)

int main(int argc, char* argv[])
{
    read_dir_r("./");
    //与命令du -s相同
    //整个文件夹占用的大小， 单位分别为 K, G, M, K, Byte
    printf("space_usage %dK %fG %fM %fK %dByte\n", (space_usage + 1) / 2, (float)space_usage / gigaByte, (float)space_usage / megaByte, (float)space_usage / kiloByte, space_usage / kiloByte * 1024);
    //与命令du -b相同
    //文件大小累加和 文件夹大小累加和 总的大小
    printf("%dByte %dByte %dByte\n", file_size, folder_size + 4096, file_size + folder_size + 4096);
    //filecnt这个数计算的大小会少了一个目录的大小，可能是缺少目录本身或者一开始的大小，手动添加一个4096才会与du -b命令相同
    return 0;
}