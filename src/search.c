#include <stdlib.h>
#include "search.h"

int sequential_search(const int *array, int size, int value)
{
    int i = 0;

    if (array == NULL)
        return -1;

    /* i < size is tested first: when it is false, && stops and array[size] is never read */
    while ((i < size) && (array[i] != value))
        i = i + 1;

    if (i < size)
        return i;
    else
        return -1;
}
