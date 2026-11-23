#include <limits.h>
#include "memory.h"
#include "queue.h"

struct Queue
{
    BatchTest *tests;
    int start;
    int count;
    int capacity;
};

int queue_create(int capacity, Queue **out)
{
    Queue *queue;

    if (out == NULL || capacity <= 0 || capacity > INT_MAX / (int)sizeof(BatchTest))
        return 0;

    queue = mem_alloc(sizeof(Queue));
    if (queue == NULL)
        return 0;

    queue->tests = mem_alloc(capacity * sizeof(BatchTest));
    if (queue->tests == NULL)
    {
        mem_free(queue, sizeof(Queue));
        return 0;
    }

    queue->start = 0;
    queue->count = 0;
    queue->capacity = capacity;
    *out = queue;
    return 1;
}

void queue_destroy(Queue **queue)
{
    if (queue == NULL || *queue == NULL)
        return;

    mem_free((*queue)->tests, (*queue)->capacity * sizeof(BatchTest));
    mem_free(*queue, sizeof(Queue));
    *queue = NULL;
}

int queue_enqueue(Queue *queue, BatchTest test)
{
    int end;

    if (queue == NULL || queue->count == queue->capacity)
        return 0;

    end = (queue->start + queue->count) % queue->capacity;
    queue->tests[end] = test;
    queue->count++;
    return 1;
}

int queue_dequeue(Queue *queue, BatchTest *out)
{
    if (queue == NULL || out == NULL || queue->count == 0)
        return 0;

    *out = queue->tests[queue->start];
    queue->start = (queue->start + 1) % queue->capacity;
    queue->count--;
    return 1;
}

int queue_count(const Queue *queue)
{
    if (queue == NULL)
        return 0;

    return queue->count;
}
