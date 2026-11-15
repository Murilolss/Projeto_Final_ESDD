#ifndef SORT_H
#define SORT_H

#include "metrics.h"

/* Number of algorithms in the algorithm table (sort.c). */
#define SORT_COUNT 7

/* Pointer to a sort function.
   A variable of type SortFunction stores the address of any function that receives
   (int *array, int size, Metrics *m) and returns nothing, e.g. SortFunction f = bubble_sort;
   Calling f(array, size, &m) runs the function it points to. */
typedef void (*SortFunction)(int *array, int size, Metrics *m);

/* Each algorithm sorts the array in place, counting comparisons and swaps in m. */
void bubble_sort(int *array, int size, Metrics *m);
void insertion_sort(int *array, int size, Metrics *m);
void merge_sort_iterative(int *array, int size, Metrics *m);
void merge_sort_recursive(int *array, int size, Metrics *m);
void quick_sort_first_pivot(int *array, int size, Metrics *m);
void quick_sort_last_pivot(int *array, int size, Metrics *m);
void selection_sort(int *array, int size, Metrics *m);

/* Name of the algorithm at position index (0 .. SORT_COUNT - 1), or NULL if index is invalid. */
const char *sort_name(int index);

/* Copies source into dest (both with size elements), sorts dest with the algorithm at
   position index and fills out with its metrics and time.
   Returns 1 on success, 0 on invalid arguments. */
int sort_run(int index, const int *source, int *dest, int size, Metrics *out);

#endif
