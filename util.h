/* See LICENSE file for copyright and license details. */

#ifndef BSPWMBAR_UTIL_H_
#define BSPWMBAR_UTIL_H_
#include <unistd.h>

/* utility macros */
#define LENGTH(X)        (sizeof (X) / sizeof (X[0]))
#define BETWEEN(X, A, B) ((A) <= (X) && (X) <= (B))
#define SMALLER(A, B)    ((A) < (B) ? (A) : (B))
#define BIGGER(A, B)     ((A) > (B) ? (A) : (B))
#define DIVCEIL(n, d)    (((n) + ((d) - 1)) / (d))

extern char buf[1024];

void die(const char *, ...);
int pscanf(const char *, const char *, ...);

typedef struct _list_head {
	struct _list_head *prev, *next;
} list_head;

/* list */
#define list_head_init(ptr) { (ptr)->prev = (ptr); (ptr)->next = (ptr); }
#define list_for_each(head, pos) \
for (pos = (head)->next; pos != (head); pos = pos->next)
#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define list_empty(head) ((head)->next == (head))

static inline void
list_init(list_head *head, list_head *prev, list_head *next)
{
	next->prev = head;
	head->next = next;
	head->prev = prev;
	prev->next = head;
}

static inline void
list_add(list_head *head, list_head *entry)
{
	list_init(entry, head, head->next);
}

static inline void
list_add_tail(list_head *head, list_head *entry)
{
	list_init(entry, head->prev, head);
}

static inline void
list_del(list_head *head)
{
	list_head *prev = head->prev;
	list_head *next = head->next;

	next->prev = prev;
	prev->next = next;
}

#endif
