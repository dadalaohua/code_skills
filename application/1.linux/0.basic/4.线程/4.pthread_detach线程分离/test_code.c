#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  

// 子线程的处理代码
void* test_thread(void* arg)
{
    int i;
    
    printf("ID: %ld\n", pthread_self());
    for(i = 0; i < 6; ++i)
    {
        printf("i: = %d\n", i);
    }
    return NULL;
}
  
int main(int argc, char* argv[])
{  
    pthread_t tid;

    pthread_create(&tid, NULL, test_thread, NULL);
    // 设置子线程和主线程分离
    pthread_detach(tid);
    
    // 让主线程自己退出即可
    pthread_exit(NULL);

    return 0;  
}
