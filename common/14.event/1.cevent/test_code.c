#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cevent.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_task_handle_0(unsigned int param);
void test_task_handle_1(unsigned int param);
void test_task_handle_2(unsigned int param1, unsigned int param2);
/************************************************************************/
/*                                                                      */
/************************************************************************/
CEVENT_EXPORT(0, test_task_handle_0);

void test_task_handle_0(unsigned int param)
{
    printf("test_task_handle_0 %d\n", param);
}

void test_task_init_0(void)
{
    printf("test_task_init 0\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEVENT_EXPORT(1, test_task_handle_1);

void test_task_handle_1(unsigned int param)
{
    printf("test_task_handle_1 %d\n", param);
}

void test_task_init_1(void)
{
    printf("test_task_init 1\n");  
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEVENT_EXPORT(2, test_task_handle_2);

void test_task_handle_2(unsigned int param1, unsigned int param2)
{
    printf("test_task_handle_2 %d %d\n", param1, param2);
}

void test_task_init_2(void)
{
    printf("test_task_init 2\n");
    
    
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
    
    while (1)
    {
        ceventPost(1);
        sleep(1);
        ceventPost(2);
        sleep(1);
    }
    
    return 0;
}