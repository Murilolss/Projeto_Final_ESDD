#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doubly_list.h"
#include "memory.h"

typedef struct Node {
    int value;
    struct Node *prev; /* previous node, or NULL if this is the first one */
    struct Node *next; /* next node, or NULL if this is the last one */
} Node;

struct DoublyList {
    Node *head; /* first node, or NULL if the list is empty */
    Node *tail; /* last node, or NULL if the list is empty */
    int size;   /* number of nodes */
};

DoublyList *dlist_create(void)
{
    DoublyList *l = (DoublyList *)mem_alloc(sizeof(DoublyList));

    if (l == NULL)
        return NULL;

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return l;
}

int dlist_insert_back(DoublyList *l, int value)
{
    Node *new_node;

    if (l == NULL)
        return 0;

    new_node = (Node *)mem_alloc(sizeof(Node));
    if (new_node == NULL)
        return 0;

    new_node->value = value;
    new_node->prev = l->tail; /* the old last node comes before the new one */
    new_node->next = NULL;

    if (l->tail != NULL)
        l->tail->next = new_node;
    else
        l->head = new_node; /* the list was empty: the new node is also the first one */

    l->tail = new_node;
    l->size++;

    return 1;
}

int dlist_from_array(DoublyList *l, const int *v, int size)
{
    if (l == NULL || v == NULL || size <= 0)
        return 0;

    dlist_clear(l);

    /* With the tail pointer, inserting at the end costs O(1), so the array can be read
       from the first value to the last one (the singly list has no tail and has to
       insert at the start, from the last value to the first one). */
    for (int i = 0; i < size; i++)
    {
        if (dlist_insert_back(l, v[i]) == 0)
        {
            dlist_clear(l);
            return 0;
        }
    }

    return 1;
}

int dlist_to_array(const DoublyList *l, int *out, int size)
{
    Node *current;
    int i = 0;

    if (l == NULL || out == NULL || size != l->size)
        return 0;

    current = l->head;
    while (current != NULL)
    {
        out[i] = current->value;
        i++;
        current = current->next;
    }

    return 1;
}

int dlist_size(const DoublyList *l)
{
    if (l == NULL)
        return 0;

    return l->size;
}

long long dlist_memory_bytes(const DoublyList *l)
{
    if (l == NULL)
        return 0;

    return (long long)sizeof(DoublyList) + (long long)l->size * (long long)sizeof(Node);
}

