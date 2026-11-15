#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <string.h>
#include "metrics.h"

void metrics_init(Metrics *m, const char *name)
{
    if (m == NULL || name == NULL)
        return;

    strncpy(m->name, name, sizeof(m->name) - 1);
    m->name[sizeof(m->name) - 1] = '\0';
    m->comparisons = 0;
    m->swaps = 0;
    m->time_ms = 0.0;
}

void metrics_print(const Metrics *m, int size)
{
    if (m == NULL)
        return;

    printf("\n===== Relatorio de Desempenho =====\n");
    printf("Algoritmo:    %s\n", m->name);
    printf("Itens:        %d\n", size);
    printf("Tempo:        %.3f ms\n", m->time_ms);
    printf("Comparacoes:  %lld\n", m->comparisons);
    printf("Trocas:       %lld\n", m->swaps);
    printf("===================================\n");
}

void metrics_print_table(const Metrics *list, int count, int size)
{
    if (list == NULL)
        return;

    printf("\n=================== Metricas dos Metodos de Ordenacao ===================\n");
    printf("Itens no vetor: %d\n\n", size);
    printf("%-22s %12s %15s %15s\n", "Algoritmo", "Tempo (ms)", "Comparacoes", "Trocas");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-22s %12.3f %15lld %15lld\n",
               list[i].name, list[i].time_ms, list[i].comparisons, list[i].swaps);
    }
    printf("=========================================================================\n");
}
