#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://blog.csdn.net/chenlong_cxy/article/details/121184624

/*
可以使用ipcs命令时，查看消息队列、共享内存以及信号量相关的信息

使用ipcrm -m shmid命令释放指定id的共享内存资源
例如：ipcrm -m 98305
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PATHNAME    "../README.md"  //路径名
#define PROJ_ID     0x6666          //整数标识符
#define SIZE        4096            //共享内存的大小

int main(int argc, char* argv[])
{
    key_t key = ftok(PATHNAME, PROJ_ID); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }

    int shm = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666); //创建新的共享内存
    if (shm < 0) {
        perror("shmget");
        return 2;
    }
    
    printf("key: %x\n", key); //打印key值
    printf("shm: %d\n", shm); //打印共享内存用户层id

    char* mem = shmat(shm, NULL, 0); //关联共享内存

    while (1) {
        printf("client: %s\n", mem);    //每隔1s打印一次
        if((strlen(mem) > 0) && (mem[strlen(mem) - 1] == 'Z'))
            break;
        sleep(1);
    }

    shmdt(mem); //共享内存去关联

    shmctl(shm, IPC_RMID, NULL); //释放共享内存

    return 0;
}