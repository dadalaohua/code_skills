#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{ 
    int pid1,pid2;
    int Cpid1,Cpid2=-1;
    int fd[2];//0为读出段,1为写入端
    char outpipe1[100],inpipe[200],outpipe2[100];
    void *shm = NULL;
    sem_t *shared;

    int shmid = shmget((key_t)(1234), sizeof(sem_t *), 0666 | IPC_CREAT);//创建一个共享内存，返回一个标识符

    if(shmid == -1)
    {
        perror("shmat :");

        exit(0);
    }

    shm = shmat(shmid, 0, 0);//返回指向共享内存第一个字节的指针
    shared = (sem_t *)shm;
    
    sem_init(shared, 1, 0);//初始化共享内存信号量值为0
    pipe(fd);//建立一个无名管道

    pid1 = fork();
    if(pid1<0)
    {
        printf("error in the first fork!");
    }
    else if(pid1==0)
    {               //子进程1
        Cpid1 = getpid();
        close(fd[0]);//关掉读出端
        
        lockf(fd[1], 1, 0);//上锁,则锁定从当前偏移量到文件结尾的区域
        sprintf(outpipe1, "Child process 1 is sending a message!\n");
        write(fd[1], outpipe1, strlen(outpipe1));
        lockf(fd[1], 0, 0);//解锁
        sem_post(shared);

        exit(0);
    }
    else
    {
        pid2 = fork();
        if(pid2<0)
        {
            printf("error in the second fork!\n");
        }
        else if(pid2==0)
        {
            sem_wait(shared);
            Cpid2 = getpid();
            close(fd[0]);

            lockf(fd[1], 1, 0);
            sprintf(outpipe2, "Child process 2 is sending a message!\n");
            write(fd[1], outpipe2, strlen(outpipe2));
            lockf(fd[1], 0, 0);//解锁

            exit(0);
        }

        if(pid1 > 0 && pid2 >0)
        {
            waitpid(pid2, NULL, 0);//同步,保证子进程先写父进程再读
            close(fd[1]);//关掉写端
            read(fd[0], inpipe, 200);
            printf("%s\n", inpipe);

            exit(0);
        }
    }

    return 0;
}