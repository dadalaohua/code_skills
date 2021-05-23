/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_LIST_H_
#define _U_LIST_H_

// #include <u/libu_conf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* forward decl */
struct u_list_s;

/**
 *  \addtogroup list
 *  \{
 */

/** \brief  Basic list object type */
typedef struct u_list_s u_list_t;

/** \brief  List iterator 
 *
 *  \param  list    an ::u_list_t object
 *  \param  n       a variable that will get the current value from \p list
 *  \param  it      an opaque iterator with type \c void**
 */
#define u_list_foreach(list, n, it) \
    for(n = u_list_first(list, &it); n; n = u_list_next(list, &it))

/** \brief  List iterator with iteration counter
 *
 *  \param  list    an ::u_list_t object
 *  \param  n       a variable that will get the current value from \p list
 *  \param  it      an opaque iterator with type \c void**
 *  \param  i       variable of type \c integer that will be get the iteration
 *                  counter (0..i)
 */ 
#define u_list_iforeach(list, n, it, i) \
    for(i = 0, n = u_list_first(list, &it); n; n = u_list_next(list, &it), ++i)

int u_list_create (u_list_t **plist);
void u_list_free (u_list_t *list);
int u_list_clear (u_list_t *list);
int u_list_add (u_list_t *list, void *ptr);
int u_list_insert (u_list_t *list, void *ptr, size_t n);
int u_list_del (u_list_t *list, void *ptr);
int u_list_del_n (u_list_t *list, size_t n, void **pptr);
void *u_list_get_n (u_list_t *list, size_t n);
size_t u_list_count (u_list_t *list);
void *u_list_first (u_list_t *list, void **it);
void *u_list_next (u_list_t *list, void **it);

/**
 *  \}
 */ 
 
/* Tail queue definitions. */
#define TAILQ_HEAD(name, type)                                              \
struct name {                                                               \
        struct type *tqh_first;     /* first element */                     \
        struct type **tqh_last;     /* addr of last next element */         \
}


#define TAILQ_ENTRY(type)                                                   \
struct {                                                                    \
        struct type *tqe_next;      /* next element */                      \
        struct type **tqe_prev;     /* address of previous next element */  \
}

/* Tail queue functions. */
#define TAILQ_INIT(head) {                                                  \
        (head)->tqh_first = NULL;                                           \
        (head)->tqh_last = &(head)->tqh_first;                              \
}

#define TAILQ_INSERT_HEAD(head, elm, field) {                               \
        if (((elm)->field.tqe_next = (head)->tqh_first) != NULL)            \
                (elm)->field.tqe_next->field.tqe_prev =                     \
                    &(elm)->field.tqe_next;                                 \
        else                                                                \
                (head)->tqh_last = &(elm)->field.tqe_next;                  \
        (head)->tqh_first = (elm);                                          \
        (elm)->field.tqe_prev = &(head)->tqh_first;                         \
}

#define TAILQ_INSERT_TAIL(head, elm, field) {                               \
        (elm)->field.tqe_next = NULL;                                       \
        (elm)->field.tqe_prev = (head)->tqh_last;                           \
        *(head)->tqh_last = (elm);                                          \
        (head)->tqh_last = &(elm)->field.tqe_next;                          \
}

#define TAILQ_INSERT_AFTER(head, listelm, elm, field) {                     \
        if (((elm)->field.tqe_next = (listelm)->field.tqe_next) != NULL)    \
                (elm)->field.tqe_next->field.tqe_prev =                     \
                    &(elm)->field.tqe_next;                                 \
        else                                                                \
                (head)->tqh_last = &(elm)->field.tqe_next;                  \
        (listelm)->field.tqe_next = (elm);                                  \
        (elm)->field.tqe_prev = &(listelm)->field.tqe_next;                 \
}

