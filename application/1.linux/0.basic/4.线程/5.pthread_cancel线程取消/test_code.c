#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  

// 子线程的处理代码
void* test_thread(void* arg)
{
    int i;
    
    sleep(1);
    
    // 这个函数会调用系统函数, 因此这是个间接的系统调用
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

    // 杀死子线程, 如果子线程中做系统调用, 子线程就结束了
    pthread_cancel(tid);
    
    printf("cancel end\n");
    
    pthread_join(tid, NULL);
    
    // 让主线程自己退出即可
    pthread_exit(NULL);

    return 0;  
}
