#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "circular_list.h"
#include "memory.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct CircularList {
    Node *tail; /* last node (tail->next is the first one), or NULL if the list is empty */
    int size;   /* number of nodes */
};

CircularList *clist_create(void)
{
    CircularList *l = (CircularList *)mem_alloc(sizeof(CircularList));

    if (l == NULL)
        return NULL;

    l->tail = NULL;
    l->size = 0;

    return l;
}

int clist_insert_back(CircularList *l, int value)
{
    Node *new_node;

    if (l == NULL)
        return 0;

    new_node = (Node *)mem_alloc(sizeof(Node));
    if (new_node == NULL)
        return 0;

    new_node->value = value;
    if (l->tail == NULL)
    {
        new_node->next = new_node; /* only node: it points to itself */
    }
    else
    {
        new_node->next = l->tail->next; /* the new last node points to the first one */
        l->tail->next = new_node;       /* the old last node points to the new one */
    }
    l->tail = new_node;
    l->size++;

    return 1;
}

int clist_from_array(CircularList *l, const int *v, int size)
{
    if (l == NULL || v == NULL || size <= 0)
        return 0;

    clist_clear(l);

    /* Inserting at the end costs O(1) per value, because the list keeps the tail */
    for (int i = 0; i < size; i++)
    {
        if (clist_insert_back(l, v[i]) == 0)
        {
            clist_clear(l);
            return 0;
        }
    }

    return 1;
}

int clist_to_array(const CircularList *l, int *out, int size)
{
    Node *current;

    if (l == NULL || out == NULL || size != l->size)
        return 0;
    if (l->tail == NULL)
        return 1; /* empty list: nothing to copy */

    /* There is no NULL at the end, so the loop counts the nodes */
    current = l->tail->next;
    for (int i = 0; i < l->size; i++)
    {
        out[i] = current->value;
        current = current->next;
    }

    return 1;
}

int clist_size(const CircularList *l)
{
    if (l == NULL)
        return 0;

    return l->size;
}

long long clist_memory_bytes(const CircularList *l)
{
    if (l == NULL)
        return 0;

    return (long long)sizeof(CircularList) + (long long)l->size * (long long)sizeof(Node);
}

void clist_print(const CircularList *l)
{
    Node *first;
    Node *current;

    if (l == NULL)
        return;
    if (l->tail == NULL)
    {
        printf("(lista vazia)\n");
        return;
    }

    /* Goes around the circle once: stops when it gets back to the first node */
    first = l->tail->next;
    current = first;
    do
    {
        printf("%d -> ", current->value);
        current = current->next;
    } while (current != first);
    printf("(volta ao %d)\n", first->value);
}

void clist_clear(CircularList *l)
{
    Node *current;
    Node *temp;

    if (l == NULL)
        return;
    if (l->tail == NULL)
        return; /* already empty */

    /* There is no NULL at the end: a while (current != NULL) would never stop.
       The loop frees exactly size nodes, starting at the first one. */
    current = l->tail->next;
    for (int i = 0; i < l->size; i++)
    {
        temp = current;
        current = current->next; /* saves the next node before freeing this one */
        mem_free(temp, sizeof(Node));
        temp = NULL;
    }

    l->tail = NULL;
    l->size = 0;
}

void clist_destroy(CircularList **l)
{
    if (l == NULL || *l == NULL)
        return;

    clist_clear(*l);
    mem_free(*l, sizeof(CircularList));
    *l = NULL;
}

/* ---------- Opening and closing the circle ---------- */

/* The sorts are the same as in the singly list (singly_list.c). Those algorithms stop
   when they find NULL: split_middle looks for the end of the list and the merge stops
   when one of the halves ends. In the circle there is no NULL, so they would never stop.
   Because of that the circle is opened before sorting and closed again after it. */

/* Breaks the link from the last node to the first one, so the list ends with NULL.
   Returns the first node. The list must not be empty. */
static Node *open_cycle(CircularList *l)
{
    Node *head = l->tail->next;

    l->tail->next = NULL;
    return head;
}

/* Walks to the last node of the list that starts at head (one pass, O(n)), links it
   back to head and makes it the new tail. head must not be NULL. */
static void close_cycle(CircularList *l, Node *head)
{
    Node *last = head;

    while (last->next != NULL)
        last = last->next;

    last->next = head;
    l->tail = last;
}

/* ---------- Insertion Sort (moving nodes) ---------- */