void dlist_print(const DoublyList *l)
{
    Node *current;

    if (l == NULL)
        return;

    current = l->head;
    while (current != NULL)
    {
        printf("%d <-> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void dlist_print_reverse(const DoublyList *l)
{
    Node *current;

    if (l == NULL)
        return;

    current = l->tail;
    while (current != NULL)
    {
        printf("%d <-> ", current->value);
        current = current->prev;
    }
    printf("NULL\n");
}

void dlist_clear(DoublyList *l)
{
    Node *current;
    Node *temp;

    if (l == NULL)
        return;

    current = l->head;
    while (current != NULL)
    {
        temp = current;
        current = current->next; /* saves the next node before freeing this one */
        mem_free(temp, sizeof(Node));
        temp = NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

void dlist_destroy(DoublyList **l)
{
    if (l == NULL || *l == NULL)
        return;

    dlist_clear(*l);
    mem_free(*l, sizeof(DoublyList));
    *l = NULL;
}

/* ---------- Insertion Sort (moving nodes) ---------- */

/* The sorted part goes from head to sorted_tail. The node right after sorted_tail
   (current) is the next one to be inserted.
   - If current is not smaller than sorted_tail, it is already in place: the sorted part
     just grows by one node (1 comparison, no node moved).
   - Otherwise current is unlinked and the search goes back from sorted_tail using the
     prev pointers, like the array version goes from right to left. Each node inserted
     in another position counts as 1 swap.
   Sorted data: n - 1 comparisons and 0 moves (same as the array).
   Reversed data: every node walks back to the head, about n * n / 2 comparisons (same
   as the array), but only n - 1 nodes moved (the array shifts about n * n / 2 values). */
int dlist_insertion_sort(DoublyList *l, Metrics *m)
{
    Node *sorted_tail;
    Node *current;
    Node *pos;

    if (l == NULL || m == NULL)
        return 0;
    if (l->head == NULL || l->head->next == NULL)
        return 1; /* empty list or only one node: already sorted */

    sorted_tail = l->head;
    while (sorted_tail->next != NULL)
    {
        current = sorted_tail->next;

        m->comparisons++;
        if (sorted_tail->value <= current->value)
        {
            sorted_tail = current; /* already in place */
            continue;
        }

        /* Unlinks current, connecting its two neighbours (like remover in the class
           slides, but without free: the node will be linked again). */
        sorted_tail->next = current->next;
        if (current->next != NULL)
            current->next->prev = sorted_tail;
        else
            l->tail = sorted_tail; /* current was the last node */

        /* Goes back while the values are greater than current->value.
           pos stops at the last node with value <= current->value, or at NULL if
           current is smaller than all the sorted part. */
        pos = sorted_tail->prev;
        while (pos != NULL)
        {
            m->comparisons++;
            if (pos->value <= current->value)
                break;
            pos = pos->prev;
        }

        if (pos == NULL)
        {
            /* current becomes the new head */
            current->prev = NULL;
            current->next = l->head;
            l->head->prev = current;
            l->head = current;
        }
        else
        {
            /* Links current between pos and pos->next. pos->next is never NULL here,
               because pos comes before sorted_tail. */
            current->prev = pos;
            current->next = pos->next;
            pos->next->prev = current;
            pos->next = current;
        }
        m->swaps++;
    }

    return 1;
}

/* ---------- Merge Sort (moving nodes) ---------- */

/* Splits the list that starts at head in two halves and returns the start of the
   second one. slow walks one node at a time and fast walks two, so when fast reaches
   the end, slow is in the middle. Both halves become separate lists: the first one
   ends with next = NULL and the second one starts with prev = NULL.
   head must have at least two nodes. */
static Node *split_middle(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;
    Node *second;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    second = slow->next;
    slow->next = NULL;
    second->prev = NULL;

    return second;
}

/* Merges two sorted lists (a and b) into one and returns its first node.
   No node is allocated: the smaller front node is linked after tail each time, setting
   both pointers (tail->next and node->prev). Each node linked this way counts as 1 swap.
   When one list ends, the rest of the other one is linked at once (those nodes do not
   move, so they are not counted).
   It is a loop and not a recursion: a recursive merge would go n levels deep and
   overflow the stack with n = 50000. */
static Node *merge_nodes(Node *a, Node *b, Metrics *m)
{
    Node *first;
    Node *tail;

    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    /* Chooses the first node of the result */
    m->comparisons++;
    if (a->value <= b->value)
    {
        first = a;
        a = a->next;
    }
    else
    {
        first = b;
        b = b->next;
    }
    first->prev = NULL;
    m->swaps++;
    tail = first;

    while (a != NULL && b != NULL)
    {
        m->comparisons++;
        if (a->value <= b->value)
        {
            tail->next = a;
            a->prev = tail;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b->prev = tail;
            b = b->next;
        }
        tail = tail->next;
        m->swaps++;
    }

    /* Links what is left (only one of them is not NULL) */
    if (a != NULL)
    {
        tail->next = a;
        a->prev = tail;
    }
    else
    {
        tail->next = b;
        b->prev = tail;
    }

    return first;
}

/* Sorts the list that starts at head and returns its new first node.
   Each call splits the list in half, so the recursion depth is about log2(n). */
static Node *merge_sort_nodes(Node *head, Metrics *m)
{
    Node *second;

    if (head == NULL || head->next == NULL)
        return head; /* 0 or 1 node: already sorted */

    second = split_middle(head);
    head = merge_sort_nodes(head, m);
    second = merge_sort_nodes(second, m);

    return merge_nodes(head, second, m);
}

/* Unlike the array version, it needs no temporary arrays: the extra memory is 0. */
int dlist_merge_sort(DoublyList *l, Metrics *m)
{
    Node *current;

    if (l == NULL || m == NULL)
        return 0;
    if (l->head == NULL)
        return 1; /* empty list: already sorted */

    l->head = merge_sort_nodes(l->head, m);

    /* The merge does not keep track of the last node, so it is found here once, O(n). */
    current = l->head;
    while (current->next != NULL)
        current = current->next;
    l->tail = current;

    return 1;
}

/* ---------- Algorithm table ---------- */

/* Pointer to a list sort function (same idea as SortFunction in sort.h). */
typedef int (*ListSortFunction)(DoublyList *l, Metrics *m);

typedef struct {
    const char *name;
    ListSortFunction function;
} ListSortAlgorithm;

static const ListSortAlgorithm list_algorithms[DLIST_SORT_COUNT] = {
    {"Insertion Lista Dupla", dlist_insertion_sort},
    {"Merge Lista Dupla", dlist_merge_sort}
};

const char *dlist_sort_name(int index)
{
    if (index < 0 || index >= DLIST_SORT_COUNT)
        return NULL;

    return list_algorithms[index].name;
}

int dlist_sort_run(int index, const int *source, int size, DoublyList *dest, Metrics *out)
{
    clock_t start, end;
    long long baseline;
    int ok;

    if (index < 0 || index >= DLIST_SORT_COUNT)
        return 0;
    if (source == NULL || dest == NULL || out == NULL || size <= 0)
        return 0;

    /* The list is built before the clock starts, so it is not part of the measured time */
    if (dlist_from_array(dest, source, size) == 0)
        return 0;
    metrics_init(out, list_algorithms[index].name);

    /* Extra memory = peak during the sort minus what was allocated before it
       (the vector and the nodes of the list). */
    mem_reset_peak();
    baseline = mem_current();

    start = clock();
    ok = list_algorithms[index].function(dest, out);
    end = clock();

    out->time_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    out->memory_bytes = mem_peak() - baseline;
    return ok;
}
