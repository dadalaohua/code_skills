#include "work.h"
#include "list.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
static struct list_head work_head;


/************************************************************************/
/*                                                                      */
/************************************************************************/

static int work_enqueue(work_t *work)
{
    /* new work to queue */
    list_add_tail(&work->node, &work_head);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int work_sch(work_t*work)
{
    work_t *work_cur,*work_next;
    if(work==NULL)
    {
        //printf("Invalid work!\n");
        return -1;
    }
    work_enqueue(work);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int work_init(void)
{
    struct list_head *node;
    
    node = &work_head;
    node->next = node;
    node->prev = node;

    return 0;
}

void work_poll(void)
{
    work_t *work_cur, *work_next;
    struct list_head *node;
    node = &work_head;

    work_cur = list_entry(node->next,work_t,node);
    
    list_for_each_entry_safe(work_cur, work_next, &work_head, node)
    {
        if(work_cur->poll)
        {
            work_cur->poll(work_cur->priv);
        
            list_del(&work_cur->node);
        }
    }  
}


int work_create(work_t *work, work_cb cb, void*priv)
{
    if (work==NULL || cb==NULL)
    {
        //printf("work create failed!\n");
        return -1;
    }

    work->poll = cb;
    work->priv = priv;

    return 0;
}

void work_destroy(work_t *work)
{
    return ;
}

