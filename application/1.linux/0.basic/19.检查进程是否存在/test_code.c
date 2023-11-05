#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROCESS_NAME    "bash"   //要监控的进程

int check_app(void)
{
    FILE* fp;
    int count;
    char buf[512];
    char command[512];
    
    sprintf(command, "ps -ef | grep "PROCESS_NAME" | grep -v grep | wc -l" );
    
    if((fp = popen(command, "r")) == NULL) {
        return 0;
    }
    
    if( (fgets(buf, sizeof(buf), fp))!= NULL ) {
        count = atoi(buf);
        
        if(count == 0)
            printf("进程不存在!\n");
        else
            printf("进程已找到，有%d个!\n",count);
    }
    
    pclose(fp);
    
    return 0;
}

int main(int argc, char* argv[])
{
    check_app();
    
    return 0;
}
