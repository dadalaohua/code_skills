#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  
/*线程一*/  
void thread_1(void* argc)  
{  
    int i;  
    
    for(i = 0; i < 6; i++)  
    {  
        printf("This is a pthread_1.\n"); 
        
        if(i == 2)  
            pthread_exit(0);  
        
        sleep(1);  
    }  
}  
  
/*线程二*/  
void thread_2(void* argc)  
{  
    int i;  
    
    for(i = 0; i < 3;i++)  
        printf("This is a pthread_2.\n");  
    
    pthread_exit(0);  
}  
  
int main(int argc, char* argv[])
{  
    pthread_t id_1, id_2; 
    int ret; 
    
/*创建线程一*/  
    ret = pthread_create(&id_1, NULL, (void  *)thread_1, NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }
    
/*创建线程二*/  
    ret = pthread_create(&id_2, NULL, (void  *)thread_2, NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }
    
/*等待线程结束, 进行资源的回收*/ 
    pthread_join(id_1,NULL);  
    pthread_join(id_2,NULL); 
    
    return 0;  
}  
