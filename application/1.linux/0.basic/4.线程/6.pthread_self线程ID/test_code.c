#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  

// 子线程的处理代码
void* test_thread(void* arg)
{
    printf("pthread ID: %ld\n", pthread_self());
    
    sleep(1);
    
    return NULL;
}
  
int main(int argc, char* argv[])
{  
    pthread_t tid;

    printf("main ID: %ld\n", pthread_self());
    
    pthread_create(&tid, NULL, test_thread, NULL);
    
    pthread_join(tid, NULL);

    return 0;  
}
