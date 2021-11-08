#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{ 
    int pid1,pid2;
    sem_t *resource1; 
    sem_t *resource2; 
    int Cpid1,Cpid2=-1;
    int fd[2];//0为读出段,1为写入端
    char outpipe1[100],inpipe[200],outpipe2[100];
    pipe(fd);//建立一个无名管道

    pid1 = fork();

    if(pid1 < 0)
    {
        printf("error in the first fork!");
    }
    else if(pid1 == 0)
    {                   //子进程1
        printf("Child process 1\n");
        resource1 = sem_open("name_sem1", O_CREAT, 0666, 0);
        Cpid1 = getpid();
        close(fd[0]);  //关掉读出端
        
        lockf(fd[1], 1, 0);//上锁,则锁定从当前偏移量到文件结尾的区域
        sprintf(outpipe1, "Child process 1 is sending a message!\n");
        write(fd[1], outpipe1, strlen(outpipe1));
        lockf(fd[1], 0, 0);//解锁

        sem_post(resource1);
        sem_close(resource1);
        
        exit(0);
   }
   else
   {
        pid2 = fork();
        if(pid2 < 0)
        {
            printf("error in the second fork!\n");
        }
        else if(pid2 == 0)
        {
            printf("Child process 2\n");
            resource1=sem_open("name_sem1", O_CREAT, 0666, 0);
            resource2=sem_open("name_sem2", O_CREAT, 0666, 0);
            Cpid2 = getpid();
            sem_wait(resource1);
            close(fd[0]);
            
            lockf(fd[1], 1, 0);
            sprintf(outpipe2, "Child process 2 is sending a message!\n");
            
            write(fd[1], outpipe2, strlen(outpipe2));
            lockf(fd[1], 0, 0);//解锁
            
            sem_post(resource2);
            sem_close(resource1);
            sem_close(resource2);

            exit(0);
        }

        if(pid1 > 0 && pid2 >0)
        {
            resource2 = sem_open("name_sem2", O_CREAT, 0666, 0);
            sem_wait(resource2);
            waitpid(pid1, NULL, 0); //回收指定ID的子进程
            waitpid(pid2, NULL, 0);
            close(fd[1]);           //关掉写端
            read(fd[0], inpipe, 200);
            printf("%s\n",inpipe);
            sem_close(resource2);

            exit(0);
        }

        sem_unlink("name_sem1");
        sem_unlink("name_sem2");

    }

    return 0;
}