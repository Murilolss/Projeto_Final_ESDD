#ifndef VECTOR_H
#define VECTOR_H

/* Allocates an int array with malloc. Returns NULL if size <= 0 or allocation fails. */
int *vector_create(int size);

/* Fills the array with the values 1..size in random order (no repeated values).
   srand() must be called once in main before the first call. */
void vector_fill_random(int *v, int size);

void vector_print(const int *v, int size);

/* Frees the array and sets the caller's pointer to NULL. */
void vector_destroy(int **v);

#endif
