#include <stdlib.h>
#include "search.h"

int sequential_search(const int *array, int size, int value)
{
    int i = 0;

    if (array == NULL)
        return -1;

    /* TODO(T03): array[i] is read before checking i < size (reads one past the end). */
    while ((array[i] != value) && (i < size))
        i = i + 1;

    if (i < size)
        return i;
    else
        return -1;
}
