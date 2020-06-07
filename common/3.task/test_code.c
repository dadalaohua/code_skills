#include <stdio.h>

#include "task.h"
#include "test_task.h"

int main(int argc, char* argv[])
{  
    task_init();
    test_task_1_init();
    test_task_2_init();

    for(;;){
        usleep(1000);
        task_timer();   //invoke this function per 1ms
        
        task_poll();
    }

    return 0;
}