#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int cp_file(const char* src_path, const char* dst_path)
{
    FILE *src_fp, *dst_fp;
    char buff[1024];
    int len;
    
    src_fp = fopen(src_path, "r");
    if(src_fp == NULL) {
        return -1;
    }
    dst_fp = fopen(dst_path, "w+");
    if(dst_fp == NULL) {
        fclose(src_fp);
        return -1;
    }
    
    while((len = fread(buff, 1, sizeof(buff), src_fp))) {
        fwrite(buff, 1, len, dst_fp);
    }
    
    fclose(src_fp);
    fclose(dst_fp);
    
    return 0;
}

int cp_dir(const char *src_path, const char* dst_path) {
    DIR *dp = NULL;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    //char tmp_name[128]={0};
    char src_file_path[1024]={0};
    char dst_file_path[1024]={0};
    int src_file_len = strlen(src_path);
    int dst_file_len = strlen(dst_path);
    
    strcpy(src_file_path, src_path);
    strcpy(dst_file_path, dst_path);
    
    dp = opendir(src_file_path);
    if(dp == NULL) {
        printf("open dir error!!\n");
        return -1;
    }
    
    mkdir(dst_file_path, 0777);
    
    while(1) {
        st = readdir(dp);
        if(NULL == st) {    //读取完毕
            break;
        }
        
        // strcpy(tmp_name, path);
        // if(path[strlen(path)-1] != '/') //判断路径名是否带/
            // strcat(tmp_name, "/");
        // strcat(tmp_name, st->d_name);  //新文件路径名
        
        sprintf(&src_file_path[src_file_len], "/%s", st->d_name);
        sprintf(&dst_file_path[dst_file_len], "/%s", st->d_name);
        
        ret = stat(src_file_path, &sta); //查看目录下文件属性
        if(ret < 0) {
            printf("read stat fail\n");
            return -1;
        }

        if(S_ISDIR(sta.st_mode)) {  //如果为目录文件
            if( 0 == strcmp("..",st->d_name) || 0 == strcmp(".",st->d_name)) //忽略当前目录和上一层目录
                continue;
            else {
                cp_dir(src_file_path, dst_file_path);  //递归复制
                printf("%s\n", src_file_path);

            }
        } else { //不为目录则打印文件路径名
            printf("%s\n",src_file_path);
            cp_file(src_file_path, dst_file_path);  //递归复制
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
    cp_dir("./testcp", "./testcp_bak");
    return 0;
}