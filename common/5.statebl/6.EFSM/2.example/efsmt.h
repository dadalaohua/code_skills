/* 
 * MIT License
 *
 * Copyright (c) 2019 极简美 @ konishi5202@163.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _EFSMT_H__
#define _EFSMT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
#include "efsm.h"

typedef struct worker{
    void *arg;
    struct worker *next;
    EFSM_EVENT_TYPE event;
    EFSM_EVENT_HANDLER handler;
}EFSMTWorker;

typedef struct{
    char *_name;
    pthread_t _thread_id;
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
    EFSMTWorker *_queue_head;
    volatile int  _queue_num;
    volatile bool _exit_flag;
}EFSMT_OBJECT;

#define EFSMT_OBJECT_CREATE(name) \
        EFSMT_OBJECT efsmt_object_##name = {#name, 0, PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, NULL, 0, false}

#define EFSMT_THREAD_CREATE(name) \
        static void *efsmt_thread_##name(void *arg) \
        { \
            EFSMTWorker *worker = NULL; \
            (void)arg; /* shield warning on unused variable */ \
            /* make dynamic thread detached */ \
            pthread_detach(pthread_self()); \
            EFSM_PRINT_INL("EFSMT-Info: %s-EFSM-thread is running.\n", #name); \
            while(true) \
            { \
                pthread_mutex_lock(&efsmt_object_##name._mutex); \
                while((0 == efsmt_object_##name._queue_num) && !efsmt_object_##name._exit_flag) \
                    pthread_cond_wait(&efsmt_object_##name._cond, &efsmt_object_##name._mutex); \
                if(efsmt_object_##name._exit_flag) \
                { \
                    pthread_mutex_unlock(&efsmt_object_##name._mutex); \
                    break; \
                } \
                efsmt_object_##name._queue_num--; \
                worker = efsmt_object_##name._queue_head; \
                efsmt_object_##name._queue_head = efsmt_object_##name._queue_head->next; \
                pthread_mutex_unlock(&efsmt_object_##name._mutex); \
                assert(NULL != worker); \
                if(worker->handler) \
                    (*(worker->handler))(worker->event, worker->arg); \
                free(worker); \
                worker = NULL; \
            } \
            pthread_exit(NULL); \
        } \

extern bool efsmt_create_inl(EFSMT_OBJECT *efsmt_o, void *(*thread)(void *));
extern void efsmt_destroy_inl(EFSMT_OBJECT *efsmt_o);
extern bool efsmt_invoke_inl(EFSMT_OBJECT *efsmt_o, EFSM_EVENT_TYPE event, char *event_name, 
                                                    EFSM_EVENT_HANDLER handler, void*arg);

/************************** API Interface **************************/

#define EFSMT_CREATE(name) \
        EFSM_PTR_CREATE(name); \
        EFSMT_OBJECT_CREATE(name); \
        EFSMT_THREAD_CREATE(name)

#define EFSMT_DECLEAR(name) \
        EFSM_PTR_DECLEAR(name); \
        extern EFSMT_OBJECT efsmt_object_##name

#define EFSMT_DESTROY(name) \
        efsmt_destroy_inl(&efsmt_object_##name)

#define EFSMT_BIND(name, state) do { \
            efsmt_create_inl(&efsmt_object_##name, efsmt_thread_##name); \
            EFSM_PTR_BIND(name, state); \
        } while (0)

#define EFSMT_INVOKE(name, event, arg) \
        efsmt_invoke_inl(&efsmt_object_##name, event, #event, EFSM_HANDLER(name, event), arg)

#ifdef __cplusplus
}
#endif

#endif  // _EFSMT_H__
