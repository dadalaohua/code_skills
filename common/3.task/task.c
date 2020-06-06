#include "task.h"
#include "list.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
static unsigned int task_run_flag;
static struct list_head task_head[XTASK_GROUP_MAX];


#define XTASK_MAX  16

struct task_table_t
{

    unsigned char use[XTASK_MAX];
    task_t       task[XTASK_MAX];
};
struct task_table_t task_table;
struct task_table_t *this_table = &task_table;

/************************************************************************/
/*                                                                      */
/************************************************************************/
static inline void set_bit(int nr, unsigned int *flag)
{
    unsigned int mask = 1 << nr;
    *flag |= mask;
}
static inline void clear_bit(int nr, unsigned int *flag)
{
    unsigned int mask = 1 << nr;
    *flag &= ~mask;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
static unsigned short task_tid(void)
{
    static unsigned short static_tid = 0;

    return ++static_tid;
}

static int task_enqueue(task_t *task, int task_group)
{
    task_t *task_cur, *task_next;

    list_for_each_entry_safe(task_cur, task_next, &task_head[task_group], node)
    {
        if (task_cur == task)
        {
            //printf("Task already in queue!\n");
            return 0;
        }
    }

    task->tid = task_tid();
    /* new work to queue */
    list_add_tail(&task->node, &task_head[task_group]);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int task_sch(task_t*task, int task_group, int sch_type)
{
    if(task==NULL || task_group >= XTASK_GROUP_MAX || task_group < 0)
    {
        //printf("Invalid task!\n");
        return -1;
    }

    if (sch_type == XTASK_SCH_ONESH)
    {
        set_bit(XTASK_FLAG_ONESH, (unsigned int *)&task->task_flag);
    }
    task_enqueue(task, task_group);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int task_init(void)
{
    struct list_head *node;
    int i;

    task_run_flag = 0;
    for (i = XTASK_GROUP_BASE; i < XTASK_GROUP_MAX; i++)
    {
        node = &task_head[i];
        node->next = node;
        node->prev = node;
    }

    return 0;
}

void task_poll(void)
{
    task_t *task_cur, *task_next;
    int i,ret = 0;

    for (i = XTASK_GROUP_BASE; i < XTASK_GROUP_MAX; i++)
    {
        if (i == XTASK_GROUP_LOOP || (task_run_flag & (1 << i)))
        {
            clear_bit(i, &task_run_flag);
            list_for_each_entry_safe(task_cur, task_next, &task_head[i], node)
            {
                
                if(task_cur->poll)
                {
                    set_bit(XTASK_FLAG_RUNNING, (unsigned int *)&task_cur->task_flag);
                    ret  = task_cur->poll(task_cur->priv);
                    clear_bit(XTASK_FLAG_RUNNING,(unsigned int *)&task_cur->task_flag);
                }
                
                if ((task_cur->task_flag & XTASK_FLAG_ONESH)||\
                    ((task_cur->task_flag & XTASK_FLAG_RESULT)&&ret == 0))
                {
                    /* task done */
                    task_cur->task_flag = 0;
                    task_cur->tid = 0;
                    list_del(&task_cur->node);
                    
                }
            }
        }
    }
}

/************************************************************************/
/* invoke this function per 1ms                                         */
/************************************************************************/
void task_timer(void)
{
    volatile static unsigned int counter = 0;

    ++counter;

    set_bit(XTASK_GROUP_1MS, &task_run_flag);
    if (counter % 5 == 0)
        set_bit(XTASK_GROUP_5MS, &task_run_flag);
    if (counter % 10 == 0)
        set_bit(XTASK_GROUP_10MS, &task_run_flag);
    if (counter % 50 == 0)
        set_bit(XTASK_GROUP_50MS, &task_run_flag);
    if (counter % 100 == 0)
        set_bit(XTASK_GROUP_100MS, &task_run_flag);
    if (counter % 500 == 0)
        set_bit(XTASK_GROUP_500MS, &task_run_flag);
}

int task_free(task_t *t)
{
    int i;
    for(i = 0;i < XTASK_MAX;i++)
    {
        if(t == &this_table->task[i])
        {
            this_table->use[i] = 0;
            return 0;
        }
    }
    return -1;
}
int task_alloc(task_t **t)
{
    int i,ret = -1;
    
    if(this_table==NULL)
        return -1;
    
    for(i = 0;i < XTASK_MAX;i++)
    {
        if(this_table->use[i]==0)
        {
            *t = &this_table->task[i];
            this_table->use[i] = 1;
            ret = 0;
            break;
        }
    }
    return ret;
}

int task_create(task_t *task, task_cb poll, void*priv)
{
    if (task==NULL || poll==NULL)
    {
        //printf("Task create failed!\n");
        return -1;
    }

    task->poll = poll;
    task->priv = priv;

    return 0;
}

void task_destroy(task_t *task)
{
    return ;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
