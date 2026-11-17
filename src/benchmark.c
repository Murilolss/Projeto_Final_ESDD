#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include "benchmark.h"
#include "vector.h"
#include "sort.h"
#include "metrics.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "circular_list.h"

#define BENCHMARK_KIND_COUNT 3

/* Sizes and kinds of data used in the comparison (one table for each pair). */
static const int sizes[BENCHMARK_SIZE_COUNT] = {1000, 10000, 50000};
static const int kinds[BENCHMARK_KIND_COUNT] = {FILL_RANDOM, FILL_SORTED, FILL_REVERSED};

static void print_header(int kind, int size);
static void print_row(const char *structure, const Metrics *m, long long structure_bytes);
static void print_failure(const char *structure, const char *name);
static void print_footer(void);
static int run_table(int kind, int size, SinglyList *slist, DoublyList *dlist, CircularList *clist);

int benchmark_size(int index)
{
    if (index < 0 || index >= BENCHMARK_SIZE_COUNT)
        return 0;

    return sizes[index];
}

int benchmark_run_all(void)
{
    SinglyList *slist;
    DoublyList *dlist;
    CircularList *clist;
    int ok = 1;

    /* The three lists are created once and rebuilt by each *_sort_run */
    slist = slist_create();
    dlist = dlist_create();
    clist = clist_create();
    if (slist == NULL || dlist == NULL || clist == NULL)
    {
        /* destroy does nothing for the ones that are NULL */
        slist_destroy(&slist);
        dlist_destroy(&dlist);
        clist_destroy(&clist);
        return 0;
    }

    for (int k = 0; k < BENCHMARK_KIND_COUNT; k++)
    {
        for (int s = 0; s < BENCHMARK_SIZE_COUNT; s++)
        {
            if (run_table(kinds[k], sizes[s], slist, dlist, clist) == 0)
                ok = 0;
        }
    }

    slist_destroy(&slist);
    dlist_destroy(&dlist);
    clist_destroy(&clist);
    return ok;
}

/* Fills one array with the kind of data chosen and runs every algorithm on those values.
   Returns 1 if every algorithm ran, 0 otherwise. */
static int run_table(int kind, int size, SinglyList *slist, DoublyList *dlist, CircularList *clist)
{
    int *source;
    int *copy;
    long long vector_bytes = (long long)size * (long long)sizeof(int);
    int ok = 1;
    Metrics m;

    source = vector_create(size);
    copy = vector_create(size);
    if (source == NULL || copy == NULL)
    {
        printf("\nErro ao alocar memoria para N = %d.\n", size);
        vector_destroy(&source, size);
        vector_destroy(&copy, size);
        return 0;
    }

    /* Filled only once: every algorithm below receives exactly these values */
    vector_fill(source, size, kind);

    print_header(kind, size);

    /* Contiguous array: sort_run copies source into copy and sorts the copy */
    for (int i = 0; i < SORT_COUNT; i++)
    {
        if (sort_run(i, source, copy, size, &m) == 1)
            print_row("Vetor", &m, vector_bytes);
        else
        {
            print_failure("Vetor", sort_name(i));
            ok = 0;
        }
    }
    vector_destroy(&copy, size);

    /* Linked lists: each *_sort_run rebuilds the list with the values of source.
       The nodes are freed (clear) before the next structure is measured. */
    for (int i = 0; i < SLIST_SORT_COUNT; i++)
    {
        if (slist_sort_run(i, source, size, slist, &m) == 1)
            print_row("Simples", &m, slist_memory_bytes(slist));
        else
        {
            print_failure("Simples", slist_sort_name(i));
            ok = 0;
        }
    }
    slist_clear(slist);

    for (int i = 0; i < DLIST_SORT_COUNT; i++)
    {
        if (dlist_sort_run(i, source, size, dlist, &m) == 1)
            print_row("Dupla", &m, dlist_memory_bytes(dlist));
        else
        {
            print_failure("Dupla", dlist_sort_name(i));
            ok = 0;
        }
    }
    dlist_clear(dlist);

    for (int i = 0; i < CLIST_SORT_COUNT; i++)
    {
        if (clist_sort_run(i, source, size, clist, &m) == 1)
            print_row("Circular", &m, clist_memory_bytes(clist));
        else
        {
            print_failure("Circular", clist_sort_name(i));
            ok = 0;
        }
    }
    clist_clear(clist);

    print_footer();
    vector_destroy(&source, size);
    return ok;
}

static void print_header(int kind, int size)
{
    printf("\n========================================= Vetor x Listas =========================================\n");
    printf("Dados: %s    Itens: %d\n\n", vector_fill_name(kind), size);
    printf("%-9s %-24s %11s %13s %13s %13s %11s\n",
           "Estrutura", "Algoritmo", "Tempo (ms)", "Comparacoes", "Trocas", "Estrutura (B)", "Extra (B)");
    printf("--------------------------------------------------------------------------------------------------\n");
    fflush(stdout);
}

/* structure_bytes = memory of the array or of the list (struct + nodes). */
static void print_row(const char *structure, const Metrics *m, long long structure_bytes)
{
    printf("%-9s %-24s %11.3f %13lld %13lld %13lld %11lld\n",
           structure, m->name, m->time_ms, m->comparisons, m->swaps,
           structure_bytes, m->memory_bytes);
    /* Shows the row right away: the slow algorithms can take several seconds */
    fflush(stdout);
}

static void print_failure(const char *structure, const char *name)
{
    printf("%-9s %-24s nao foi possivel executar (falta de memoria)\n", structure, name);
    fflush(stdout);
}

static void print_footer(void)
{
    printf("==================================================================================================\n");
    printf("Estrutura (B) = memoria do vetor ou da lista (struct + nos).\n");
    printf("Extra (B) = pico de memoria alocada pelo algoritmo durante a ordenacao.\n");
    printf("Nas listas, Trocas = nos religados em outra posicao (nenhum valor e copiado).\n");
    printf("Tempos muito curtos podem aparecer como 0 (precisao do clock()).\n");
    fflush(stdout);
}
