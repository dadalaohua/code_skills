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
    pthread_t mytid;

    printf("main ID: %ld\n", pthread_self());
    
    pthread_create(&tid, NULL, test_thread, NULL);
    
    mytid = pthread_self();
    
    //如果两个线程 ID 相等返回非 0 值，如果不相等返回 0
    printf("equal: %d\n", pthread_equal(mytid, tid));
    
    pthread_join(tid, NULL);

    return 0;  
}
