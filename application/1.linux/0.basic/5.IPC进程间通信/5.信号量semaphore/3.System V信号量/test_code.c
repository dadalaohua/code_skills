#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <fcntl.h>
 
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
可以使用ipcs命令时，查看消息队列、共享内存以及信号量相关的信息

使用ipcrm -s semid命令释放指定id的信号量资源
例如：ipcrm -s 98305
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

static int sem_id = 0;

/************************************************************************/
/*                                                                      */
/************************************************************************/
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

static int set_semvalue(void)
{
    // 用于初始化信号量，在使用信号量前必须这样做
    union semun sem_union;
 
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        return 0;
    }
    return 1;
}
 
static void del_semvalue(void)
{
    // 删除信号量
    union semun sem_union;
 
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        fprintf(stderr, "Failed to delete semaphore\n");
    }
}
 
static int semaphore_p(void)
{
    // 对信号量做减1操作，即等待P（sv）
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;//P()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_p failed\n");
        return 0;
    }
 
    return 1;
}
 
static int semaphore_v(void)
{
    // 这是一个释放操作，它使信号量变为可用，即发送信号V（sv）
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; // V()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_v failed\n");
        return 0;
    }
 
    return 1;
}
 
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char message = 'X';
    int i = 0;
    
    key_t key = ftok(argv[0], 0x6666); //获取key值
    if (key < 0) {
        perror("ftok");
        return 1;
    }
 
    // 创建信号量
    sem_id = semget(key, 1, 0666 | IPC_CREAT);
 
    if (argc > 1)
    {
        // 程序第一次被调用，初始化信号量
        if (!set_semvalue())
        {
            fprintf(stderr, "Failed to initialize semaphore\n");
            exit(EXIT_FAILURE);
        }
 
        // 设置要输出到屏幕中的信息，即其参数的第一个字符
        message = argv[1][0];
        sleep(2);
    }
 
    for (i = 0; i < 10; ++i)
    {
        // 进入临界区
        if (!semaphore_p())
        {
            exit(EXIT_FAILURE);
        }
 
        // 向屏幕中输出数据
        printf("%c", message);
 
        // 清理缓冲区，然后休眠随机时间
        fflush(stdout);
        sleep(rand() % 3);
 
        // 离开临界区前再一次向屏幕输出数据
        printf("%c", message);
        fflush(stdout);
 
        // 离开临界区，休眠随机时间后继续循环
        if (!semaphore_v())
        {
            exit(EXIT_FAILURE);
        }
        sleep(rand() % 2);
    }
 
    sleep(10);
    printf("\n%d - finished\n", getpid());
 
    if (argc > 1)
    {
        // 如果程序是第一次被调用，则在退出前删除信号量
        sleep(3);
        del_semvalue();
    }
    exit(EXIT_SUCCESS);

    return 0;
}
