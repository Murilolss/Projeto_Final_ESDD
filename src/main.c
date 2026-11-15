#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "sort.h"
#include "metrics.h"

static void clear_input(void);
static void wait_enter(void);
static int menu_sort(const int *vector, int size);
static void menu_compare_all(const int *vector, int size);

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
        printf("1 - Metodos de ordenacao\n");
        printf("2 - Mostrar vetor\n");
        printf("3 - Comparar todos os algoritmos\n");
        printf("4 - Encerrar programa\n");
        printf("-----------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        scanf("%d", &choice);
        clear_input();

        switch (choice)
        {
        case 1:
            if (menu_sort(numbers, size) == 1)
                choice = 4; /* the user chose Exit inside the submenu */
            break;

        case 2:
            system("cls");
            printf("\nVetor: ");
            vector_print(numbers, size);
            wait_enter();
            break;

        case 3:
            system("cls");
            menu_compare_all(numbers, size);
            break;

        case 4:
            break;

        default:
            printf("\nOpcao invalida! Digite novamente.\n");
            wait_enter();
            break;
        }
    } while (choice != 4);

    printf("\nEncerrando o programa.\n");
    vector_destroy(&numbers);
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
            vector_destroy(&copy);
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

    vector_destroy(&copy);

    metrics_print_table(results, count, size);
    wait_enter();
}
