#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include "metrics.h"

/* Doubly linked list of ints.
   Each node has a value, a pointer to the previous node and a pointer to the next one.
   The first node has prev = NULL and the last one has next = NULL.
   Consistency rule: if A->next == B, then B->prev == A.
   The struct is opaque: only doubly_list.c knows its fields (head, tail and size).
   Every node is allocated with mem_alloc and freed with mem_free (memory.h). */
typedef struct DoublyList DoublyList;

/* Number of algorithms in the list algorithm table (doubly_list.c). */
#define DLIST_SORT_COUNT 2

/* Creates an empty list. Returns NULL if there is not enough memory. */
DoublyList *dlist_create(void);

/* Inserts value at the end of the list in O(1) (uses the tail pointer).
   Returns 1 on success, 0 on failure. */
int dlist_insert_back(DoublyList *l, int value);

/* Removes all nodes and inserts the values of v, in the same order as the array.
   Returns 1 on success; returns 0 on invalid arguments or if there is not enough memory
   (in that case the list is left empty). */
int dlist_from_array(DoublyList *l, const int *v, int size);

/* Copies the values of the list to out (which has room for size ints).
   Returns 1 on success; returns 0 on invalid arguments or if size is not the list size. */
int dlist_to_array(const DoublyList *l, int *out, int size);

/* Number of nodes, or 0 if l is NULL. */
int dlist_size(const DoublyList *l);

/* Bytes used by the list: the list struct plus all the nodes. */
long long dlist_memory_bytes(const DoublyList *l);

/* Prints the list from head to tail: 1 <-> 2 <-> 3 <-> NULL. */
void dlist_print(const DoublyList *l);

/* Prints the list from tail to head, following the prev pointers: 3 <-> 2 <-> 1 <-> NULL. */
void dlist_print_reverse(const DoublyList *l);

/* Frees all nodes. The list itself stays allocated and becomes empty. */
void dlist_clear(DoublyList *l);

/* Frees all nodes and the list, and sets the caller's pointer to NULL. */
void dlist_destroy(DoublyList **l);

/* Both sorts only change the prev and next pointers (and head and tail): no value is
   copied and no node is allocated. They count comparisons and nodes moved (in m->swaps).
   Return 1 on success, 0 if l or m is NULL. */
int dlist_insertion_sort(DoublyList *l, Metrics *m);
int dlist_merge_sort(DoublyList *l, Metrics *m);

/* Name of the list algorithm at position index (0 .. DLIST_SORT_COUNT - 1), or NULL. */
const char *dlist_sort_name(int index);

/* Same idea as sort_run (sort.h): rebuilds dest with the values of source (before the
   clock starts), sorts it with the algorithm at position index and fills out with its
   metrics, time and extra memory (peak bytes).
   Returns 1 on success, 0 on invalid arguments or out of memory. */
int dlist_sort_run(int index, const int *source, int size, DoublyList *dest, Metrics *out);

#endif
