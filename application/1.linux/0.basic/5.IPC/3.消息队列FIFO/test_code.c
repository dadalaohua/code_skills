#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      //包含errno所需要的头文件 
#include <string.h>     //包含strerror所需要的头文件  
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

int main(int argc, char* argv[])
{ 
    mqd_t mqID;
    
    mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT | O_EXCL, 0666, NULL);  

    if (mqID < 0)
    {
        if (errno == EEXIST)
        {  
            mq_unlink("/anonymQueue");
            mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT, 0666, NULL);
            
            if (mqID < 0)
            {
                printf("open message queue error: %s \n", strerror(errno));
            
                return -1;
            }
        }
        else
        {
            printf("open message queue error: %s \n", strerror(errno));
            
            return -1;
        }
    }

    if (fork() == 0)  
    {  
        char buf[128];  
        int i;
        struct mq_attr mqAttr;
        
        if(mq_getattr(mqID, &mqAttr) < 0)
        {
            printf("get the message queue attribute error %s \n", strerror(errno));
            
            return -1;  
        }
        
        printf("mq_flags:   %ld \n", mqAttr.mq_flags);
        printf("mq_maxmsg:  %ld \n", mqAttr.mq_maxmsg);
        printf("mq_msgsize: %ld \n", mqAttr.mq_msgsize);
        printf("mq_curmsgs: %ld \n", mqAttr.mq_curmsgs);

        for (i = 1; i <= 5; i++)  
        {  
            if (mq_receive(mqID, buf, mqAttr.mq_msgsize, NULL) < 0)  
            {  
                printf("receive message failed, error info: %s \n", strerror(errno));
                
                continue;  
            }  
  
            printf("%d receive message %s\n", i, buf);
        }
        
        exit(0);  
    }
    else
    {
        char msg[] = "yuki";
        int i;
        
        for (i = 1; i <= 5; ++i)  
        {  
            if (mq_send(mqID, msg, sizeof(msg), i) < 0)  
            {  
                printf("send message failed, error info: %s \n", strerror(errno));
            }
            
            printf("%d send message successs\n", i);
                
            sleep(1);  
        }
    }

    return 0;
}