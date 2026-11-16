#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "singly_list.h"
#include "memory.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct SinglyList {
    Node *head; /* first node, or NULL if the list is empty */
    int size;   /* number of nodes */
};

SinglyList *slist_create(void)
{
    SinglyList *l = (SinglyList *)mem_alloc(sizeof(SinglyList));

    if (l == NULL)
        return NULL;

    l->head = NULL;
    l->size = 0;

    return l;
}

int slist_insert_front(SinglyList *l, int value)
{
    Node *new_node;

    if (l == NULL)
        return 0;

    new_node = (Node *)mem_alloc(sizeof(Node));
    if (new_node == NULL)
        return 0;

    new_node->value = value;
    new_node->next = l->head; /* the old first node comes after the new one */
    l->head = new_node;
    l->size++;

    return 1;
}

int slist_from_array(SinglyList *l, const int *v, int size)
{
    if (l == NULL || v == NULL || size <= 0)
        return 0;

    slist_clear(l);

    /* Inserting at the start from the last value to the first one keeps the order of
       the array and costs O(1) per value. Inserting at the end would walk the whole
       list each time (O(n) per value, about 1.25 billion steps with 50000 values). */
    for (int i = size - 1; i >= 0; i--)
    {
        if (slist_insert_front(l, v[i]) == 0)
        {
            slist_clear(l);
            return 0;
        }
    }

    return 1;
}

int slist_to_array(const SinglyList *l, int *out, int size)
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

int slist_size(const SinglyList *l)
{
    if (l == NULL)
        return 0;

    return l->size;
}

long long slist_memory_bytes(const SinglyList *l)
{
    if (l == NULL)
        return 0;

    return (long long)sizeof(SinglyList) + (long long)l->size * (long long)sizeof(Node);
}

void slist_print(const SinglyList *l)
{
    Node *current;

    if (l == NULL)
        return;

    current = l->head;
    while (current != NULL)
    {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void slist_clear(SinglyList *l)
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
    l->size = 0;
}

void slist_destroy(SinglyList **l)
{
    if (l == NULL || *l == NULL)
        return;

    slist_clear(*l);
    mem_free(*l, sizeof(SinglyList));
    *l = NULL;
}

/* ---------- Insertion Sort (moving nodes) ---------- */

/* The sorted part goes from head to sorted_tail. The node right after sorted_tail
   (current) is the next one to be inserted.
   - If current is not smaller than sorted_tail, it is already in place: the sorted part
     just grows by one node (1 comparison, no node moved).
   - Otherwise current is unlinked and inserted in the sorted part. The list has no
     pointer to the previous node, so the search starts at head (in the array the search
     goes from right to left). Each node inserted in another position counts as 1 swap.
   Sorted data: n - 1 comparisons and 0 moves (same as the array).
   Reversed data: every node goes to the head, 2 comparisons and 1 move per node
   (the array shifts all the elements: about n * n / 2 shifts). */
int slist_insertion_sort(SinglyList *l, Metrics *m)
{
    Node *sorted_tail;
    Node *current;
    Node *prev;

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

        /* Unlinks current: sorted_tail now points to the node after current */
        sorted_tail->next = current->next;

        m->comparisons++;
        if (current->value < l->head->value)
        {
            /* Smaller than all the sorted part: current becomes the new head */
            current->next = l->head;
            l->head = current;
        }
        else
        {
            /* prev stops at the last node with value <= current->value.
               The loop always stops before sorted_tail, because sorted_tail->value is
               greater than current->value, so prev->next is never NULL. */
            prev = l->head;
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

    return 1;
}

/* ---------- Merge Sort (moving nodes) ---------- */

/* Splits the list that starts at head in two halves and returns the start of the
   second one. slow walks one node at a time and fast walks two, so when fast reaches
   the end, slow is in the middle. The first half is ended with NULL.
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
int slist_merge_sort(SinglyList *l, Metrics *m)
{
    if (l == NULL || m == NULL)
        return 0;

    l->head = merge_sort_nodes(l->head, m);
    return 1;
}

/* ---------- Algorithm table ---------- */

/* Pointer to a list sort function (same idea as SortFunction in sort.h). */
typedef int (*ListSortFunction)(SinglyList *l, Metrics *m);

typedef struct {
    const char *name;
    ListSortFunction function;
} ListSortAlgorithm;

static const ListSortAlgorithm list_algorithms[SLIST_SORT_COUNT] = {
    {"Insertion Lista Simples", slist_insertion_sort},
    {"Merge Lista Simples", slist_merge_sort}
};

const char *slist_sort_name(int index)
{
    if (index < 0 || index >= SLIST_SORT_COUNT)
        return NULL;

    return list_algorithms[index].name;
}

int slist_sort_run(int index, const int *source, int size, SinglyList *dest, Metrics *out)
{
    clock_t start, end;
    long long baseline;
    int ok;

    if (index < 0 || index >= SLIST_SORT_COUNT)
        return 0;
    if (source == NULL || dest == NULL || out == NULL || size <= 0)
        return 0;

    /* The list is built before the clock starts, so it is not part of the measured time */
    if (slist_from_array(dest, source, size) == 0)
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
