#include <stdio.h>

#include "test_task.h"
#include "Task.h"

unsigned int test_task_1_count = 0;

unsigned int test_task_1_poll(void)
{
    printf("test_task_1_poll %d\n", ++test_task_1_count);
    
    return 0;
}

int test_task_1_init(void)
{
    SCH_Add_Task(test_task_1_poll, 50, 500);

    return 0;
}