#include "ipp_list.h"
#include <stdlib.h>

void list_init(ipp_list *list)
{
	list->next = list->prev = list;
}

/* initialize a ipp_list */
ipp_list *create_ipp_list()
{
	ipp_list *list = (ipp_list *)malloc(sizeof(ipp_list));
	list_init(list);
	return list;
}

/* add an element after the specified one */
void list_add_after(ipp_list *elem ,ipp_list *to_add)
{
	to_add->next = elem->next;
	to_add->prev = elem;
	elem->next->prev = to_add;
	elem->next = to_add;
}

/* add an element before the specified one */
void list_add_before(ipp_list *elem ,ipp_list *to_add)
{
	to_add->next = elem;
	to_add->prev = elem->prev;
	elem->prev->next = to_add;
	elem->prev = to_add;
}

/* add element at the head of the ipp_list */
void list_add_head(ipp_list *list ,ipp_list *elem)
{
	list_add_after( list, elem);
}

/* add element at the tail of the ipp_list */
void list_add_tail(ipp_list *list ,ipp_list *elem)
{
	list_add_before( list, elem);
}

/* remove an element from its ipp_list */
void list_remove(ipp_list *elem)
{
	elem->next->prev = elem->prev;
	elem->prev->next = elem->next;
}

/* get the next element */
ipp_list *list_next(const ipp_list *list, const ipp_list *elem)
{
	ipp_list *ret = elem->next;
	if (elem->next == list) ret = NULL;
	return ret;
}

/* get the previous element */
ipp_list *list_prev(const ipp_list *list, const ipp_list *elem)
{
	ipp_list *ret = elem->prev;
	if (elem->prev == list) ret = NULL;
	return ret;
}

/* get the first element */
ipp_list *list_head(const ipp_list *list)
{
	return list_next(list, list);
}

/* get the last element */
ipp_list *list_tail(const ipp_list *list)
{
	return list_prev( list, list);
}

/* check if a list is empty */
int list_empty(const ipp_list *list)
{
	return list->next == list;
}

/* count the elements of a ipp_list */
unsigned int list_count(const ipp_list *list)
{
	unsigned count = 0;
	const ipp_list *ptr;
	for (ptr = list->next; ptr != list; ptr = ptr->next) count++;
	return count;
}

/* move all elements from src to the tail of dst */
void list_move_tail(ipp_list *dst ,ipp_list *src)
{
	if (list_empty(src)) return;

	dst->prev->next = src->next;
	src->next->prev = dst->prev;
	dst->prev = src->prev;
	src->prev->next = dst;
	list_init(src);
}

/* move all elements from src to the head of dst */
void list_move_head(ipp_list *dst ,ipp_list *src)
{
	if (list_empty(src)) return;

	dst->next->prev = src->prev;
	src->prev->next = dst->next;
	dst->next = src->next;
	src->next->prev = dst;
	list_init(src);
}
