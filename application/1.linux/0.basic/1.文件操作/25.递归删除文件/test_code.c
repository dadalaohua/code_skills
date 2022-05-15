#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int del_dir_r(char *path) {
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
                del_dir_r(tmp_name);  //递归读取
            }
        } else { //不为目录则打印文件路径名
            printf("%s\n",tmp_name);
            remove(tmp_name);
        }
    }
    closedir(dp);
    
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    del_dir_r("./testdel");
    return 0;
}