/* Same algorithm as slist_insertion_sort, on the open list that starts at head.
   Returns the new first node.
   The sorted part goes from head to sorted_tail. The node right after sorted_tail
   (current) is the next one to be inserted.
   - If current is not smaller than sorted_tail, it is already in place: the sorted part
     just grows by one node (1 comparison, no node moved).
   - Otherwise current is unlinked and inserted in the sorted part. There is no pointer
     to the previous node, so the search starts at head. Each node inserted in another
     position counts as 1 swap.
   Sorted data: n - 1 comparisons and 0 moves. Reversed data: every node goes to the
   head, 2 comparisons and 1 move per node. */
static Node *insertion_nodes(Node *head, Metrics *m)
{
    Node *sorted_tail;
    Node *current;
    Node *prev;

    sorted_tail = head;
    while (sorted_tail->next != NULL)
    {
        current = sorted_tail->next;

        m->comparisons++;
        if (sorted_tail->value <= current->value)
        {
            sorted_tail = current; /* already in place */
            continue;
        }

        /* Unlinks current: sorted_tail now points to the node after current */
        sorted_tail->next = current->next;

        m->comparisons++;
        if (current->value < head->value)
        {
            /* Smaller than all the sorted part: current becomes the new head */
            current->next = head;
            head = current;
        }
        else
        {
            /* prev stops at the last node with value <= current->value.
               The loop always stops before sorted_tail, because sorted_tail->value is
               greater than current->value, so prev->next is never NULL. */
            prev = head;
            while (1)
            {
                m->comparisons++;
                if (prev->next->value > current->value)
                    break;
                prev = prev->next;
            }

            /* Links current between prev and prev->next */
            current->next = prev->next;
            prev->next = current;
        }
        m->swaps++;
    }

    return head;
}

int clist_insertion_sort(CircularList *l, Metrics *m)
{
    Node *head;

    if (l == NULL || m == NULL)
        return 0;
    if (l->size < 2)
        return 1; /* empty list or only one node: already sorted */

    head = open_cycle(l);
    head = insertion_nodes(head, m);
    close_cycle(l, head);

    return 1;
}

/* ---------- Merge Sort (moving nodes) ---------- */

/* Splits the list that starts at head in two halves and returns the start of the
   second one. slow walks one node at a time and fast walks two, so when fast reaches
   the end (NULL), slow is in the middle. The first half is ended with NULL.
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

    return second;
}

/* Merges two sorted lists (a and b) into one and returns its first node.
   No node is allocated: the smaller front node is linked after tail each time.
   Each node linked this way counts as 1 swap. When one list ends, the rest of the
   other one is linked at once (those nodes do not move, so they are not counted).
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
    m->swaps++;
    tail = first;

    while (a != NULL && b != NULL)
    {
        m->comparisons++;
        if (a->value <= b->value)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
        m->swaps++;
    }

    /* Links what is left (only one of them is not NULL) */
    if (a != NULL)
        tail->next = a;
    else
        tail->next = b;

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
int clist_merge_sort(CircularList *l, Metrics *m)
{
    Node *head;

    if (l == NULL || m == NULL)
        return 0;
    if (l->size < 2)
        return 1; /* empty list or only one node: already sorted */

    head = open_cycle(l);
    head = merge_sort_nodes(head, m);
    close_cycle(l, head);

    return 1;
}

/* ---------- Algorithm table ---------- */

/* Pointer to a list sort function (same idea as SortFunction in sort.h). */
typedef int (*ListSortFunction)(CircularList *l, Metrics *m);

typedef struct {
    const char *name;
    ListSortFunction function;
} ListSortAlgorithm;

static const ListSortAlgorithm list_algorithms[CLIST_SORT_COUNT] = {
    {"Insertion Lista Circular", clist_insertion_sort},
    {"Merge Lista Circular", clist_merge_sort}
};

const char *clist_sort_name(int index)
{
    if (index < 0 || index >= CLIST_SORT_COUNT)
        return NULL;

    return list_algorithms[index].name;
}

int clist_sort_run(int index, const int *source, int size, CircularList *dest, Metrics *out)
{
    clock_t start, end;
    long long baseline;
    int ok;

    if (index < 0 || index >= CLIST_SORT_COUNT)
        return 0;
    if (source == NULL || dest == NULL || out == NULL || size <= 0)
        return 0;

    /* The list is built before the clock starts, so it is not part of the measured time */
    if (clist_from_array(dest, source, size) == 0)
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