#define TAILQ_INSERT_BEFORE(listelm, elm, field) do {                       \
        (elm)->field.tqe_prev = (listelm)->field.tqe_prev;                  \
        (elm)->field.tqe_next = (listelm);                                  \
        *(listelm)->field.tqe_prev = (elm);                                 \
        (listelm)->field.tqe_prev = &(elm)->field.tqe_next;                 \
} while (0)

#define TAILQ_REMOVE(head, elm, field) {                                    \
        if (((elm)->field.tqe_next) != NULL)                                \
                (elm)->field.tqe_next->field.tqe_prev =                     \
                    (elm)->field.tqe_prev;                                  \
        else                                                                \
                (head)->tqh_last = (elm)->field.tqe_prev;                   \
        *(elm)->field.tqe_prev = (elm)->field.tqe_next;                     \
}

#ifndef LIST_ENTRY_NULL
#define LIST_ENTRY_NULL { NULL, NULL }
#endif

#ifndef LIST_FOREACH_SAFE
#define LIST_FOREACH_SAFE(var, head, field, tvar)                       \
        for ((var) = LIST_FIRST((head));                                \
            (var) && ((tvar) = LIST_NEXT((var), field), 1);             \
            (var) = (tvar))
#endif

#ifndef LIST_FIRST
#define LIST_FIRST(head)    ((head)->lh_first)
#endif 

#ifndef TAILQ_ENTRY_NULL
#define TAILQ_ENTRY_NULL { NULL, NULL }
#endif

#ifndef TAILQ_FIRST
#define TAILQ_FIRST(head)   ((head)->tqh_first)
#endif 

#ifndef TAILQ_END
#define TAILQ_END(head)     NULL
#endif

#ifndef TAILQ_NEXT
#define TAILQ_NEXT(elm, field)  ((elm)->field.tqe_next)
#endif

#ifndef TAILQ_LAST
#define TAILQ_LAST(head, headname)                                          \
        (*(((struct headname *)((head)->tqh_last))->tqh_last))
#endif

#ifndef TAILQ_PREV
#define TAILQ_PREV(elm, headname, field)                                    \
        (*(((struct headname *)((elm)->field.tqe_prev))->tqh_last))
#endif

#ifndef TAILQ_EMPTY
#define TAILQ_EMPTY(head)                                                   \
        (TAILQ_FIRST(head) == TAILQ_END(head))
#endif

#ifndef TAILQ_FOREACH
#define TAILQ_FOREACH(var, head, field)                                     \
        for((var) = TAILQ_FIRST(head);                                      \
            (var) != TAILQ_END(head);                                       \
            (var) = TAILQ_NEXT(var, field))
#endif

#ifndef TAILQ_FOREACH_SAFE
#define TAILQ_FOREACH_SAFE(var, head, field, tvar)                      \
        for ((var) = TAILQ_FIRST((head));                               \
            (var) && ((tvar) = TAILQ_NEXT((var), field), 1);            \
            (var) = (tvar))
          
#endif
#ifndef TAILQ_FOREACH_REVERSE
#define TAILQ_FOREACH_REVERSE(var, head, headname, field)               \
        for ((var) = TAILQ_LAST((head), headname);                      \
            (var);                                                      \
            (var) = TAILQ_PREV((var), headname, field))

#endif

#ifndef TAILQ_FOREACH_REVERSE_SAFE
#define TAILQ_FOREACH_REVERSE_SAFE(var, head, headname, field, tvar)    \
        for ((var) = TAILQ_LAST((head), headname);                      \
            (var) && ((tvar) = TAILQ_PREV((var), headname, field), 1);  \
            (var) = (tvar))
#endif


#define u_zalloc(sz) calloc(1, sz)
#define u_free(sz) free(sz)

#define nop_return_if(expr, err)       do { if(expr) return err; } while(0)

#define dbg_return_if(expr, err)    do { if( (expr) ) return err; } while(0)

#define dbg_err_if(expr)            do { if( (expr) ) goto err; } while(0)
#define dbg_err_sif(expr)           do { if( (expr) ) goto err; } while(0)

#ifdef __cplusplus
}
#endif

#endif /* !_U_LIST_H_ */
