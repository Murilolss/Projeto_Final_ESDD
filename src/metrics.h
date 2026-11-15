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
} Metrics;

void metrics_init(Metrics *m, const char *name);
void metrics_print(const Metrics *m, int size);
void metrics_print_table(const Metrics *list, int count, int size);

#endif
