#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include "metrics.h"

/* Circular singly linked list of ints.
   Each node has a value and a pointer to the next node. There is no NULL at the end:
   the last node points back to the first one.
   The list keeps only a pointer to the last node (tail): the first node is tail->next.
   With only one node, tail->next == tail. An empty list has tail = NULL.
   The struct is opaque: only circular_list.c knows its fields (tail and size).
   Every node is allocated with mem_alloc and freed with mem_free (memory.h). */
typedef struct CircularList CircularList;

/* Number of algorithms in the list algorithm table (circular_list.c). */
#define CLIST_SORT_COUNT 2

/* Creates an empty list. Returns NULL if there is not enough memory. */
CircularList *clist_create(void);

/* Inserts value at the end of the list in O(1) (uses the tail pointer).
   Returns 1 on success, 0 on failure. */
int clist_insert_back(CircularList *l, int value);

/* Removes all nodes and inserts the values of v, in the same order as the array.
   Returns 1 on success; returns 0 on invalid arguments or if there is not enough memory
   (in that case the list is left empty). */
int clist_from_array(CircularList *l, const int *v, int size);

/* Copies the values of the list to out (which has room for size ints), starting at the
   first node. Returns 1 on success; returns 0 on invalid arguments or if size is not
   the list size. */
int clist_to_array(const CircularList *l, int *out, int size);

/* Number of nodes, or 0 if l is NULL. */
int clist_size(const CircularList *l);

/* Bytes used by the list: the list struct plus all the nodes. */
long long clist_memory_bytes(const CircularList *l);

/* Prints the list once around the circle: 1 -> 2 -> 3 -> (volta ao 1). */
void clist_print(const CircularList *l);

/* Frees all nodes. The list itself stays allocated and becomes empty. */
void clist_clear(CircularList *l);

/* Frees all nodes and the list, and sets the caller's pointer to NULL. */
void clist_destroy(CircularList **l);

/* Both sorts open the circle (the last node points to NULL), sort it like a singly
   linked list and close the circle again. They only change the next pointers (and tail):
   no value is copied and no node is allocated. They count comparisons and nodes moved
   (in m->swaps). Return 1 on success, 0 if l or m is NULL. */
int clist_insertion_sort(CircularList *l, Metrics *m);
int clist_merge_sort(CircularList *l, Metrics *m);

/* Name of the list algorithm at position index (0 .. CLIST_SORT_COUNT - 1), or NULL. */
const char *clist_sort_name(int index);

/* Same idea as sort_run (sort.h): rebuilds dest with the values of source (before the
   clock starts), sorts it with the algorithm at position index and fills out with its
   metrics, time and extra memory (peak bytes).
   Returns 1 on success, 0 on invalid arguments or out of memory. */
int clist_sort_run(int index, const int *source, int size, CircularList *dest, Metrics *out);

#endif
