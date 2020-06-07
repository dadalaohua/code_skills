#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "work.h"

work_t test_work_1;
work_t test_work_2;
/************************************************************************/
/*                                                                      */
/************************************************************************/
int test_task_1(void *priv)
{
    printf("test_task_1\n");
    return 0;
}

int test_task_2(void *priv)
{
    printf("test_task_2\n");
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{  
    work_init();
    work_create(&test_work_1, test_task_1, NULL);
    work_create(&test_work_2, test_task_2, NULL);
    
    work_sch(&test_work_1);
    for(;;){    
        work_sch(&test_work_2);
        sleep(1);
        
        work_poll();
    }

    return 0;
}