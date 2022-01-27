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

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "efsmt.h"

bool efsmt_create_inl(EFSMT_OBJECT *efsmt_o, void *(*thread)(void *))
{
    size_t stack_size = 0;
    pthread_attr_t thread_attr;

    stack_size = EFSM_THREAD_STACK_SIZE*1024;
    if(pthread_attr_init(&thread_attr) != 0)
        return false;
    if(pthread_attr_setstacksize(&thread_attr, stack_size) != 0)
        return false;

    if(pthread_create(&efsmt_o->_thread_id, &thread_attr, thread, NULL) != 0)
    {
        EFSM_PRINT_INL("EFSMT-Error: %s pthread_create failed, errno:%d,error:%s!!!\n", efsmt_o->_name, errno, strerror(errno));
        return false;
    }

    return true;
}

void efsmt_destroy_inl(EFSMT_OBJECT *efsmt_o)
{
    EFSMTWorker *worker = NULL;
    
    if(efsmt_o->_exit_flag)
        return ;
    efsmt_o->_exit_flag = true;
    usleep(5*1000);
    
    pthread_mutex_lock(&efsmt_o->_mutex);
    pthread_cond_broadcast(&efsmt_o->_cond);
    pthread_mutex_unlock(&efsmt_o->_mutex);

    pthread_join(efsmt_o->_thread_id, NULL);
    while(NULL != efsmt_o->_queue_head)
    {
        worker = efsmt_o->_queue_head;
        efsmt_o->_queue_head = efsmt_o->_queue_head->next;
        free(worker);
    }    
}

bool efsmt_invoke_inl(EFSMT_OBJECT *efsmt_o, EFSM_EVENT_TYPE event, char *event_name, 
                                          EFSM_EVENT_HANDLER handler, void*arg)
{
    EFSMTWorker *node = NULL;
    EFSMTWorker *worker = NULL;

    if(NULL == handler)
    {
        EFSM_PRINT_INL("EFSMT-Info: %s dones't have handler on %s-state.\n", event_name, efsmt_o->_name);
        return true;
    }

    if(efsmt_o->_queue_num >= EFSM_THREAD_QUEUE_SIZE)
    {
        EFSM_PRINT_INL("EFSMT-Warn: %s queue size is to large:%d!!!\n", efsmt_o->_name, efsmt_o->_queue_num);
        return false;
    }

    worker = (EFSMTWorker *)malloc(sizeof(EFSMTWorker));
    if(NULL == worker)
    {
        EFSM_PRINT_INL("EFSMT-Warn: malloc memory for worker failed!!!\n");
        return false;
    }

    worker->arg = arg;
    worker->event = event;
    worker->handler = handler;
    worker->next = NULL;

    pthread_mutex_lock(&efsmt_o->_mutex);
    if(NULL == efsmt_o->_queue_head)
    {
        efsmt_o->_queue_head = worker;
    }
    else
    {
        node = efsmt_o->_queue_head;
        while(NULL != node->next)
            node = node->next;
        node->next = worker;
    }
    efsmt_o->_queue_num++;
    pthread_cond_signal(&efsmt_o->_cond);
    pthread_mutex_unlock(&efsmt_o->_mutex);

    return true;
}

