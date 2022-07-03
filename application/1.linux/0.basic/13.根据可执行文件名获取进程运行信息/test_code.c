#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc_info.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    PROCESS_INFO table={0};
    strcpy(table.proc_name, "test_code"); //监控的进程名
    sys_proc_info_init( &table, 1); //系统监控初始化
    while(1)
    {
        sleep(1);
        printf("-----------------------\n");
        printf("proc_name = %s\n",table.proc_name);
        printf("state = %d\n",table.state);
        printf("thread_num = %d\n",table.thread_num);
        printf("pid = %d\n",table.pid);
        printf("rss = %ld kB\n",table.rss); //cat /proc/<PID>/stat
        printf("vss = %ld kB\n",table.vss); //cat /proc/<PID>/stat
        printf("cpu = %.2lf\n",table.cpu);
        printf("reset_times = %d\n\n",table.reset_times);
    }

    sys_proc_info_uninit();
    return 0;
}