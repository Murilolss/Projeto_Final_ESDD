#ifndef BENCHMARK_H
#define BENCHMARK_H

/* Comparison of the contiguous array with the linked lists (singly, doubly and circular).
   For each kind of data (random, sorted and reversed) and each size of the table below,
   one array is filled once and every algorithm sorts exactly those values: the 7 array
   algorithms (sort.h) and the 2 algorithms of each list. One table is printed per
   (kind, size) with time, comparisons, swaps, memory of the structure and extra memory. */

/* Number of sizes in the size table (benchmark.c). */
#define BENCHMARK_SIZE_COUNT 3

/* Size at position index (0 .. BENCHMARK_SIZE_COUNT - 1), or 0 if index is invalid. */
int benchmark_size(int index);

/* Runs the whole comparison and prints the tables.
   Each row is printed as soon as its algorithm ends, so the user sees the progress.
   Returns 1 on success, 0 if there is not enough memory or an algorithm fails. */
int benchmark_run_all(void);

#endif
