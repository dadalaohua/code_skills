#include <stdio.h>
#include <string.h>
#include <time.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "log_general.h"

#define TAG   "TEST"

int log_timestamp(void)
{
    time_t t;
    time(&t);
    return t;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test(void)
{
    LOGE(TAG, "test %s %d", "function", 233);
    LOGE(TAG, "test");
}

int main(int argc, char* argv[])
{
    LOGE(TAG, "hello %s %d", "world", 666);
    LOGE(TAG, "hello");
    LOGW(TAG, "hello %s %d", "world", 666);
    LOGW(TAG, "hello");
    LOGI(TAG, "hello %s %d", "world", 666);
    LOGI(TAG, "hello");
    LOGD(TAG, "hello %s %d", "world", 666);
    LOGD(TAG, "hello");
    LOGV(TAG, "hello %s %d", "world", 666);
    LOGV(TAG, "hello");
    
    test();
    
    return 0;
}