#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include "metrics.h"

/* Singly linked list of ints.
   Each node has a value and a pointer to the next node; the last one points to NULL.
   The struct is opaque: only singly_list.c knows its fields (head and size).
   Every node is allocated with mem_alloc and freed with mem_free (memory.h). */
typedef struct SinglyList SinglyList;

/* Number of algorithms in the list algorithm table (singly_list.c). */
#define SLIST_SORT_COUNT 2

/* Creates an empty list. Returns NULL if there is not enough memory. */
SinglyList *slist_create(void);

/* Inserts value at the start of the list. Returns 1 on success, 0 on failure. */
int slist_insert_front(SinglyList *l, int value);

/* Removes all nodes and inserts the values of v, in the same order as the array.
   Returns 1 on success; returns 0 on invalid arguments or if there is not enough memory
   (in that case the list is left empty). */
int slist_from_array(SinglyList *l, const int *v, int size);

/* Copies the values of the list to out (which has room for size ints).
   Returns 1 on success; returns 0 on invalid arguments or if size is not the list size. */
int slist_to_array(const SinglyList *l, int *out, int size);

/* Number of nodes, or 0 if l is NULL. */
int slist_size(const SinglyList *l);

/* Bytes used by the list: the list struct plus all the nodes. */
long long slist_memory_bytes(const SinglyList *l);

/* Prints the list as 1 -> 2 -> 3 -> NULL. */
void slist_print(const SinglyList *l);

/* Frees all nodes. The list itself stays allocated and becomes empty. */
void slist_clear(SinglyList *l);

/* Frees all nodes and the list, and sets the caller's pointer to NULL. */
void slist_destroy(SinglyList **l);

/* Both sorts only change the next pointers: no value is copied and no node is allocated.
   They count comparisons and nodes moved (in m->swaps).
   Return 1 on success, 0 if l or m is NULL. */
int slist_insertion_sort(SinglyList *l, Metrics *m);
int slist_merge_sort(SinglyList *l, Metrics *m);

/* Name of the list algorithm at position index (0 .. SLIST_SORT_COUNT - 1), or NULL. */
const char *slist_sort_name(int index);

/* Same idea as sort_run (sort.h): rebuilds dest with the values of source (before the
   clock starts), sorts it with the algorithm at position index and fills out with its
   metrics, time and extra memory (peak bytes).
   Returns 1 on success, 0 on invalid arguments or out of memory. */
int slist_sort_run(int index, const int *source, int size, SinglyList *dest, Metrics *out);

#endif
