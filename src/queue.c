#include <stdint.h>
#include "memory.h"
#include "queue.h"

struct Queue
{
    BatchTest *tests;
    size_t start;
    size_t count;
    size_t capacity;
};

int queue_create(int capacity, Queue **out)
{
    Queue *queue;

    if (out == NULL || capacity <= 0 || (size_t)capacity > SIZE_MAX / sizeof(BatchTest))
        return 0;

    queue = mem_alloc(sizeof(Queue));
    if (queue == NULL)
        return 0;

    queue->tests = mem_alloc((size_t)capacity * sizeof(BatchTest));
    if (queue->tests == NULL)
    {
        mem_free(queue, sizeof(Queue));
        return 0;
    }

    queue->start = 0;
    queue->count = 0;
    queue->capacity = (size_t)capacity;
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
    size_t end;

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

    return (int)queue->count;
}
