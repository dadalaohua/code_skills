#ifndef __TASK_H__
#define __TASK_H__

#include "list.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define XTASK_GROUP_BASE  0
#define XTASK_GROUP_LOOP  (XTASK_GROUP_BASE+0)
#define XTASK_GROUP_1MS   (XTASK_GROUP_BASE+1)
#define XTASK_GROUP_5MS   (XTASK_GROUP_BASE+2)
#define XTASK_GROUP_10MS  (XTASK_GROUP_BASE+3)
#define XTASK_GROUP_50MS  (XTASK_GROUP_BASE+4)
#define XTASK_GROUP_100MS (XTASK_GROUP_BASE+5)
#define XTASK_GROUP_500MS (XTASK_GROUP_BASE+6)
#define XTASK_GROUP_1S    (XTASK_GROUP_BASE+7)

#define XTASK_GROUP_MAX   (XTASK_GROUP_BASE+8)

#define XTASK_SCH_ONESH 1

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef int(*task_cb) (void *priv);

typedef struct task_api
{
    /* list node */
    struct list_head       node;
    unsigned short         tid;
#define XTASK_FLAG_RUNNING 0
#define XTASK_FLAG_ONESH   1
#define XTASK_FLAG_RESULT  2

    volatile unsigned int task_flag;
    task_cb               poll;
    void                   *priv;
} task_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
int     task_init(void);
void    task_poll(void);
void    task_timer(void);
int     task_sch(task_t*task, int task_group, int sch_type);
int     task_create(task_t *task, task_cb poll, void*priv);
void    task_destroy(task_t *task);
int     task_free(task_t *t);
int     task_alloc(task_t **t);
#endif /* __TASK_H__ */
