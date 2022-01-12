#include <stdio.h>
#include <unistd.h>

#include "cevent.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
int test0 = 10;
int test1 = 20;
int test2 = 500;
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_0(size_t param)
{
    printf("test_task_handle_0 %d\n", *(int *)param);
}
CEVENT_EXPORT(0, test_task_handle_0, (void *)&test0);

void test_task_init_0(void)
{
    printf("test_task_init 0\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_1(size_t param)
{
    printf("test_task_handle_1 %d\n", *(int *)param);
}
CEVENT_EXPORT(1, test_task_handle_1, (void *)&test1);

void test_task_init_1(void)
{
    printf("test_task_init 1\n");  
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_2(size_t param1, size_t param2)
{
    printf("test_task_handle_2 %d %d\n", *(int *)param1, *(int *)param2);
}
CEVENT_EXPORT(2, test_task_handle_2, (void *)&test1, (void *)&test2);

void test_task_init_2(void)
{
    printf("test_task_init 2\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_3(size_t param1, size_t param2, size_t param3)
{
    printf("test_task_handle_3 %d %d %d\n", *(int *)param1, *(int *)param2, *(int *)param3);
}
CEVENT_EXPORT(3, test_task_handle_3, (void *)&test0, (void *)&test1, (void *)&test2);

void test_task_init_3(void)
{
    printf("test_task_init 3\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_4(void)
{
    printf("test_task_handle_4\n");
}
CEVENT_EXPORT(4, test_task_handle_4);

void test_task_init_4(void)
{
    printf("test_task_init 4\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    ceventInit();
    test_task_init_0();
    test_task_init_1();
    test_task_init_2();
    
    ceventPost(0);
    ceventPost(3);
    ceventPost(4);
    while (1)
    {
        ceventPost(1);
        sleep(1);
        ceventPost(2);
        sleep(1);
    }
    
    return 0;
}