#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"
#include "memory.h"

/* Every sort function returns 1 on success and 0 on failure.
   Only the Merge Sorts can fail (they allocate memory); the others always return 1. */

/* ---------- Step notification ---------- */

/* Calls the step function of the observer, if there is one.
   With observer == NULL (benchmarks, comparison table) nothing happens. */
static void notify(const StepObserver *observer, int kind, int i, int j,
                   const int *array, int size)
{
    if (observer != NULL && observer->function != NULL)
        observer->function(kind, i, j, array, size, observer->context);
}

/* ---------- Bubble Sort ---------- */
int bubble_sort(int *array, int size, Metrics *m, const StepObserver *observer)
{
    int i, keep_going, aux;
    do
    {
        keep_going = 0;
        for (i = 0; i < size - 1; i++)
        {
            m->comparisons++;
            notify(observer, STEP_COMPARE, i, i + 1, array, size);
            if (array[i] > array[i + 1])
            {
                aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
                m->swaps++;
                notify(observer, STEP_SWAP, i, i + 1, array, size);
                keep_going = 1;
            }
        }
    } while (keep_going);

    return 1;
}

/* ---------- Insertion Sort ---------- */
int insertion_sort(int *array, int size, Metrics *m, const StepObserver *observer)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;

        /* Shifts the elements greater than key one position to the right.
           The key is no longer in the array (it was copied to the variable key),
           so the comparison is notified with the position it came from (i). */
        while (j >= 0)
        {
            m->comparisons++;
            notify(observer, STEP_COMPARE, j, i, array, size);
            if (array[j] <= key)
                break;
            array[j + 1] = array[j];
            m->swaps++;
            notify(observer, STEP_WRITE, j + 1, j, array, size);
            j = j - 1;
        }
        array[j + 1] = key; /* Inserts key in its correct position */
        if (j + 1 != i)     /* only when the key really moved */
            notify(observer, STEP_WRITE, j + 1, -1, array, size);
    }

    return 1;
}

/* ---------- Merge (shared by both Merge Sorts) ---------- */
static int min_int(int a, int b)
{
    return (a < b) ? a : b;
}

/* Merges array[left..middle] and array[middle+1..right], both already sorted.
   The two halves are copied to temporary arrays allocated on the heap (mem_alloc).
   This is the extra memory of the Merge Sort: n1 + n2 ints, at most size ints at once.
   size is the size of the whole array (only used to notify the steps).
   Returns 1 on success, 0 if there is not enough memory. */
static int merge(int *array, int size, int left, int middle, int right, Metrics *m,
                 const StepObserver *observer)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int *left_part;
    int *right_part;

    /* The iterative version can call merge with an empty right half (e.g. size 10,
       current_size 4, left 8). The left half is already sorted, so there is nothing to do.
       Returning here also avoids allocating 0 bytes (mem_alloc(0) returns NULL). */
    if (n1 <= 0 || n2 <= 0)
        return 1;

    left_part = (int *)mem_alloc(n1 * sizeof(int));
    if (left_part == NULL)
        return 0;

    right_part = (int *)mem_alloc(n2 * sizeof(int));
    if (right_part == NULL)
    {
        mem_free(left_part, n1 * sizeof(int));
        left_part = NULL;
        return 0;
    }

    for (i = 0; i < n1; i++)
        left_part[i] = array[left + i];
    for (j = 0; j < n2; j++)
        right_part[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    /* Copies the smaller of the two fronts back to the original array.
       The values compared are in the temporary halves, so the comparison is notified
       with the positions they had in the array before the merge (left + i and
       middle + 1 + j). */
    while (i < n1 && j < n2)
    {
        m->comparisons++;
        notify(observer, STEP_COMPARE, left + i, middle + 1 + j, array, size);
        if (left_part[i] <= right_part[j])
        {
            array[k] = left_part[i];
            i++;
        }
        else
        {
            array[k] = right_part[j];
            j++;
        }
        m->swaps++;
        notify(observer, STEP_WRITE, k, -1, array, size);
        k++;
    }

    /* Copies what is left, if anything */
    while (i < n1)
    {
        array[k] = left_part[i];
        m->swaps++;
        notify(observer, STEP_WRITE, k, -1, array, size);
        i++;
        k++;
    }
    while (j < n2)
    {
        array[k] = right_part[j];
        m->swaps++;
        notify(observer, STEP_WRITE, k, -1, array, size);
        j++;
        k++;
    }

    mem_free(left_part, n1 * sizeof(int));
    left_part = NULL;
    mem_free(right_part, n2 * sizeof(int));
    right_part = NULL;

    return 1;
}

