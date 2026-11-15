#ifndef VECTOR_H
#define VECTOR_H

/* Allocates an int array (counted by memory.h). Returns NULL if size <= 0 or allocation fails. */
int *vector_create(int size);

/* Changes the array to new_size elements with realloc (the first values are kept).
   Returns 1 on success and updates *v; returns 0 on failure and *v is left unchanged. */
int vector_resize(int **v, int old_size, int new_size);

/* Fills the array with the values 1..size in random order (no repeated values).
   srand() must be called once in main before the first call. */
void vector_fill_random(int *v, int size);

void vector_print(const int *v, int size);

/* Frees the array (size elements) and sets the caller's pointer to NULL. */
void vector_destroy(int **v, int size);

#endif
