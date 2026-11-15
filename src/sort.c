#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

/* ---------- Bubble Sort ---------- */
void bubble_sort(int *array, int size, Metrics *m)
{
    int i, keep_going, aux;
    do
    {
        keep_going = 0;
        for (i = 0; i < size - 1; i++)
        {
            m->comparisons++;
            if (array[i] > array[i + 1])
            {
                aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
                m->swaps++;
                keep_going = 1;
            }
        }
    } while (keep_going);
}

/* ---------- Insertion Sort ---------- */
void insertion_sort(int *array, int size, Metrics *m)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;

        /* Shifts the elements greater than key one position to the right */
        while (j >= 0)
        {
            m->comparisons++;
            if (array[j] <= key)
                break;
            array[j + 1] = array[j];
            m->swaps++;
            j = j - 1;
        }
        array[j + 1] = key; /* Inserts key in its correct position */
    }
}

/* ---------- Merge (shared by both Merge Sorts) ---------- */
static int min_int(int a, int b)
{
    return (a < b) ? a : b;
}

/* Merges array[left..middle] and array[middle+1..right], both already sorted. */
static void merge(int *array, int left, int middle, int right, Metrics *m)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* TODO(T03): VLAs live on the stack and overflow with large arrays; use malloc. */
    int left_part[n1];
    int right_part[n2];

    for (i = 0; i < n1; i++)
        left_part[i] = array[left + i];
    for (j = 0; j < n2; j++)
        right_part[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    /* Copies the smaller of the two fronts back to the original array */
    while (i < n1 && j < n2)
    {
        m->comparisons++;
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
        k++;
    }

    /* Copies what is left, if anything */
    while (i < n1)
    {
        array[k] = left_part[i];
        m->swaps++;
        i++;
        k++;
    }
    while (j < n2)
    {
        array[k] = right_part[j];
        m->swaps++;
        j++;
        k++;
    }
}

/* ---------- Merge Sort (iterative) ---------- */
void merge_sort_iterative(int *array, int size, Metrics *m)
{
    /* current_size is the size of the subarrays being merged (1, 2, 4, 8...) */
    for (int current_size = 1; current_size <= size - 1; current_size = 2 * current_size)
    {
        /* left is the start of the left subarray */
        for (int left = 0; left < size - 1; left += 2 * current_size)
        {
            int middle = min_int(left + current_size - 1, size - 1);
            int right = min_int(left + 2 * current_size - 1, size - 1);

            merge(array, left, middle, right, m);
        }
    }
}

/* ---------- Merge Sort (recursive) ---------- */
static void merge_sort_rec(int *array, int left, int right, Metrics *m)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        merge_sort_rec(array, left, middle, m);
        merge_sort_rec(array, middle + 1, right, m);

        merge(array, left, middle, right, m);
    }
}

void merge_sort_recursive(int *array, int size, Metrics *m)
{
    merge_sort_rec(array, 0, size - 1, m);
}

/* ---------- Quick Sort (first element as pivot) ---------- */
static int partition_first(int *array, int start, int end, Metrics *m)
{
    int pivot = array[start];
    int i = end + 1; /* Boundary of the elements greater than the pivot */
    int temp;

    /* Walks backwards down to the element right after the pivot */
    for (int j = end; j >= start + 1; j--)
    {
        m->comparisons++;
        if (array[j] > pivot)
        {
            i--;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            m->swaps++;
        }
    }

    /* Moves the pivot to its correct position (i - 1) */
    temp = array[i - 1];
    array[i - 1] = array[start];
    array[start] = temp;
    m->swaps++;

    return (i - 1);
}

static void quick_sort_first_rec(int *array, int start, int end, Metrics *m)
{
    if (start < end)
    {
        int pivot = partition_first(array, start, end, m);
        quick_sort_first_rec(array, start, pivot - 1, m);
        quick_sort_first_rec(array, pivot + 1, end, m);
    }
}

void quick_sort_first_pivot(int *array, int size, Metrics *m)
{
    quick_sort_first_rec(array, 0, size - 1, m);
}

/* ---------- Quick Sort (last element as pivot) ---------- */
static int partition_last(int *array, int start, int end, Metrics *m)
{
    int pivot = array[end];
    int i = start - 1;
    int temp;

    for (int j = start; j <= end - 1; j++)
    {
        m->comparisons++;
        if (array[j] < pivot)
        {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            m->swaps++;
        }
    }

    /* Moves the pivot to its correct position */
    temp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = temp;
    m->swaps++;

    return (i + 1);
}

static void quick_sort_last_rec(int *array, int start, int end, Metrics *m)
{
    if (start < end)
    {
        int pivot = partition_last(array, start, end, m);
        quick_sort_last_rec(array, start, pivot - 1, m);
        quick_sort_last_rec(array, pivot + 1, end, m);
    }
}

void quick_sort_last_pivot(int *array, int size, Metrics *m)
{
    quick_sort_last_rec(array, 0, size - 1, m);
}

/* ---------- Selection Sort ---------- */
void selection_sort(int *array, int size, Metrics *m)
{
    int i, j, min_pos, aux;
    for (i = 0; i < size - 1; i++)
    {
        min_pos = i;
        for (j = i + 1; j < size; j++)
        {
            m->comparisons++;
            if (array[j] < array[min_pos])
                min_pos = j;
        }
        if (i != min_pos)
        {
            aux = array[i];
            array[i] = array[min_pos];
            array[min_pos] = aux;
            m->swaps++;
        }
    }
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
    clock_t start, end;

    if (index < 0 || index >= SORT_COUNT)
        return 0;
    if (source == NULL || dest == NULL || out == NULL || size <= 0)
        return 0;
    if (algorithms[index].function == NULL)
        return 0;

    /* The copy is made before the clock starts, so it is not part of the measured time */
    memcpy(dest, source, size * sizeof(int));
    metrics_init(out, algorithms[index].name);

    start = clock();
    algorithms[index].function(dest, size, out);
    end = clock();

    out->time_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    return 1;
}