/* ---------- Merge Sort (iterative) ---------- */
int merge_sort_iterative(int *array, int size, Metrics *m, const StepObserver *observer)
{
    /* current_size is the size of the subarrays being merged (1, 2, 4, 8...) */
    for (int current_size = 1; current_size <= size - 1; current_size = 2 * current_size)
    {
        /* left is the start of the left subarray */
        for (int left = 0; left < size - 1; left += 2 * current_size)
        {
            int middle = min_int(left + current_size - 1, size - 1);
            int right = min_int(left + 2 * current_size - 1, size - 1);

            if (merge(array, size, left, middle, right, m, observer) == 0)
                return 0;
        }
    }

    return 1;
}

/* ---------- Merge Sort (recursive) ---------- */
static int merge_sort_rec(int *array, int size, int left, int right, Metrics *m,
                          const StepObserver *observer)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        if (merge_sort_rec(array, size, left, middle, m, observer) == 0)
            return 0;
        if (merge_sort_rec(array, size, middle + 1, right, m, observer) == 0)
            return 0;

        return merge(array, size, left, middle, right, m, observer);
    }

    return 1;
}

int merge_sort_recursive(int *array, int size, Metrics *m, const StepObserver *observer)
{
    return merge_sort_rec(array, size, 0, size - 1, m, observer);
}

/* ---------- Quick Sort (first element as pivot) ---------- */
static int partition_first(int *array, int size, int start, int end, Metrics *m,
                           const StepObserver *observer)
{
    int pivot = array[start];
    int i = end + 1; /* Boundary of the elements greater than the pivot */
    int temp;

    /* Walks backwards down to the element right after the pivot.
       The pivot stays at position start until the end, so the comparison is
       notified with that position. */
    for (int j = end; j >= start + 1; j--)
    {
        m->comparisons++;
        notify(observer, STEP_COMPARE, j, start, array, size);
        if (array[j] > pivot)
        {
            i--;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            m->swaps++;
            notify(observer, STEP_SWAP, i, j, array, size);
        }
    }

    /* Moves the pivot to its correct position (i - 1) */
    temp = array[i - 1];
    array[i - 1] = array[start];
    array[start] = temp;
    m->swaps++;
    notify(observer, STEP_SWAP, i - 1, start, array, size);

    return (i - 1);
}

/* Only the smaller part goes to the recursion; the bigger part is sorted by the loop,
   which moves start or end and partitions again. Each recursive call gets at most half
   of the elements, so the recursion depth is at most log2(n).
   Without this, a sorted or reversed array puts the pivot at one end every time:
   the recursion goes n levels deep and overflows the stack (crash with n = 50000).
   The partitions are the same as in the plain version, so the comparisons and swaps
   are the same too. */
static void quick_sort_first_rec(int *array, int size, int start, int end, Metrics *m,
                                 const StepObserver *observer)
{
    while (start < end)
    {
        int pivot = partition_first(array, size, start, end, m, observer);

        if (pivot - start < end - pivot)
        {
            /* left part is smaller */
            quick_sort_first_rec(array, size, start, pivot - 1, m, observer);
            start = pivot + 1;
        }
        else
        {
            /* right part is smaller */
            quick_sort_first_rec(array, size, pivot + 1, end, m, observer);
            end = pivot - 1;
        }
    }
}

int quick_sort_first_pivot(int *array, int size, Metrics *m, const StepObserver *observer)
{
    quick_sort_first_rec(array, size, 0, size - 1, m, observer);
    return 1;
}

