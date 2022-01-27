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

#ifndef _EFSM_H__
#define _EFSM_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "uthash.h"
#include "pthread.h"
#include "efsm_conf.h"

/************************** Debug Config Start **************************/
#ifdef DEBUG_ENABLE

  #if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L

    #ifdef EFSM_PRINT
      #define EFSM_PRINT_INL(...) EFSM_PRINT(__VA_ARGS__)
    #else
      #define EFSM_PRINT_INL(...) printf(__VA_ARGS__)
    #endif

  #else

    #ifdef EFSM_PRINT
      #define EFSM_PRINT_INL(format, args...) EFSM_PRINT(format, ##args)
    #else
      #define EFSM_PRINT_INL(format, args...) printf(format, ##args)
    #endif
  #endif

#else

  #if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
    #define EFSM_PRINT_INL(...)
  #else
    #define EFSM_PRINT_INL(format, args...)
  #endif

#endif
/************************** Debug Config End **************************/

#ifndef bool
typedef enum{false, true} bool;
#define bool bool
#endif

typedef int EFSM_EVENT_TYPE;
typedef void (*EFSM_EVENT_HANDLER)(EFSM_EVENT_TYPE event, void *arg);
typedef struct {
    EFSM_EVENT_TYPE event;
    EFSM_EVENT_HANDLER handler;
    UT_hash_handle hh;
}EFSM_NODE;
typedef EFSM_NODE  EFSM_NODE_SETS;
typedef EFSM_NODE* EFSM_NODE_HEAD;

static inline EFSM_NODE *EFSM_NODE_FIND(EFSM_NODE_HEAD head, EFSM_EVENT_TYPE event)
{
    EFSM_NODE *node = NULL;
    if(NULL == head) return NULL;
    HASH_FIND_INT(head, &event, node);
    return node;
}

static inline EFSM_NODE_HEAD EFSM_NODE_LOAD(EFSM_NODE_SETS sets[], int num)
{
    int i = 0;
    EFSM_NODE *tmp = NULL;
    EFSM_NODE_HEAD head = NULL;
    if(NULL == sets) return NULL;
    for(; i < num; i++)
    {
        HASH_FIND_INT(head, &sets[i].event, tmp);
        if(NULL != tmp)
            tmp->handler = sets[i].handler;
        else
            HASH_ADD_INT(head, event, &sets[i]);
    }
    return head;
}
#define EFSM_LOAD(sets)  EFSM_NODE_LOAD(sets, sizeof(sets)/sizeof(EFSM_NODE))

typedef struct {
    char *_name;
    EFSM_NODE_HEAD _head;
    pthread_mutex_t _mutex;
}EFSM_OBJECT;

#define EFSM_NAME(name)  efsm_state_##name._name
#define EFSM_HEAD(name)  efsm_state_##name._head
#define EFSM_MUTEX(name) efsm_state_##name._mutex
#define EFSM_OBJECT_NAME(name)  efsm_state_##name

typedef struct {
	char *_name;
	EFSM_OBJECT *_current;
	pthread_rwlock_t _rwlock;
}EFSM_PTR_OBJECT;

/************************** API Interface **************************/
typedef EFSM_NODE EFSM_SETS;

#define EFSM_CREATE(state)  \
        EFSM_OBJECT efsm_state_##state = {#state, NULL, PTHREAD_MUTEX_INITIALIZER}

#define EFSM_DECLEAR(state) \
        extern EFSM_OBJECT efsm_state_##state

#define EFSM_BIND(state, sets) do { \
        efsm_state_##state._head = EFSM_LOAD(sets); \
    } while (0)

#define EFSM_PTR_CREATE(name) \
        EFSM_PTR_OBJECT efsm_ptr_##name = {#name, NULL, PTHREAD_RWLOCK_INITIALIZER}
#define EFSM_PTR_DECLEAR(name) \
        extern EFSM_PTR_OBJECT efsm_ptr_##name
#define EFSM_PTR_BIND(name, state) do { \
                efsm_ptr_##name._current = &efsm_state_##state; \
                pthread_mutex_lock(&efsm_ptr_##name._current->_mutex); \
            } while (0)

#define EFSM_TRANSFER_ENABLE(name)  \
        pthread_mutex_unlock(&efsm_ptr_##name._current->_mutex)
#define EFSM_TRANSFER_DISABLE(name) \
        pthread_mutex_lock(&efsm_ptr_##name._current->_mutex)
#define EFSM_TRANSFER(name, state) do { \
        char *old_state = efsm_ptr_##name._current->_name; \
        if(NULL == efsm_ptr_##name._current) \
        { \
            EFSM_PRINT_INL("EFSM-Error: cur-state-ptr have't bind a state: %s!!!\n", efsm_ptr_##name._name); \
            break; \
        } \
        if(0 == pthread_mutex_trylock(&efsm_ptr_##name._current->_mutex)) \
        { \
            pthread_mutex_unlock(&efsm_ptr_##name._current->_mutex); \
            pthread_rwlock_wrlock(&efsm_ptr_##name._rwlock); \
            efsm_ptr_##name._current = &efsm_state_##state; \
            pthread_rwlock_unlock(&efsm_ptr_##name._rwlock); \
            EFSM_PRINT_INL("EFSM-Info: '%s' switch to '%s' OK.\n", old_state, EFSM_NAME(state)); \
        } \
        else \
        { \
            EFSM_PRINT_INL("EFSM-Error: '%s' switch to '%s' failed!!!\n", old_state, EFSM_NAME(state)); \
        } \
    } while (0)

static inline EFSM_EVENT_HANDLER EFSM_HANDLER_INL(char *name, EFSM_OBJECT *efsm_ptr, pthread_rwlock_t *_rwlock, EFSM_EVENT_TYPE event)
{
    EFSM_NODE *node = NULL;
    if(NULL == efsm_ptr)
    {
        EFSM_PRINT_INL("EFSM-Error: cur-state-ptr have't bind a state: %s!!!\n", name);
        return NULL;
    }
    pthread_rwlock_rdlock(_rwlock);
    node = EFSM_NODE_FIND(efsm_ptr->_head, event);
    pthread_rwlock_unlock(_rwlock);
    if(NULL != node)
        return node->handler;
    return NULL;
}

#define EFSM_HANDLER(name, event)  \
    EFSM_HANDLER_INL(efsm_ptr_##name._name, efsm_ptr_##name._current, &efsm_ptr_##name._rwlock, event)

#ifdef __cplusplus
}
#endif

#endif  // _EFSM_H__
