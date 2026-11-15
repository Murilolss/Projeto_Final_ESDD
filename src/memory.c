#include <stdlib.h>
#include "memory.h"

/* There is only one counter for the whole program, so it is kept in two static
   variables of this file instead of a struct: no other file can change them directly,
   only through the functions below. */
static long long current_bytes = 0;
static long long peak_bytes = 0;

/* Updates the peak after the counter grows. */
static void update_peak(void)
{
    if (current_bytes > peak_bytes)
        peak_bytes = current_bytes;
}

void *mem_alloc(size_t bytes)
{
    void *p;

    if (bytes == 0)
        return NULL;

    p = malloc(bytes);
    if (p == NULL)
        return NULL;

    current_bytes = current_bytes + (long long)bytes;
    update_peak();
    return p;
}

void *mem_realloc(void *p, size_t old_bytes, size_t new_bytes)
{
    void *new_p;

    if (new_bytes == 0)
        return NULL;

    new_p = realloc(p, new_bytes);
    if (new_p == NULL)
        return NULL; /* p was not freed by realloc, so the counter stays the same */

    current_bytes = current_bytes - (long long)old_bytes + (long long)new_bytes;
    update_peak();
    return new_p;
}

void mem_free(void *p, size_t bytes)
{
    if (p == NULL)
        return;

    free(p);
    current_bytes = current_bytes - (long long)bytes;
}

long long mem_current(void)
{
    return current_bytes;
}

long long mem_peak(void)
{
    return peak_bytes;
}

void mem_reset_peak(void)
{
    peak_bytes = current_bytes;
}
