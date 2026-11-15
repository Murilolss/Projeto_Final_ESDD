#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h> /* size_t */

/* Memory counter of the whole program.
   Every malloc, realloc and free of the project goes through these functions, which
   call the real ones and add or subtract the bytes from a counter.
   free() does not know the size of a block, so the caller passes it (bytes). */

/* malloc(bytes) and adds bytes to the counter. Returns NULL if bytes == 0 or it fails. */
void *mem_alloc(size_t bytes);

/* realloc(p, new_bytes). The counter changes only if realloc succeeds.
   Returns NULL on failure; in that case p is still valid and was not freed. */
void *mem_realloc(void *p, size_t old_bytes, size_t new_bytes);

/* free(p) and subtracts bytes from the counter. Does nothing if p is NULL.
   The caller must still set its own pointer to NULL. */
void mem_free(void *p, size_t bytes);

/* Bytes allocated right now. */
long long mem_current(void);

/* Largest value mem_current() reached since the last mem_reset_peak(). */
long long mem_peak(void);

/* Starts a new peak measurement: peak = current. */
void mem_reset_peak(void);

#endif
