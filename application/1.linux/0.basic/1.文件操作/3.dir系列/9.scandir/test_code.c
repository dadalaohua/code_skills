#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dirent.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
scandir 函数

int scandir(const char *restrict dirp,
                   struct dirent ***restrict namelist,
                   int (*filter)(const struct dirent *),
                   int (*compar)(const struct dirent **,
                                 const struct dirent **));
*/

/***************************************************
** description： scandir()会扫描参数dir指定的目录文件，经由参数select指定的函数来挑选目录结构至参数namelist数组中，最后再调用
参数compar指定的函数来排序namelist 数组中的目录数据。每次从目录文件中读取一个目录结构后便将此结构传给参数select所指的
函数， select函数若不想要将此目录结构复制到namelist数组就返回0，若select为空指针则代表选择所有的目录结构。scandir()会
调用 qsort()来排序数据，参数compar则为qsort()的参数，若是要排列目录名称字母则可使用alphasort(). 结构dirent定义请参考
readdir()
** parameter：
        ** 
 ** return：成功则返回复制到namelist数组中的数据结构数目，有错误发生则返回-1
****************************************************/



/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct dirent **namelist;
    int n;
    n = scandir("./hello", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        while(n--)
        {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
    
    return 0;
}