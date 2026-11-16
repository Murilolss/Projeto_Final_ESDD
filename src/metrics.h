#ifndef METRICS_H
#define METRICS_H

/* Performance report of one sort execution.
   The struct is public (not opaque) because it is a plain record of values:
   the client declares arrays of it on the stack, e.g. Metrics results[7]. */
typedef struct {
    char name[30];
    long long comparisons;
    long long swaps;
    double time_ms;
    long long memory_bytes; /* peak of extra heap memory used by the algorithm */
} Metrics;

void metrics_init(Metrics *m, const char *name);
/* data_kind is the name of the kind of data that was sorted (e.g. "Ordenado"); it can be NULL. */
void metrics_print(const Metrics *m, int size, const char *data_kind);
void metrics_print_table(const Metrics *list, int count, int size, const char *data_kind);

#endif
