#include <stdio.h>

#include "test_task.h"
#include "timeslice.h"

TimesilceTaskObj task_2;
unsigned int test_task_2_count = 0;

void test_task_2_poll(void)
{
    printf("test_task_2_poll %d\n", ++test_task_2_count);
}

int test_task_2_init(void)
{
    timeslice_task_init(&task_2, test_task_2_poll, 2, 2000);
    timeslice_task_add(&task_2);

    return 0;
}