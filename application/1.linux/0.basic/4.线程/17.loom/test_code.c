#include <stdio.h>
#include <poll.h>

#include "loom.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
static void sleep_msec(int msec) {
    poll(NULL, 0, msec);
}

static void set_flag_cb(void *env) {
    uintptr_t i = (uintptr_t)env;
    printf("set_flag_cb %zd\n", i);
}

static void set_flag_dont_cleanup_cb(void *env) {
    uintptr_t i = (uintptr_t)env;
    printf("set_flag_dont_cleanup_cb %zd\n", i);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct loom *l = NULL;
    
    loom_config cfg = {
        .init_threads = 1,
    };
    
    if(LOOM_INIT_RES_OK != loom_init(&cfg, &l)) {
        printf("loom_init != LOOM_INIT_RES_OK\n");
        return -1;
    }

    for (uintptr_t i = 0; i < 8; i++) {
        loom_task t = {
            .task_cb = set_flag_cb,
            .cleanup_cb = set_flag_dont_cleanup_cb,
            .env = (void *)i,
        };
        
        for (int i = 0; i < 100; i++) {  // 100 retries
            size_t backpressure = 0;
            if (loom_enqueue(l, &t, &backpressure)) { 
                break;
            }
            sleep_msec(backpressure / 10);

            if (i == 99) { 
                printf("queue full too long\n"); 
            }
        }
    }

    loom_info info;

    /* Give them a bit to actually work... */
    for (uintptr_t i = 0; i < 8; i++) {
        loom_get_stats(l, &info);
        /* If all tasks have been started, break */
        if (info.backlog_size == 0) {
            break;
        }
        sleep_msec(info.backlog_size);
    }

    /* Give the last task(s) still running time to finish before shutting down */
    sleep_msec(10);

    loom_get_stats(l, &info);
    if(info.backlog_size != 0) {
        printf("info.backlog_size != 0\n"); 
    }
    
    loom_free(l);

    return 0;
}