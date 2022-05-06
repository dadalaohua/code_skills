#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int fd;                                     //定义整型返回值
    fd = open("./testfile", O_RDWR);            //open指令 打开可读可写testfile文件返回值
    printf("fd = %d\n", fd);
    if(fd == -1){                               //若返回值为-1  没有testfile文件
        printf("open file failed\n");
        
        //open 指令 若没有file文件 ” | O_CREAT ” 创建testfile文件 权限0600
        fd = open("./testfile" , O_RDWR | O_CREAT , 0600);
        //fd = open("./testfile" , O_RDWR | O_CREAT , S_IRUSR | S_IWUSR); //或者这样写
        if(fd > 0){
            printf("creat file success\n");
        }   
    }
    printf("fd = %d\n", fd);
    
    close(fd);
    
    
    char *buf = "Hello world";

    //O_APPEND 每次写时都加到文件的尾端
    fd = open("./testfile", O_RDWR | O_APPEND);

    printf("fd = %d \n", fd);

    int writelen = write(fd, buf, strlen(buf));

    if(writelen != -1){
        printf("write %d byte to file\n", writelen);
    }
    close(fd);
    
    //creat 等效于调用带有等于 O_CREAT|O_WRONLY|O_TRUNC 的flag的 open()。
    //S_IRWXU 用户（文件所有者）具有读、写和执行权限
    fd = creat("./testfile2", S_IRWXU);
    if(fd == -1)
        printf("creat file failed\n");
    close(fd);
    
    return 0;
}