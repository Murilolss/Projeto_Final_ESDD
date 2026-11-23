#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "queue.h"
#include "sort.h"
#include "metrics.h"
#include "memory.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "circular_list.h"
#include "benchmark.h"
#include "step_view.h"
#include "export.h"

#define OPTION_SORT 1
#define OPTION_SHOW 2
#define OPTION_COMPARE 3
#define OPTION_RESIZE 4
#define OPTION_KIND 5
#define OPTION_LIST 6
#define OPTION_BENCHMARK 7
#define OPTION_EXIT 8
#define OPTION_BATCH 9

#define BATCH_CAPACITY 10
#define BATCH_MAX_SIZE 50000 /* largest N of the vector x lists comparison */

static void clear_input(void);
static void wait_enter(void);
static int read_data_kind(void);
static int read_yes_no(const char *question);
static int run_sort(int index, const int *vector, int *copy, int size, int data_kind,
                    Metrics *m);
static int menu_sort(const int *vector, int size, int data_kind);
static int menu_list_sort(const int *vector, int size, int data_kind);
static void menu_compare_all(const int *vector, int size, int data_kind);
static void menu_resize(int **vector, int *size, int data_kind);
static void menu_kind(int *vector, int size, int *data_kind);
static void menu_benchmark(void);
static void menu_batch(int data_kind);

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
        printf("%d - Comparativo vetor x listas (N = %d, %d e %d)\n", OPTION_BENCHMARK,
               benchmark_size(0), benchmark_size(1), benchmark_size(2));
        printf("%d - Fila de testes em lote\n", OPTION_BATCH);
        printf("%d - Encerrar programa\n", OPTION_EXIT);
        printf("-----------------------------\n");
        printf("Digite uma opcao: ");
        choice = 0;
        if (scanf("%d", &choice) == EOF)
            break;
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

        case OPTION_BENCHMARK:
            system("cls");
            menu_benchmark();
            break;

        case OPTION_BATCH:
            system("cls");
            menu_batch(data_kind);
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

/* Asks a yes/no question. The user types Sim or Nao (or just S or N).
   Only the first letter is checked, so "sim", "Sim" and "S" are all yes.
   Returns 1 for yes and 0 for no; any other answer asks again. */
static int read_yes_no(const char *question)
{
    int answer;

    while (1)
    {
        printf("%s Digite Sim ou Nao: ", question);
        answer = getchar();
        if (answer == EOF)
            return 0;
        if (answer != '\n')
            clear_input();

        if (answer == 's' || answer == 'S')
            return 1;
        if (answer == 'n' || answer == 'N')
            return 0;

        printf("Resposta invalida.\n");
    }
}

/* Data received by step_both: the screen of the step-by-step mode and the log file. */
typedef struct {
    StepView *view;
    Exporter *exporter;
} StepTargets;

/* Step function used when the step-by-step mode and the export are both on.
   A StepObserver holds only one function, so this one passes the same step to the
   two others: first it is written to the log, then it is shown on the screen. */
static void step_both(int kind, int i, int j, int left_value, int right_value,
                      const int *array, int size, void *context)
{
    StepTargets *targets = (StepTargets *)context;

    export_step(kind, i, j, left_value, right_value, array, size, targets->exporter);
    step_view_show(kind, i, j, left_value, right_value, array, size, targets->view);
}

/* Asks if the steps should be exported to a JSON file (T10).
   Returns 1 only if the user said yes and the array is small enough. */
static int ask_export(int size)
{
    if (read_yes_no("Exportar log das comparacoes e trocas?") == 0)
        return 0;

    /* See EXPORT_MAX_SIZE in export.h: the file grows with the square of N */
    if (size > EXPORT_MAX_SIZE)
    {
        printf("\nExportacao disponivel so para vetores de ate %d itens (este tem %d).\n",
               EXPORT_MAX_SIZE, size);
        printf("O numero de passos cresce com o quadrado de N: com N = 10000 o Bubble Sort\n");
        printf("gera cerca de 120 milhoes de passos (arquivo de uns 6 GB), grande demais para\n");
        printf("gravar e para a interface animar. Use Alterar tamanho para um vetor menor.\n");
        printf("A ordenacao vai rodar sem exportar.\n");
        wait_enter();
        return 0;
    }

    return 1;
}

