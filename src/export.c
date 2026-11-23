#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "export.h"
#include "sort.h"
#include "memory.h"

#define EXPORT_PATH_SIZE 128

struct Exporter {
    FILE *file;
    char path[EXPORT_PATH_SIZE];
    int size;
    long long steps; /* steps written so far (to know when to put a comma) */
    int failed;      /* 1 = some write to the file failed */
};

/* Writes the algorithm name in the file name style: lowercase and '_' instead of spaces
   (e.g. "Quick Sort Pivo Fim" -> "quick_sort_pivo_fim"). dest has room for max chars. */
static void file_name_style(const char *name, char *dest, int max)
{
    int k = 0;

    for (int p = 0; name[p] != '\0' && k < max - 1; p++)
    {
        char c = name[p];
        if (c == ' ')
            c = '_';
        else if (c >= 'A' && c <= 'Z')
            c = c - 'A' + 'a';
        dest[k] = c;
        k++;
    }
    dest[k] = '\0';
}

/* 1 if a file with this path already exists (it can be opened for reading). */
static int file_exists(const char *path)
{
    FILE *f = fopen(path, "r");

    if (f == NULL)
        return 0;
    fclose(f);
    return 1;
}

/* Builds logs/<algorithm>_n<size>_<date>_<time>.json in path.
   Two exports in the same second would get the same name, so if the file already
   exists a number is added at the end (_2, _3, ...) and no log is overwritten. */
static void build_path(const char *algorithm, int size, char *path)
{
    char name[48];
    char stamp[20];
    time_t now = time(NULL);
    int number = 2;

    file_name_style(algorithm, name, (int)sizeof(name));
    strftime(stamp, sizeof(stamp), "%Y%m%d_%H%M%S", localtime(&now));

    snprintf(path, EXPORT_PATH_SIZE, "%s/%s_n%d_%s.json", EXPORT_FOLDER, name, size, stamp);
    while (file_exists(path))
    {
        snprintf(path, EXPORT_PATH_SIZE, "%s/%s_n%d_%s_%d.json",
                 EXPORT_FOLDER, name, size, stamp, number);
        number++;
    }
}

/* Writes a JSON list: [v0, v1, ...]. */
static void write_array(Exporter *exporter, const int *array, int size)
{
    fprintf(exporter->file, "[");
    for (int p = 0; p < size; p++)
    {
        if (p > 0)
            fprintf(exporter->file, ", ");
        fprintf(exporter->file, "%d", array[p]);
    }
    fprintf(exporter->file, "]");
}

int export_open(const char *algorithm, const char *data_kind, const int *initial, int size,
                Exporter **out)
{
    Exporter *exporter;

    if (algorithm == NULL || data_kind == NULL || initial == NULL || out == NULL)
        return 0;
    if (size <= 0 || size > EXPORT_MAX_SIZE)
        return 0;

    exporter = (Exporter *)mem_alloc(sizeof(Exporter));
    if (exporter == NULL)
        return 0;

    build_path(algorithm, size, exporter->path);
    exporter->file = fopen(exporter->path, "w");
    if (exporter->file == NULL)
    {
        mem_free(exporter, sizeof(Exporter));
        exporter = NULL;
        return 0;
    }

    exporter->size = size;
    exporter->steps = 0;
    exporter->failed = 0;

    /* The names come from the program itself (algorithm table and kinds of data) and
       have no quotes or backslashes, so they can be written between quotes as they are. */
    fprintf(exporter->file, "{\n");
    fprintf(exporter->file, "  \"algorithm\": \"%s\",\n", algorithm);
    fprintf(exporter->file, "  \"data_kind\": \"%s\",\n", data_kind);
    fprintf(exporter->file, "  \"size\": %d,\n", size);
    fprintf(exporter->file, "  \"initial\": ");
    write_array(exporter, initial, size);
    fprintf(exporter->file, ",\n");
    fprintf(exporter->file, "  \"steps\": [\n");

    *out = exporter;
    return 1;
}

void export_step(int kind, int i, int j, int left_value, int right_value,
                 const int *array, int size, void *context)
{
    /* context is the Exporter the caller put in the StepObserver */
    Exporter *exporter = (Exporter *)context;
    int written;

    if (exporter == NULL || exporter->file == NULL || array == NULL || size != exporter->size)
        return;

    /* Only the three kinds of step in sort.h are written; any other is ignored here,
       before the comma, so the JSON stays valid */
    if (kind != STEP_COMPARE && kind != STEP_SWAP && kind != STEP_WRITE)
        return;

    /* Every step but the first starts with a comma closing the previous line */
    if (exporter->steps > 0)
        fprintf(exporter->file, ",\n");

    if (kind == STEP_COMPARE)
    {
        /* The values compared are saved too: in the Insertion and Merge Sorts the
           positions i and j may no longer hold them (see contexto/formato_log.md) */
        written = fprintf(exporter->file,
                          "    {\"type\": \"compare\", \"i\": %d, \"j\": %d, "
                          "\"value_i\": %d, \"value_j\": %d}",
                          i, j, left_value, right_value);
    }
    else if (kind == STEP_SWAP)
        written = fprintf(exporter->file, "    {\"type\": \"swap\", \"i\": %d, \"j\": %d}", i, j);
    else
        /* STEP_WRITE (checked above). The step comes after the write, so array[i] is
           already the new value */
        written = fprintf(exporter->file,
                          "    {\"type\": \"write\", \"i\": %d, \"j\": %d, \"value\": %d}",
                          i, j, array[i]);

    if (written < 0) /* fprintf returns a negative number when the write fails (disk full) */
        exporter->failed = 1;
    exporter->steps++;
}

const char *export_path(const Exporter *exporter)
{
    if (exporter == NULL)
        return NULL;

    return exporter->path;
}

int export_close(Exporter **exporter, const int *final, const Metrics *m)
{
    Exporter *e;
    int ok;

    if (exporter == NULL || *exporter == NULL)
        return 0;

    e = *exporter;

    /* Ends the list of steps (a new line only if there was at least one step) */
    if (e->steps > 0)
        fprintf(e->file, "\n");
    fprintf(e->file, "  ],\n");

    fprintf(e->file, "  \"final\": ");
    if (final != NULL)
        write_array(e, final, e->size);
    else
        fprintf(e->file, "[]");
    fprintf(e->file, ",\n");

    if (m != NULL)
        fprintf(e->file,
                "  \"metrics\": {\"comparisons\": %lld, \"swaps\": %lld, "
                "\"time_ms\": %.3f, \"memory_bytes\": %lld}\n",
                m->comparisons, m->swaps, m->time_ms, m->memory_bytes);
    else
        fprintf(e->file, "  \"metrics\": {}\n");
    fprintf(e->file, "}\n");

    /* ferror tells if any write failed; fclose returns EOF if the last data could not
       be saved to the disk */
    ok = !e->failed && !ferror(e->file);
    if (fclose(e->file) == EOF)
        ok = 0;
    e->file = NULL;

    mem_free(e, sizeof(Exporter));
    *exporter = NULL;
    return ok;
}
