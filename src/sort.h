#ifndef SORT_H
#define SORT_H

#include "metrics.h"

/* Number of algorithms in the algorithm table (sort.c). */
#define SORT_COUNT 7

/* ---------- Step notification (step-by-step mode, export and undo) ----------
   Every time a sort compares or changes the array it calls a function received by
   parameter (a pointer to function), telling what happened. The sort does not know
   what that function does: the step-by-step mode shows the array and waits for ENTER,
   the export (T10) writes one line of the log and the undo (T11) pushes the swap. */

/* Kinds of step */
#define STEP_COMPARE 1 /* compares values that came from positions i and j */
#define STEP_SWAP 2    /* the values of positions i and j were swapped */
#define STEP_WRITE 3   /* position i received a new value; j is the position it came from,
                          or -1 if it came from outside the array (the key of the
                          Insertion Sort or the temporary halves of the Merge Sort) */

/* Pointer to a step function. It is called right AFTER the step, so array already shows
   the result. size is the number of elements of the whole array.
   For STEP_COMPARE, left_value and right_value are the actual values compared.
   The values at their original positions i and j may have changed. The two value
   parameters are unused for STEP_SWAP and STEP_WRITE.
   context is any data the caller wants to receive back in every call (void * = pointer
   to any type); the step function converts it back to the right type. */
typedef void (*StepFunction)(int kind, int i, int j, int left_value, int right_value,
                             const int *array, int size, void *context);

/* A step function and the data it receives. A NULL StepObserver (or a NULL function)
   means "nobody is watching": the sort runs without notifying, as in the benchmarks. */
typedef struct {
    StepFunction function;
    void *context;
} StepObserver;

/* Pointer to a sort function.
   A variable of type SortFunction stores the address of any function that receives
   (int *array, int size, Metrics *m, const StepObserver *observer) and returns an int,
   e.g. SortFunction f = bubble_sort; calling f(array, size, &m, NULL) runs it. */
typedef int (*SortFunction)(int *array, int size, Metrics *m, const StepObserver *observer);

/* Each algorithm sorts the array in place, counting comparisons and swaps in m, and
   notifies every step to observer (which can be NULL).
   Returns 1 on success, 0 on failure (only the Merge Sorts can fail: out of memory). */
int bubble_sort(int *array, int size, Metrics *m, const StepObserver *observer);
int insertion_sort(int *array, int size, Metrics *m, const StepObserver *observer);
int merge_sort_iterative(int *array, int size, Metrics *m, const StepObserver *observer);
int merge_sort_recursive(int *array, int size, Metrics *m, const StepObserver *observer);
int quick_sort_first_pivot(int *array, int size, Metrics *m, const StepObserver *observer);
int quick_sort_last_pivot(int *array, int size, Metrics *m, const StepObserver *observer);
int selection_sort(int *array, int size, Metrics *m, const StepObserver *observer);

/* Name of the algorithm at position index (0 .. SORT_COUNT - 1), or NULL if index is invalid. */
const char *sort_name(int index);

/* Copies source into dest (both with size elements), sorts dest with the algorithm at
   position index and fills out with its metrics, time and extra memory (peak bytes).
   Returns 1 on success, 0 on invalid arguments or if the algorithm fails. */
int sort_run(int index, const int *source, int *dest, int size, Metrics *out);

/* Same as sort_run, but every step is notified to observer (which can be NULL).
   In the step-by-step mode the time also counts the pauses waiting for the user. */
int sort_run_steps(int index, const int *source, int *dest, int size, Metrics *out,
                   const StepObserver *observer);

#endif
