#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "sort.h"
#include "metrics.h"
#include "memory.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "circular_list.h"

#define OPTION_SORT 1
#define OPTION_SHOW 2
#define OPTION_COMPARE 3
#define OPTION_RESIZE 4
#define OPTION_KIND 5
#define OPTION_LIST 6
#define OPTION_EXIT 7

static void clear_input(void);
static void wait_enter(void);
static int read_data_kind(void);
static int menu_sort(const int *vector, int size, int data_kind);
static int menu_list_sort(const int *vector, int size, int data_kind);
static void menu_compare_all(const int *vector, int size, int data_kind);
static void menu_resize(int **vector, int *size, int data_kind);
static void menu_kind(int *vector, int size, int *data_kind);

int main()
{
    int size = 0;
    int data_kind;
    int choice;
    int *numbers;

    /* Seeds rand() once, with the current time, so each run gets different numbers */
    srand((unsigned)time(NULL));

    printf("Digite o tamanho do vetor: ");
    if (scanf("%d", &size) != 1 || size <= 0)
    {
        printf("Tamanho invalido.\n");
        return 1;
    }
    clear_input();

    data_kind = read_data_kind();
    if (data_kind == 0)
    {
        printf("Tipo de dados invalido.\n");
        return 1;
    }

    numbers = vector_create(size);
    if (numbers == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    vector_fill(numbers, size, data_kind);

    do
    {
        system("cls");
        printf("Vetor: %d itens, dados %s\n\n", size, vector_fill_name(data_kind));
        printf("---- Selecione uma opcao ----\n");
        printf("%d - Metodos de ordenacao\n", OPTION_SORT);
        printf("%d - Mostrar vetor\n", OPTION_SHOW);
        printf("%d - Comparar todos os algoritmos\n", OPTION_COMPARE);
        printf("%d - Alterar tamanho do vetor\n", OPTION_RESIZE);
        printf("%d - Alterar tipo dos dados\n", OPTION_KIND);
        printf("%d - Ordenar listas encadeadas\n", OPTION_LIST);
        printf("%d - Encerrar programa\n", OPTION_EXIT);
        printf("-----------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        scanf("%d", &choice);
        clear_input();

        switch (choice)
        {
        case OPTION_SORT:
            if (menu_sort(numbers, size, data_kind) == 1)
                choice = OPTION_EXIT; /* the user chose Exit inside the submenu */
            break;

        case OPTION_SHOW:
            system("cls");
            printf("\nDados: %s\n", vector_fill_name(data_kind));
            printf("Vetor: ");
            vector_print(numbers, size);
            printf("\nMemoria do vetor: %d x %d = %lld bytes\n",
                   size, (int)sizeof(int), (long long)size * (long long)sizeof(int));
            printf("Memoria alocada no programa: %lld bytes\n", mem_current());
            wait_enter();
            break;

        case OPTION_COMPARE:
            system("cls");
            menu_compare_all(numbers, size, data_kind);
            break;

        case OPTION_RESIZE:
            system("cls");
            menu_resize(&numbers, &size, data_kind);
            break;

        case OPTION_KIND:
            system("cls");
            menu_kind(numbers, size, &data_kind);
            break;

        case OPTION_LIST:
            if (menu_list_sort(numbers, size, data_kind) == 1)
                choice = OPTION_EXIT; /* the user chose Exit inside the submenu */
            break;

        case OPTION_EXIT:
            break;

        default:
            printf("\nOpcao invalida! Digite novamente.\n");
            wait_enter();
            break;
        }
    } while (choice != OPTION_EXIT);

    printf("\nEncerrando o programa.\n");
    vector_destroy(&numbers, size);

    /* Everything was freed, so this must be 0. Any other value means a memory leak. */
    printf("Memoria nao liberada: %lld bytes\n", mem_current());
    return 0;
}

/* Discards the rest of the line typed by the user. */
static void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void wait_enter(void)
{
    printf("\nPressione ENTER para continuar...");
    clear_input();
}

/* Asks the user for the kind of data.
   Returns FILL_RANDOM, FILL_SORTED or FILL_REVERSED, or 0 if the answer is invalid. */
static int read_data_kind(void)
{
    int kind = 0;

    printf("\n---- Tipo dos dados ----\n");
    printf("%d - %s\n", FILL_RANDOM, vector_fill_name(FILL_RANDOM));
    printf("%d - %s\n", FILL_SORTED, vector_fill_name(FILL_SORTED));
    printf("%d - %s\n", FILL_REVERSED, vector_fill_name(FILL_REVERSED));
    printf("------------------------\n");
    printf("Digite uma opcao: ");
    if (scanf("%d", &kind) != 1)
        kind = 0;
    clear_input();

    if (vector_fill_name(kind) == NULL)
        return 0;

    return kind;
}

/* Menu built from the algorithm table: option i + 1 runs the algorithm at index i.
   Returns 1 if the user chose Exit, 0 if the user chose Back. */
static int menu_sort(const int *vector, int size, int data_kind)
{
    int choice;
    int back_option = SORT_COUNT + 1;
    int exit_option = SORT_COUNT + 2;
    int *copy;
    Metrics m;

    copy = vector_create(size);
    if (copy == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        wait_enter();
        return 0;
    }

    while (1)
    {
        system("cls");
        printf("---- Selecione o algoritmo de ordenacao ----\n");
        for (int i = 0; i < SORT_COUNT; i++)
        {
            printf("%d - %s\n", i + 1, sort_name(i));
        }
        printf("%d - Voltar\n", back_option);
        printf("%d - Encerrar programa\n", exit_option);
        printf("--------------------------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        scanf("%d", &choice);
        clear_input();

        if (choice >= 1 && choice <= SORT_COUNT)
        {
            if (sort_run(choice - 1, vector, copy, size, &m) == 1)
            {
                printf("\nVetor ordenado: ");
                vector_print(copy, size);
                metrics_print(&m, size, vector_fill_name(data_kind));
            }
            else
            {
                printf("\nNao foi possivel executar o algoritmo.\n");
            }
            wait_enter();
        }
        else if (choice == back_option || choice == exit_option)
        {
            vector_destroy(&copy, size);
            return (choice == exit_option) ? 1 : 0;
        }
        else
        {
            printf("\nOpcao invalida! Digite novamente.\n");
            wait_enter();
        }
    }
}

/* Builds a linked list (singly, doubly or circular) with the values of the array and
   sorts it with the list algorithm chosen. The array itself is not changed.
   Options 1 .. SLIST_SORT_COUNT use the singly list; the next DLIST_SORT_COUNT options
   use the doubly list and the next CLIST_SORT_COUNT options use the circular list.
   Returns 1 if the user chose Exit, 0 if the user chose Back. */
static int menu_list_sort(const int *vector, int size, int data_kind)
{
    int choice;
    int first_doubly = SLIST_SORT_COUNT + 1; /* option of the first doubly list algorithm */
    int first_circular = first_doubly + DLIST_SORT_COUNT; /* first circular list algorithm */
    int back_option = first_circular + CLIST_SORT_COUNT;
    int exit_option = back_option + 1;
    long long vector_bytes = (long long)size * (long long)sizeof(int);
    SinglyList *slist;
    DoublyList *dlist;
    CircularList *clist;
    Metrics m;

    slist = slist_create();
    dlist = dlist_create();
    clist = clist_create();
    if (slist == NULL || dlist == NULL || clist == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        slist_destroy(&slist);
        dlist_destroy(&dlist);
        clist_destroy(&clist);
        wait_enter();
        return 0;
    }

    while (1)
    {
        system("cls");
        printf("---- Ordenar listas encadeadas ----\n");
        for (int i = 0; i < SLIST_SORT_COUNT; i++)
        {
            printf("%d - %s\n", i + 1, slist_sort_name(i));
        }
        for (int i = 0; i < DLIST_SORT_COUNT; i++)
        {
            printf("%d - %s\n", first_doubly + i, dlist_sort_name(i));
        }
        for (int i = 0; i < CLIST_SORT_COUNT; i++)
        {
            printf("%d - %s\n", first_circular + i, clist_sort_name(i));
        }
        printf("%d - Voltar\n", back_option);
        printf("%d - Encerrar programa\n", exit_option);
        printf("-----------------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        scanf("%d", &choice);
        clear_input();

        if (choice >= 1 && choice <= SLIST_SORT_COUNT)
        {
            if (slist_sort_run(choice - 1, vector, size, slist, &m) == 1)
            {
                printf("\nLista ordenada: ");
                slist_print(slist);
                metrics_print(&m, size, vector_fill_name(data_kind));
                printf("Memoria da lista: %lld bytes (vetor: %lld bytes)\n",
                       slist_memory_bytes(slist), vector_bytes);
            }
            else
            {
                printf("\nNao foi possivel executar o algoritmo.\n");
            }
            wait_enter();
        }
        else if (choice >= first_doubly && choice < first_doubly + DLIST_SORT_COUNT)
        {
            if (dlist_sort_run(choice - first_doubly, vector, size, dlist, &m) == 1)
            {
                printf("\nLista ordenada: ");
                dlist_print(dlist);
                printf("Do fim ao inicio: ");
                dlist_print_reverse(dlist);
                metrics_print(&m, size, vector_fill_name(data_kind));
                printf("Memoria da lista: %lld bytes (vetor: %lld bytes)\n",
                       dlist_memory_bytes(dlist), vector_bytes);
            }
            else
            {
                printf("\nNao foi possivel executar o algoritmo.\n");
            }
            wait_enter();
        }
        else if (choice >= first_circular && choice < first_circular + CLIST_SORT_COUNT)
        {
            if (clist_sort_run(choice - first_circular, vector, size, clist, &m) == 1)
            {
                printf("\nLista ordenada: ");
                clist_print(clist);
                metrics_print(&m, size, vector_fill_name(data_kind));
                printf("Memoria da lista: %lld bytes (vetor: %lld bytes)\n",
                       clist_memory_bytes(clist), vector_bytes);
            }
            else
            {
                printf("\nNao foi possivel executar o algoritmo.\n");
            }
            wait_enter();
        }
        else if (choice == back_option || choice == exit_option)
        {
            slist_destroy(&slist);
            dlist_destroy(&dlist);
            clist_destroy(&clist);
            return (choice == exit_option) ? 1 : 0;
        }
        else
        {
            printf("\nOpcao invalida! Digite novamente.\n");
            wait_enter();
        }
    }
}

/* Runs every algorithm of the table on the same array, then every list algorithm
   (singly, doubly and circular) on lists with the same values, and shows all results
   together. */
static void menu_compare_all(const int *vector, int size, int data_kind)
{
    Metrics results[SORT_COUNT + SLIST_SORT_COUNT + DLIST_SORT_COUNT + CLIST_SORT_COUNT];
    int count = 0;
    int *copy;
    SinglyList *list;
    DoublyList *dlist;
    CircularList *clist;

    copy = vector_create(size);
    if (copy == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        wait_enter();
        return;
    }

    for (int i = 0; i < SORT_COUNT; i++)
    {
        if (sort_run(i, vector, copy, size, &results[count]) == 1)
            count++;
    }

    vector_destroy(&copy, size);

    list = slist_create();
    if (list == NULL)
    {
        printf("Erro ao alocar memoria para a lista.\n");
    }
    else
    {
        for (int i = 0; i < SLIST_SORT_COUNT; i++)
        {
            if (slist_sort_run(i, vector, size, list, &results[count]) == 1)
                count++;
        }
        slist_destroy(&list);
    }

    dlist = dlist_create();
    if (dlist == NULL)
    {
        printf("Erro ao alocar memoria para a lista dupla.\n");
    }
    else
    {
        for (int i = 0; i < DLIST_SORT_COUNT; i++)
        {
            if (dlist_sort_run(i, vector, size, dlist, &results[count]) == 1)
                count++;
        }
        dlist_destroy(&dlist);
    }

    clist = clist_create();
    if (clist == NULL)
    {
        printf("Erro ao alocar memoria para a lista circular.\n");
    }
    else
    {
        for (int i = 0; i < CLIST_SORT_COUNT; i++)
        {
            if (clist_sort_run(i, vector, size, clist, &results[count]) == 1)
                count++;
        }
        clist_destroy(&clist);
    }

    metrics_print_table(results, count, size, vector_fill_name(data_kind));
    wait_enter();
}

/* Asks for a new size, resizes the array with realloc and fills it again
   with the current kind of data (random, sorted or reversed). */
static void menu_resize(int **vector, int *size, int data_kind)
{
    int new_size = 0;
    long long before = mem_current();

    printf("Tamanho atual: %d\n", *size);
    printf("Digite o novo tamanho do vetor: ");
    if (scanf("%d", &new_size) != 1 || new_size <= 0)
    {
        clear_input();
        printf("\nTamanho invalido.\n");
        wait_enter();
        return;
    }
    clear_input();

    if (vector_resize(vector, *size, new_size) == 0)
    {
        printf("\nErro ao realocar memoria. O vetor continua com %d itens.\n", *size);
        wait_enter();
        return;
    }

    *size = new_size;
    vector_fill(*vector, *size, data_kind);

    printf("\nVetor realocado com %d itens e preenchido de novo (dados %s).\n",
           *size, vector_fill_name(data_kind));
    printf("Memoria alocada no programa: %lld -> %lld bytes\n", before, mem_current());
    wait_enter();
}

/* Asks for a new kind of data and fills the array again (the size does not change). */
static void menu_kind(int *vector, int size, int *data_kind)
{
    int kind;

    printf("Tipo atual: %s\n", vector_fill_name(*data_kind));
    kind = read_data_kind();
    if (kind == 0 || vector_fill(vector, size, kind) == 0)
    {
        printf("\nTipo invalido. O vetor nao foi alterado.\n");
        wait_enter();
        return;
    }

    *data_kind = kind;
    printf("\nVetor preenchido de novo com dados %s.\n", vector_fill_name(*data_kind));
    wait_enter();
}
