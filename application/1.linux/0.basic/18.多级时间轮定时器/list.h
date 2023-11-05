#if !defined(_BLKID_LIST_H) && !defined(LIST_HEAD)
#define _BLKID_LIST_H
#ifdef __cplusplus 
extern "C" {
#endif
/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct list_head {
 struct list_head *next, *prev;
};
#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
 struct list_head name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr) do { \
 (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)
static inline void
__list_add(struct list_head *entry,
                struct list_head *prev, struct list_head *next)
{
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;
}
/**
 * Insert a new element after the given list head. The new element does not
 * need to be initialised as empty list.
 * The list changes from:
 *      head → some element → ...
 * to
 *      head → new element → older element → ...
 *
 * Example:
 * struct foo *newfoo = malloc(...);
 * list_add(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
static inline void
list_add(struct list_head *entry, struct list_head *head)
{
    __list_add(entry, head, head->next);
}
/**
 * Append a new element to the end of the list given with this list head.
 *
 * The list changes from:
 *      head → some element → ... → lastelement
 * to
 *      head → some element → ... → lastelement → new element
 *
 * Example:
 * struct foo *newfoo = malloc(...);
 * list_add_tail(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
static inline void
list_add_tail(struct list_head *entry, struct list_head *head)
{
    __list_add(entry, head->prev, head);
}
static inline void
__list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}
/**
 * Remove the element from the list it is in. Using this function will reset
 * the pointers to/from this element so it is removed from the list. It does
 * NOT free the element itself or manipulate it otherwise.
 *
 * Using list_del on a pure list head (like in the example at the top of
 * this file) will NOT remove the first element from
 * the list but rather reset the list as empty list.
 *
 * Example:
 * list_del(&foo->entry);
 *
 * @param entry The element to remove.
 */
static inline void
list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}
static inline void
list_del_init(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}
static inline void list_move_tail(struct list_head *list,
      struct list_head *head)
{
 __list_del(list->prev, list->next);
 list_add_tail(list, head);
}
/**
 * Check if the list is empty.
 *
 * Example:
 * list_empty(&bar->list_of_foos);
 *
 * @return True if the list contains one or more elements or False otherwise.
 */
static inline int
list_empty(struct list_head *head)
{
    return head->next == head;
}
/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(struct list_head *old,
    struct list_head *new)
{
 new->next = old->next;
 new->next->prev = new;
 new->prev = old->prev;
 new->prev->next = new;
}
/**
 * Retrieve the first list entry for the given list pointer.
 *
 * Example:
 * struct foo *first;
 * first = list_first_entry(&bar->list_of_foos, struct foo, list_of_foos);
 *
 * @param ptr The list head
 * @param type Data type of the list element to retrieve
 * @param member Member name of the struct list_head field in the list element.
 * @return A pointer to the first list element.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)
static inline void list_replace_init(struct list_head *old,
     struct list_head *new)
{
 list_replace(old, new);
 INIT_LIST_HEAD(old);
}
/**
 * list_entry - get the struct for this entry
 * @ptr: the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
 ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
/**
 * list_for_each - iterate over elements in a list
 * @pos: the &struct list_head to use as a loop counter.
 * @head: the head for your list.
 */
#define list_for_each(pos, head) \
 for (pos = (head)->next; pos != (head); pos = pos->next)
/**
 * list_for_each_safe - iterate over elements in a list, but don't dereference
 *                      pos after the body is done (in case it is freed)
 * @pos: the &struct list_head to use as a loop counter.
 * @pnext: the &struct list_head to use as a pointer to the next item.
 * @head: the head for your list (not included in iteration).
 */
#define list_for_each_safe(pos, pnext, head) \
 for (pos = (head)->next, pnext = pos->next; pos != (head); \
      pos = pnext, pnext = pos->next)
#ifdef __cplusplus
}
#endif
#endif /* _BLKID_LIST_H */