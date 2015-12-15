#ifndef _IPP_LIST_H_
#define _IPP_LIST_H_

#include <stddef.h>

typedef struct _ipp_list
{
	struct _ipp_list *next;
	struct _ipp_list *prev;
}ipp_list;

/* initialize a ipp_list */
ipp_list *create_ipp_list();

/* add an element after the specified one */
void list_add_after(ipp_list *elem ,ipp_list *to_add);

/* add an element before the specified one */
void list_add_before(ipp_list *elem ,ipp_list *to_add);

/* add element at the head of the ipp_list */
void list_add_head(ipp_list *list ,ipp_list *elem);

/* add element at the tail of the ipp_list */
void list_add_tail(ipp_list *list ,ipp_list *elem);

/* remove an element from its ipp_list */
void list_remove(ipp_list *elem);

/* get the next element */
ipp_list *list_next(const ipp_list *list, const ipp_list *elem);

/* get the previous element */
ipp_list *list_prev(const ipp_list *list, const ipp_list *elem);

/* get the first element */
ipp_list *list_head(const ipp_list *list);

/* get the last element */
ipp_list *list_tail(const ipp_list *list);

/* check if a list is empty */
int list_empty(const ipp_list *list);

/* count the elements of a ipp_list */
unsigned int list_count(const ipp_list *list);

/* move all elements from src to the tail of dst */
void list_move_tail(ipp_list *dst ,ipp_list *src);

/* move all elements from src to the head of dst */
void list_move_head(ipp_list *dst ,ipp_list *src);

/* iterate through the ipp_list */
#define LIST_FOR_EACH(cursor,list) \
	for ((cursor) = (list)->next; (cursor) != (list); (cursor) = (cursor)->next)

/* iterate through the list, with safety against removal */
#define LIST_FOR_EACH_SAFE(cursor, cursor2, list) \
	for ((cursor) = (list)->next, (cursor2) = (cursor)->next; \
	(cursor) != (list); \
	(cursor) = (cursor2), (cursor2) = (cursor)->next)

/* iterate through the list using a list entry */
#define LIST_FOR_EACH_DEF_ENTRY(elem, list, type) \
	LIST_FOR_EACH_ENTRY(elem, list, type, entry)

/* iterate through the list using a list entry */
#define LIST_FOR_EACH_ENTRY(elem, list, type, field) \
	for ((elem) = LIST_ENTRY((list)->next, type, field); \
	&(elem)->field != (list); \
	(elem) = LIST_ENTRY((elem)->field.next, type, field))

/* iterate through the list using a list entry, with safety against removal */
#define LIST_FOR_EACH_ENTRY_SAFE(cursor, cursor2, list, type, field) \
	for ((cursor) = LIST_ENTRY((list)->next, type, field), \
	(cursor2) = LIST_ENTRY((cursor)->field.next, type, field); \
	&(cursor)->field != (list); \
	(cursor) = (cursor2), \
	(cursor2) = LIST_ENTRY((cursor)->field.next, type, field))

/* iterate through the list in reverse order */
#define LIST_FOR_EACH_REV(cursor,list) \
	for ((cursor) = (list)->prev; (cursor) != (list); (cursor) = (cursor)->prev)

/* iterate through the list in reverse order, with safety against removal */
#define LIST_FOR_EACH_SAFE_REV(cursor, cursor2, list) \
	for ((cursor) = (list)->prev, (cursor2) = (cursor)->prev; \
	(cursor) != (list); \
	(cursor) = (cursor2), (cursor2) = (cursor)->prev)

/* iterate through the list in reverse order using a list entry */
#define LIST_FOR_EACH_ENTRY_REV(elem, list, type, field) \
	for ((elem) = LIST_ENTRY((list)->prev, type, field); \
	&(elem)->field != (list); \
	(elem) = LIST_ENTRY((elem)->field.prev, type, field))

/* iterate through the list in reverse order using a list entry, with safety against removal */
#define LIST_FOR_EACH_ENTRY_SAFE_REV(cursor, cursor2, list, type, field) \
	for ((cursor) = LIST_ENTRY((list)->prev, type, field), \
	(cursor2) = LIST_ENTRY((cursor)->field.prev, type, field); \
	&(cursor)->field != (list); \
	(cursor) = (cursor2), \
	(cursor2) = LIST_ENTRY((cursor)->field.prev, type, field))

/* get pointer to object containing list element */
#undef LIST_ENTRY
#define LIST_ENTRY(elem, type, field) \
	((type *)((char *)(elem) - offsetof(type, field)))

#endif  /* _LIST_H_ */
