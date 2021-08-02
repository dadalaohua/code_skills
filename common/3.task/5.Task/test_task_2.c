#include <stdio.h>

#include "test_task.h"
#include "Task.h"

unsigned int test_task_2_count = 0;

unsigned int test_task_2_poll(void)
{
    printf("test_task_2_poll %d\n", ++test_task_2_count);
    
    return 0;
}

int test_task_2_init(void)
{
    SCH_Add_Task(test_task_2_poll, 10, 1000);

    return 0;
}