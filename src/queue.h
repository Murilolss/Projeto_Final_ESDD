#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue;

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
