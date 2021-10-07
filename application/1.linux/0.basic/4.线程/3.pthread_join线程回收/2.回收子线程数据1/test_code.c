#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  
// 定义结构
struct teststruct
{
    int id;
    char buff[36];
};

struct teststruct gtest;   // 定义全局变量

// 子线程的处理代码
void* test_thread(void* arg)
{
    int i;
    
    printf("ID: %ld\n", pthread_self());
    for(i = 0; i < 100; ++i)
    {
        printf("i: = %d\n", i);
        if(i == 6)
        {
            gtest.id = 666;
            strcpy(gtest.buff, "hello world");
            // 该函数的参数将这个地址传递给了主线程的pthread_join()
            pthread_exit(&gtest);
        }
    }
    return NULL;
}
  
int main(int argc, char* argv[])
{  
    pthread_t tid;
    void* ptr = NULL;
    struct teststruct* testval;
    
    pthread_create(&tid, NULL, test_thread, NULL);

    // 阻塞等待子线程退出
    // ptr是一个传出参数, 在函数内部让这个指针指向一块有效内存
    // 这个内存地址就是pthread_exit() 参数指向的内存
    pthread_join(tid, &ptr);
    testval = (struct teststruct*)ptr;
    printf("id: %d buff: %s, \n", testval->id, testval->buff);
    
    return 0;  
}
