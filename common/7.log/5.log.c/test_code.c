#include "log.h"
#include <pthread.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
static const char *test_level_strings[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static void test_callback(log_Event *ev) {
    char buf[64];
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
    fprintf(
        ev->udata, "%s %-5s %s:%d: ",
        buf, test_level_strings[ev->level], ev->file, ev->line);
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

void test_log_lock(bool lock, void *udata) {
    if(lock)
        pthread_mutex_lock((pthread_mutex_t *)udata);
    else
        pthread_mutex_unlock((pthread_mutex_t *)udata);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
编译时增加-DLOG_USE_COLOR打印log会带有颜色
*/
int main(int argc, char* argv[])
{
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    printf("\n");
    
    //设置锁
    pthread_mutex_t mutex;
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    log_set_lock(test_log_lock, &mutex);
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);

    //设置安静模式，启用后不会输出任何内容
    log_set_quiet(true);
    
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    printf("\n");
    
    //设置安静模式关闭
    log_set_quiet(false);
    
    //设置当前的日志级别，只打印LOG_WARN及以上等级的log
    log_set_level(LOG_WARN);
    
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    printf("\n");
    
    //设置回调函数，只打印LOG_WARN及以上等级的log
    log_add_callback(test_callback, stdout, LOG_WARN);
    
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    printf("\n");
    
    //设置安静模式，安静模式下回调函数依然会调用
    log_set_quiet(true);
    
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    //设置安静模式关闭
    log_set_quiet(false);
    
    //将log写入文件，，只写入LOG_WARN及以上等级的log
    FILE *fp = fopen("test.log", "w");
    log_add_fp(fp, LOG_WARN);
    
    log_trace("hello %s %d", "world", 666);
    log_debug("hello %s %d", "world", 666);
    log_info("hello %s %d", "world", 666);
    log_warn("hello %s %d", "world", 666);
    log_error("hello %s %d", "world", 666);
    log_fatal("hello %s %d", "world", 666);
    
    
    //释放互斥锁
    pthread_mutex_destroy(&mutex);
    
    return 0;
}