/* ---------- Quick Sort (last element as pivot) ---------- */
static int partition_last(int *array, int size, int start, int end, Metrics *m,
                          const StepObserver *observer)
{
    int pivot = array[end];
    int i = start - 1;
    int temp;

    /* The pivot stays at position end until the end of the loop */
    for (int j = start; j <= end - 1; j++)
    {
        m->comparisons++;
        notify(observer, STEP_COMPARE, j, end, array, size);
        if (array[j] < pivot)
        {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            m->swaps++;
            notify(observer, STEP_SWAP, i, j, array, size);
        }
    }

    /* Moves the pivot to its correct position */
    temp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = temp;
    m->swaps++;
    notify(observer, STEP_SWAP, i + 1, end, array, size);

    return (i + 1);
}

/* Same idea as quick_sort_first_rec: recursion only on the smaller part. */
static void quick_sort_last_rec(int *array, int size, int start, int end, Metrics *m,
                                const StepObserver *observer)
{
    while (start < end)
    {
        int pivot = partition_last(array, size, start, end, m, observer);

        if (pivot - start < end - pivot)
        {
            /* left part is smaller */
            quick_sort_last_rec(array, size, start, pivot - 1, m, observer);
            start = pivot + 1;
        }
        else
        {
            /* right part is smaller */
            quick_sort_last_rec(array, size, pivot + 1, end, m, observer);
            end = pivot - 1;
        }
    }
}

int quick_sort_last_pivot(int *array, int size, Metrics *m, const StepObserver *observer)
{
    quick_sort_last_rec(array, size, 0, size - 1, m, observer);
    return 1;
}

/* ---------- Selection Sort ---------- */
int selection_sort(int *array, int size, Metrics *m, const StepObserver *observer)
{
    int i, j, min_pos, aux;
    for (i = 0; i < size - 1; i++)
    {
        min_pos = i;
        for (j = i + 1; j < size; j++)
        {
            m->comparisons++;
            notify(observer, STEP_COMPARE, j, min_pos, array, size);
            if (array[j] < array[min_pos])
                min_pos = j;
        }
        if (i != min_pos)
        {
            aux = array[i];
            array[i] = array[min_pos];
            array[min_pos] = aux;
            m->swaps++;
            notify(observer, STEP_SWAP, i, min_pos, array, size);
        }
    }

    return 1;
}

/* ---------- Algorithm table ---------- */

/* One row of the table: the name shown in the menu and the function that sorts. */
typedef struct {
    const char *name;
    SortFunction function;
} SortAlgorithm;

/* To add an algorithm: write the function, add one row here and update SORT_COUNT. */
static const SortAlgorithm algorithms[SORT_COUNT] = {
    {"Bubble Sort", bubble_sort},
    {"Insertion Sort", insertion_sort},
    {"Merge Sort Iterativo", merge_sort_iterative},
    {"Merge Sort Recursivo", merge_sort_recursive},
    {"Quick Sort Pivo Inicio", quick_sort_first_pivot},
    {"Quick Sort Pivo Fim", quick_sort_last_pivot},
    {"Selection Sort", selection_sort}
};

const char *sort_name(int index)
{
    if (index < 0 || index >= SORT_COUNT)
        return NULL;

    return algorithms[index].name;
}

int sort_run(int index, const int *source, int *dest, int size, Metrics *out)
{
    /* Nobody watches the steps: the sort runs at full speed */
    return sort_run_steps(index, source, dest, size, out, NULL);
}

int sort_run_steps(int index, const int *source, int *dest, int size, Metrics *out,
                   const StepObserver *observer)
{
    clock_t start, end;
    long long baseline;
    int ok;

    if (index < 0 || index >= SORT_COUNT)
        return 0;
    if (source == NULL || dest == NULL || out == NULL || size <= 0)
        return 0;
    if (algorithms[index].function == NULL)
        return 0;

    /* The copy is made before the clock starts, so it is not part of the measured time */
    memcpy(dest, source, size * sizeof(int));
    metrics_init(out, algorithms[index].name);

    /* Extra memory = highest amount allocated during the sort minus what was already
       allocated before it (the vectors themselves). The recursion stack is not counted:
       it is not heap memory. */
    mem_reset_peak();
    baseline = mem_current();

    start = clock();
    ok = algorithms[index].function(dest, size, out, observer);
    end = clock();

    out->time_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    out->memory_bytes = mem_peak() - baseline;
    return ok;
}
