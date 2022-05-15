#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
seekdir 函数

void seekdir(DIR *dirp, long loc);
*/

/***************************************************
** description：seekdir()设置了目录流中的位置，下一次 readdir 调用将从这个位置开始。 
                loc 参数应该是先前调用 telldir 所返回的值
** parameter：
        ** *dirp
 ** return：不返回任何值
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
    int cnt = 0, flagoffset;
    while((read_dir = readdir(dir)) != NULL) {
        
        offset = telldir(dir);
        printf("d_name:%s offset %d\n", read_dir->d_name, offset);
        
        cnt++;
        if(cnt == 3)
            flagoffset = offset;
    }
    
    seekdir(dir, flagoffset);
    read_dir = readdir(dir);
    printf("d_name:%s\n", read_dir->d_name);
    
    closedir(dir);
    
    return 0;
}