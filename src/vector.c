#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "search.h"

static int random_number(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int *vector_create(int size)
{
    int *v;

    if (size <= 0)
        return NULL;

    v = (int *)malloc(size * sizeof(int));
    if (v == NULL)
        return NULL;

    return v;
}

/* TODO(T03): srand() is never called, so every run produces the same numbers.
   TODO(T03): the first loop searches positions that were not initialized yet, and the
   second loop overwrites the unique values with rand 1..512 (duplicates).
   TODO(T03): there are only 2048 unique values, so size > 2048 never leaves the first loop. */
void vector_fill_random(int *v, int size)
{
    int value, n = 0;

    if (v == NULL || size <= 0)
        return;

    while (n < size)
    {
        value = random_number(1, 2048);
        if (sequential_search(v, size, value) == -1)
        {
            v[n] = value;
            n++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        v[i] = random_number(1, 512);
    }
}

void vector_print(const int *v, int size)
{
    if (v == NULL)
        return;

    printf("{");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", v[i]);
    }
    printf("}\n");
}

void vector_destroy(int **v)
{
    if (v == NULL || *v == NULL)
        return;

    free(*v);
    *v = NULL;
}
