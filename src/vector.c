#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "memory.h"

/* Random index in 0..max.
   On MinGW RAND_MAX is only 32767, so a single rand() never reaches positions above
   32767 in a vector of 50000. Two calls are combined into one bigger number:
   first * (RAND_MAX + 1) + second goes from 0 up to about 1 billion. */
static int random_index(int max)
{
    long big = (long)rand() * (RAND_MAX + 1L) + rand();
    return (int)(big % (max + 1));
}

int *vector_create(int size)
{
    int *v;

    if (size <= 0)
        return NULL;

    v = (int *)mem_alloc(size * sizeof(int));
    if (v == NULL)
        return NULL;

    return v;
}

int vector_resize(int **v, int old_size, int new_size)
{
    int *temp;

    if (v == NULL || *v == NULL || old_size <= 0 || new_size <= 0)
        return 0;

    /* The result goes to a temporary pointer: if realloc fails it returns NULL but
       the old block is still allocated. Writing *v = realloc(...) directly would lose
       the only pointer to that block (memory leak). */
    temp = (int *)mem_realloc(*v, old_size * sizeof(int), new_size * sizeof(int));
    if (temp == NULL)
        return 0;

    *v = temp;
    return 1;
}

void vector_fill_sorted(int *v, int size)
{
    if (v == NULL || size <= 0)
        return;

    for (int i = 0; i < size; i++)
    {
        v[i] = i + 1;
    }
}

void vector_fill_reversed(int *v, int size)
{
    if (v == NULL || size <= 0)
        return;

    /* Position 0 gets size, position size - 1 gets 1 */
    for (int i = 0; i < size; i++)
    {
        v[i] = size - i;
    }
}

/* Fills the array with the values 1..size, each one exactly once, in random order.
   It starts from the sorted array 1..size and shuffles it.
   Fisher-Yates shuffle: walks from the last position to the second one and swaps
   each position i with a random position j between 0 and i. */
void vector_fill_random(int *v, int size)
{
    int i, j, aux;

    if (v == NULL || size <= 0)
        return;

    vector_fill_sorted(v, size);

    for (i = size - 1; i > 0; i--)
    {
        j = random_index(i);
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

int vector_fill(int *v, int size, int kind)
{
    if (v == NULL || size <= 0)
        return 0;

    switch (kind)
    {
    case FILL_RANDOM:
        vector_fill_random(v, size);
        return 1;
    case FILL_SORTED:
        vector_fill_sorted(v, size);
        return 1;
    case FILL_REVERSED:
        vector_fill_reversed(v, size);
        return 1;
    default:
        return 0; /* unknown kind: the array is not changed */
    }
}

const char *vector_fill_name(int kind)
{
    switch (kind)
    {
    case FILL_RANDOM:
        return "Aleatorio";
    case FILL_SORTED:
        return "Ordenado";
    case FILL_REVERSED:
        return "Invertido";
    default:
        return NULL;
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

void vector_destroy(int **v, int size)
{
    if (v == NULL || *v == NULL)
        return;

    mem_free(*v, size * sizeof(int));
    *v = NULL;
}