/* Sorts copy (a copy of vector) with the algorithm at index.
   Before sorting it asks for the step-by-step mode (T26) and for the export (T10).
   The sort calls the step function received by parameter inside the StepObserver:
   step_view_show (screen), export_step (log file), step_both (both) or none.
   Returns 1 on success, 0 if the algorithm fails. */
static int run_sort(int index, const int *vector, int *copy, int size, int data_kind,
                    Metrics *m)
{
    StepView *view = NULL;
    Exporter *exporter = NULL;
    StepTargets targets;
    StepObserver observer;
    int step_mode;
    int export_on;
    int ok;

    step_mode = read_yes_no("Executar passo a passo?");
    export_on = ask_export(size);

    if (export_on == 1 &&
        export_open(sort_name(index), vector_fill_name(data_kind), vector, size, &exporter) == 0)
    {
        printf("\nNao foi possivel criar o arquivo na pasta %s.\n", EXPORT_FOLDER);
        printf("Rode o programa a partir da pasta raiz do projeto (onde fica a pasta %s).\n",
               EXPORT_FOLDER);
        printf("A ordenacao vai rodar sem exportar.\n");
        wait_enter();
        export_on = 0;
    }

    if (step_mode == 1)
    {
        if (size > STEP_VIEW_FULL_SIZE)
            printf("Vetor com mais de %d itens: a tela mostra so as posicoes perto de cada passo.\n"
                   "Digite f + ENTER a qualquer momento para ir ate o fim.\n",
                   STEP_VIEW_FULL_SIZE);

        if (step_view_create(sort_name(index), read_yes_no("Pausar tambem nas comparacoes?"),
                             &view) == 0)
        {
            printf("Erro ao alocar memoria: o passo a passo nao sera mostrado.\n");
            step_mode = 0;
        }
    }

    /* Chooses the step function. With function == NULL nobody is notified. */
    if (step_mode == 1 && export_on == 1)
    {
        targets.view = view;
        targets.exporter = exporter;
        observer.function = step_both;
        observer.context = &targets;
    }
    else if (step_mode == 1)
    {
        observer.function = step_view_show;
        observer.context = view;
    }
    else if (export_on == 1)
    {
        observer.function = export_step;
        observer.context = exporter;
    }
    else
    {
        observer.function = NULL;
        observer.context = NULL;
    }

    ok = sort_run_steps(index, vector, copy, size, m, &observer);

    if (step_mode == 1)
    {
        step_view_destroy(&view);
        system("cls");
        printf("Fim do passo a passo (o tempo inclui as pausas).\n");
    }

    if (export_on == 1)
    {
        printf("\nLog exportado em %s\n", export_path(exporter));
        if (export_close(&exporter, copy, m) == 1)
            printf("(o tempo inclui a gravacao do arquivo)\n");
        else
            printf("Erro ao gravar o arquivo de log: ele pode estar incompleto.\n");
    }

    return ok;
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
            int ok;

            ok = run_sort(choice - 1, vector, copy, size, data_kind, &m);

            if (ok == 1)
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

/* Warns the user that the comparison takes minutes, asks for confirmation and runs it.
   The array of the main menu is not used nor changed. */
static void menu_benchmark(void)
{
    int answer = 0;
    long long before;

    printf("---- Comparativo vetor x listas ----\n");
    printf("Roda os 7 algoritmos do vetor e os 2 de cada lista (simples, dupla e circular)\n");
    printf("com N = %d, %d e %d, nos dados aleatorios, ordenados e invertidos:\n",
           benchmark_size(0), benchmark_size(1), benchmark_size(2));
    printf("9 tabelas de 13 linhas. Todos os algoritmos de uma tabela recebem os mesmos valores.\n\n");
    printf("ATENCAO: com N = %d, os algoritmos O(n^2) (Bubble, Selection, os Insertion do\n",
           benchmark_size(BENCHMARK_SIZE_COUNT - 1));
    printf("vetor e das listas e os Quick Sort com dados ordenados ou invertidos) levam\n");
    printf("varios segundos cada. O comparativo inteiro pode levar alguns minutos.\n");
    printf("O vetor do menu principal nao e alterado.\n\n");
    printf("Digite 1 para continuar ou 0 para voltar: ");
    if (scanf("%d", &answer) != 1)
        answer = 0;
    clear_input();

    if (answer != 1)
        return;

    before = mem_current();
    if (benchmark_run_all() == 0)
        printf("\nO comparativo nao terminou: faltou memoria para algum algoritmo.\n");

    /* Everything allocated by the comparison was freed, so this must be 0 */
    printf("\nMemoria nao liberada pelo comparativo: %lld bytes\n", mem_current() - before);
    wait_enter();
}

/* Reads at most nine characters (sign included) to stay within int
   and rejects extra text on the line. */
static int read_batch_int(int *out)
{
    int read = scanf("%9d", out);
    int c;

    do
    {
        c = getchar();
    } while (c == ' ' || c == '\t' || c == '\r');

    if (c == '\n' || c == EOF)
        return read == 1;

    clear_input();
    return 0;
}

static void run_batch(Queue *queue, int data_kind)
{
    int total = queue_count(queue);
    int number = 0;
    BatchTest test;
    Metrics metrics;

    while (queue_dequeue(queue, &test) == 1)
    {
        int *source;
        int *copy = NULL;

        printf("\n--- Teste %d/%d: %s (N = %d) ---\n",
               ++number, total, sort_name(test.sort_index), test.size);
        fflush(stdout);

        source = vector_create(test.size);
        if (source != NULL)
            copy = vector_create(test.size);

        if (source == NULL || copy == NULL)
        {
            printf("Erro ao alocar memoria para o teste.\n");
        }
        else
        {
            vector_fill(source, test.size, data_kind);
            if (sort_run(test.sort_index, source, copy, test.size, &metrics) == 1)
                metrics_print(&metrics, test.size, vector_fill_name(data_kind));
            else
                printf("Nao foi possivel executar o algoritmo.\n");
        }

        vector_destroy(&copy, test.size);
        vector_destroy(&source, test.size);
    }
}

static void menu_batch(int data_kind)
{
    Queue *queue = NULL;
    BatchTest test;
    int choice;

    if (queue_create(BATCH_CAPACITY, &queue) == 0)
    {
        printf("Erro ao alocar memoria para a fila.\n");
        wait_enter();
        return;
    }

    printf("---- Fila de testes em lote ----\n");
    printf("Dados: %s. Capacidade: %d testes.\n", vector_fill_name(data_kind), BATCH_CAPACITY);
    for (int i = 0; i < SORT_COUNT; i++)
        printf("%d - %s\n", i + 1, sort_name(i));
    printf("0 - Executar lote\n");
    printf("-1 - Voltar e descartar o lote\n");

    while (!feof(stdin) && !ferror(stdin))
    {
        printf("\nAlgoritmo ou acao: ");
        if (read_batch_int(&choice) == 0 || choice < -1 || choice > SORT_COUNT)
        {
            if (!feof(stdin) && !ferror(stdin))
                printf("Opcao invalida.\n");
            continue;
        }
        if (choice == -1)
            break;
        if (choice == 0)
        {
            if (queue_count(queue) == 0)
            {
                printf("A fila esta vazia.\n");
                continue;
            }
            run_batch(queue, data_kind);
            wait_enter();
            break;
        }
        if (queue_count(queue) == BATCH_CAPACITY)
        {
            printf("A fila esta cheia. Digite 0 para executar o lote.\n");
            continue;
        }

        test.sort_index = choice - 1;
        printf("Digite o tamanho do vetor para o teste: ");
        if (read_batch_int(&test.size) == 0 || test.size < 1 || test.size > BATCH_MAX_SIZE)
        {
            if (!feof(stdin) && !ferror(stdin))
                printf("Tamanho invalido. Digite um inteiro entre 1 e %d.\n", BATCH_MAX_SIZE);
            continue;
        }

        queue_enqueue(queue, test);
        printf("Teste enfileirado (%d/%d).\n", queue_count(queue), BATCH_CAPACITY);
    }

    queue_destroy(&queue);
}
