#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "sort.h"
#include "metrics.h"
#include "memory.h"

#define OPTION_SORT 1
#define OPTION_SHOW 2
#define OPTION_COMPARE 3
#define OPTION_RESIZE 4
#define OPTION_EXIT 5

static void clear_input(void);
static void wait_enter(void);
static int menu_sort(const int *vector, int size);
static void menu_compare_all(const int *vector, int size);
static void menu_resize(int **vector, int *size);

int main()
{
    int size = 0;
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

    numbers = vector_create(size);
    if (numbers == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    vector_fill_random(numbers, size);

    do
    {
        system("cls");
        printf("---- Selecione uma opcao ----\n");
        printf("%d - Metodos de ordenacao\n", OPTION_SORT);
        printf("%d - Mostrar vetor\n", OPTION_SHOW);
        printf("%d - Comparar todos os algoritmos\n", OPTION_COMPARE);
        printf("%d - Alterar tamanho do vetor\n", OPTION_RESIZE);
        printf("%d - Encerrar programa\n", OPTION_EXIT);
        printf("-----------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        scanf("%d", &choice);
        clear_input();

        switch (choice)
        {
        case OPTION_SORT:
            if (menu_sort(numbers, size) == 1)
                choice = OPTION_EXIT; /* the user chose Exit inside the submenu */
            break;

        case OPTION_SHOW:
            system("cls");
            printf("\nVetor: ");
            vector_print(numbers, size);
            printf("\nMemoria do vetor: %d x %d = %lld bytes\n",
                   size, (int)sizeof(int), (long long)size * (long long)sizeof(int));
            printf("Memoria alocada no programa: %lld bytes\n", mem_current());
            wait_enter();
            break;

        case OPTION_COMPARE:
            system("cls");
            menu_compare_all(numbers, size);
            break;

        case OPTION_RESIZE:
            system("cls");
            menu_resize(&numbers, &size);
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

/* Menu built from the algorithm table: option i + 1 runs the algorithm at index i.
   Returns 1 if the user chose Exit, 0 if the user chose Back. */
static int menu_sort(const int *vector, int size)
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
                metrics_print(&m, size);
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

/* Runs every algorithm of the table on the same array and shows all results together. */
static void menu_compare_all(const int *vector, int size)
{
    Metrics results[SORT_COUNT];
    int count = 0;
    int *copy;

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

    metrics_print_table(results, count, size);
    wait_enter();
}

/* Asks for a new size, resizes the array with realloc and fills it again
   with a new random permutation of 1..new size. */
static void menu_resize(int **vector, int *size)
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
    vector_fill_random(*vector, *size);

    printf("\nVetor realocado com %d itens e preenchido de novo.\n", *size);
    printf("Memoria alocada no programa: %lld -> %lld bytes\n", before, mem_current());
    wait_enter();
}
