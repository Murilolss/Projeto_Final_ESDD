#ifndef VECTOR_H
#define VECTOR_H

#include <limits.h> /* INT_MAX */

/* Biggest number of elements of an array.
   The size in bytes is size * sizeof(int), computed as size_t. With the 32-bit MinGW,
   size_t has only 4 bytes (up to about 4.29 billion): with size = 1100000000 the
   product (4.4 billion) wraps around to about 105 MB, malloc succeeds with that smaller
   block and filling the array writes past its end (crash). With size up to
   INT_MAX / sizeof(int) (536870911), the product is at most INT_MAX and never wraps. */
#define VECTOR_MAX_SIZE (INT_MAX / (int)sizeof(int))

/* Kinds of data used to fill the array (see vector_fill) */
#define FILL_RANDOM 1   /* 1..size in random order */
#define FILL_SORTED 2   /* 1, 2, ..., size (best case of Insertion Sort) */
#define FILL_REVERSED 3 /* size, ..., 2, 1 (worst case of Insertion and Bubble Sort) */

/* Allocates an int array (counted by memory.h). Returns NULL if size <= 0,
   size > VECTOR_MAX_SIZE or the allocation fails. */
int *vector_create(int size);

/* Changes the array to new_size elements with realloc (the first values are kept).
   Returns 1 on success and updates *v; returns 0 on failure (including
   new_size > VECTOR_MAX_SIZE) and *v is left unchanged. */
int vector_resize(int **v, int old_size, int new_size);

/* Fills the array with the values 1..size in random order (no repeated values).
   srand() must be called once in main before the first call. */
void vector_fill_random(int *v, int size);

/* Fills the array with 1, 2, ..., size (already sorted). */
void vector_fill_sorted(int *v, int size);

/* Fills the array with size, ..., 2, 1 (sorted in reverse order). */
void vector_fill_reversed(int *v, int size);

/* Fills the array with the kind of data chosen (FILL_RANDOM, FILL_SORTED or FILL_REVERSED).
   Returns 1 on success; returns 0 if v is NULL, size <= 0 or the kind is invalid. */
int vector_fill(int *v, int size, int kind);

/* Name of the kind of data, shown to the user. Returns NULL if the kind is invalid. */
const char *vector_fill_name(int kind);

void vector_print(const int *v, int size);

/* Frees the array (size elements) and sets the caller's pointer to NULL. */
void vector_destroy(int **v, int size);

#endif
