#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      //包含errno所需要的头文件 
#include <string.h>     //包含strerror所需要的头文件  
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

int main(int argc, char* argv[])
{ 
    struct mq_attr attr; 
    struct mq_attr mqAttr;
    mqd_t mqID;
    
    if(argc < 3)
    {
        attr.mq_maxmsg  = 10;
        attr.mq_msgsize = 8192;
    }
    else
    {
        attr.mq_maxmsg  = atoi(argv[1]);
        attr.mq_msgsize = atoi(argv[2]);
    }
    
    mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT | O_EXCL, 0666, &attr);  

    if (mqID < 0)
    {
        if (errno == EEXIST)
        {  
            mq_unlink("/anonymQueue");
            mqID = mq_open("/anonymQueue", O_RDWR | O_CREAT, 0666, &attr);
            
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
    
    
    if(mq_getattr(mqID, &mqAttr) < 0)
    {
        printf("get the message queue attribute error %s \n", strerror(errno));
        
        return -1;  
    }
        
    printf("mq_flags:   %ld \n", mqAttr.mq_flags);
    printf("mq_maxmsg:  %ld \n", mqAttr.mq_maxmsg);
    printf("mq_msgsize: %ld \n", mqAttr.mq_msgsize);
    printf("mq_curmsgs: %ld \n", mqAttr.mq_curmsgs);

    return 0;
}