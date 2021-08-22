#ifndef _WORK_H_
#define _WORK_H_

#include "list.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef int(*work_cb) (void *priv);

typedef struct{

    /* list node */
    struct list_head       node;
    work_cb               poll;
    void                  *priv;
    
}work_t;

int work_sch(work_t*work);
int work_init(void);
void work_poll(void);
int work_create(work_t *work, work_cb cb, void*priv);
int work_destory(work_t *work);

#endif
