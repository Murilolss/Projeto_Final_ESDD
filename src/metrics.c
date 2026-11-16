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
    m->memory_bytes = 0;
}

void metrics_print(const Metrics *m, int size, const char *data_kind)
{
    if (m == NULL)
        return;
    if (data_kind == NULL)
        data_kind = "-";

    printf("\n===== Relatorio de Desempenho =====\n");
    printf("Algoritmo:    %s\n", m->name);
    printf("Itens:        %d\n", size);
    printf("Dados:        %s\n", data_kind);
    printf("Tempo:        %.3f ms\n", m->time_ms);
    printf("Comparacoes:  %lld\n", m->comparisons);
    printf("Trocas:       %lld\n", m->swaps);
    printf("Memoria extra: %lld bytes\n", m->memory_bytes);
    printf("===================================\n");
}

void metrics_print_table(const Metrics *list, int count, int size, const char *data_kind)
{
    if (list == NULL)
        return;
    if (data_kind == NULL)
        data_kind = "-";

    printf("\n============================ Metricas dos Metodos de Ordenacao ============================\n");
    printf("Itens no vetor: %d\n", size);
    printf("Dados: %s\n\n", data_kind);
    printf("%-22s %12s %15s %15s %14s\n", "Algoritmo", "Tempo (ms)", "Comparacoes", "Trocas", "Memoria (B)");
    printf("-------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-22s %12.3f %15lld %15lld %14lld\n",
               list[i].name, list[i].time_ms, list[i].comparisons, list[i].swaps,
               list[i].memory_bytes);
    }
    printf("===========================================================================================\n");
    printf("Memoria (B) = pico de memoria extra alocada pelo algoritmo, alem do vetor.\n");
}
