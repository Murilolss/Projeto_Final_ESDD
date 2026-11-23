#ifndef EXPORT_H
#define EXPORT_H

#include "metrics.h"

/* Export of every comparison, swap and write of one sort to a JSON file (T10).
   The format is described in contexto/formato_log.md: the initial array, the list of
   steps, the final array and the metrics. The web interface (T14) replays the steps
   from the initial array to animate the bars. */

/* Biggest array that can be exported.
   The number of steps grows with the square of N. The Bubble Sort makes about N*N
   comparisons even on random data (each pass compares the whole array and it needs
   almost N passes) plus about N*N/4 swaps. Measured with N = 1000: about 1.2 million
   steps (85 MB) for random data and 1.5 million steps (99 MB) for reversed data.
   With N = 10000 it would have 100 times more (about 120 million steps, 9 to 10 GB)
   and with N = 50000 2500 times more. Files that big take too long to write, do not
   open in the browser and could never be watched as an animation, so bigger arrays
   are not exported. */
#define EXPORT_MAX_SIZE 1000

/* Folder where the files are created. It must exist (the repository keeps it with a
   .gitkeep file) and the program must be run from the root folder of the project. */
#define EXPORT_FOLDER "logs"

typedef struct Exporter Exporter;

/* Creates the file logs/<algorithm>_n<size>_<YYYYMMDD>_<HHMMSS>.json and writes the
   beginning of the log: algorithm, kind of data, size and the initial array.
   Returns 1 on success and writes the new exporter in *out; returns 0 if the arguments
   are invalid, size > EXPORT_MAX_SIZE, there is no memory or the file cannot be created. */
int export_open(const char *algorithm, const char *data_kind, const int *initial, int size,
                Exporter **out);

/* Step function (same signature as StepFunction in sort.h).
   context must be the Exporter created by export_open. Writes one line per step. */
void export_step(int kind, int i, int j, int left_value, int right_value,
                 const int *array, int size, void *context);

/* Path of the file being written (e.g. "logs/bubble_sort_n10_20261121_153000.json"),
   or NULL if exporter is NULL. */
const char *export_path(const Exporter *exporter);

/* Writes the end of the log (final array and metrics), closes the file, frees the
   exporter and sets the caller's pointer to NULL.
   Returns 1 if the whole file was written; 0 if any write failed. */
int export_close(Exporter **exporter, const int *final, const Metrics *m);

#endif
