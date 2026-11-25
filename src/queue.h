#ifndef QUEUE_H
#define QUEUE_H

/* Static circular queue of the batch tests (T12).
   The tests are kept in an array of fixed capacity. start is the position of the first
   test and count is how many tests there are; the end is (start + count) % capacity,
   so the positions go back to 0 after the last one and no element is ever shifted.
   The struct is opaque: only queue.c knows its fields. */
typedef struct Queue Queue;

/* One test of the batch: the algorithm (index of the table in sort.h) and the size of
   the array that will be sorted. */
typedef struct
{
    int sort_index;
    int size;
} BatchTest;

/* Creates an empty queue of fixed capacity. Returns 0 on failure and leaves *out unchanged. */
int queue_create(int capacity, Queue **out);

/* Frees the queue and sets the caller's pointer to NULL. */
void queue_destroy(Queue **queue);

/* Adds a test at the end. Returns 0 if the queue is NULL or full. */
int queue_enqueue(Queue *queue, BatchTest test);

/* Removes the first test. Returns 0 if the queue is NULL or empty, or out is NULL. */
int queue_dequeue(Queue *queue, BatchTest *out);

/* Returns the number of queued tests, or 0 if the queue is NULL. */
int queue_count(const Queue *queue);

#endif
