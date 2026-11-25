/* Edge case tests of the project modules (T22).
   It is a separate program (it has its own main) that calls the functions of the TADs
   with the limit cases of each structure (empty, one element, full, invalid arguments,
   NULL, biggest size) and checks the result of each call.
   Every check prints one line only when it fails; the end shows how many checks ran,
   how many failed and the memory that was not freed (it must be 0).

   Compile and run from the root folder of the project (the export test writes to logs/):
   gcc -Wall -Wextra -Isrc tests/edge_cases.c src/benchmark.c src/circular_list.c
       src/doubly_list.c src/export.c src/memory.c src/metrics.c src/queue.c src/search.c
       src/singly_list.c src/sort.c src/stack.c src/step_view.c src/vector.c
       -o tests/edge_cases.exe
   tests/edge_cases.exe

   The cases and the manual tests of the menu are described in contexto/casos_limite.md. */

#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "vector.h"
#include "sort.h"
#include "metrics.h"
#include "memory.h"
#include "search.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "circular_list.h"
#include "stack.h"
#include "queue.h"
#include "export.h"
#include "step_view.h"
#include "benchmark.h"

#define MAX_TEST_SIZE 1000

static int checks = 0;
static int failures = 0;

/* Counts one check and prints description if condition is false (0). */
static void check(int condition, const char *description)
{
    checks++;
    if (!condition)
    {
        failures++;
        printf("FALHOU: %s\n", description);
    }
}

/* Reference sort used to know the expected result: a plain insertion sort. */
static void reference_sort(int *v, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

/* 1 if a and b have the same size values in the same order. */
static int same_array(const int *a, const int *b, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

/* ---------- Vector ---------- */

static void test_vector(void)
{
    int *v;
    int count[11];
    int ok = 1;

    check(vector_create(0) == NULL, "vector_create(0) deve falhar");
    check(vector_create(-1) == NULL, "vector_create(-1) deve falhar");
    check(vector_create(VECTOR_MAX_SIZE + 1) == NULL,
          "vector_create(VECTOR_MAX_SIZE + 1) deve falhar (size * sizeof(int) estoura)");
    check(vector_create(INT_MAX) == NULL, "vector_create(INT_MAX) deve falhar");
    /* 1073741825 * 4 = 2^32 + 4: with a 4-byte size_t (32-bit MinGW) the product wraps
       to 4 bytes, malloc succeeds and the array would have room for only 1 int */
    check(vector_create(1073741825) == NULL,
          "vector_create(1073741825) deve falhar (o tamanho em bytes daria a volta para 4)");

    v = vector_create(1);
    check(v != NULL, "vector_create(1) deve funcionar");
    if (v == NULL)
        return;

    vector_fill_random(v, 1);
    check(v[0] == 1, "vetor aleatorio de 1 item deve ser {1}");
    check(vector_fill(v, 1, 99) == 0 && v[0] == 1, "tipo de dados invalido nao muda o vetor");
    check(vector_fill(NULL, 1, FILL_SORTED) == 0, "vector_fill(NULL) deve falhar");
    check(vector_fill(v, 0, FILL_SORTED) == 0, "vector_fill com tamanho 0 deve falhar");
    check(vector_fill_name(0) == NULL && vector_fill_name(4) == NULL,
          "vector_fill_name com tipo invalido deve devolver NULL");

    check(vector_resize(&v, 1, 0) == 0 && v != NULL, "resize para 0 falha e mantem o vetor");
    check(vector_resize(&v, 1, VECTOR_MAX_SIZE + 1) == 0 && v != NULL,
          "resize acima de VECTOR_MAX_SIZE falha e mantem o vetor");
    check(vector_resize(&v, 1, 1073741825) == 0 && v != NULL,
          "resize para 1073741825 falha (o tamanho em bytes daria a volta)");
    check(vector_resize(NULL, 1, 5) == 0, "resize com ponteiro NULL deve falhar");
    check(vector_resize(&v, 1, 10) == 1 && v[0] == 1, "resize 1 -> 10 mantem o primeiro valor");

    /* Random data of size 10: each value 1..10 exactly once */
    vector_fill_random(v, 10);
    for (int k = 0; k <= 10; k++)
        count[k] = 0;
    for (int i = 0; i < 10; i++)
    {
        if (v[i] < 1 || v[i] > 10)
            ok = 0;
        else
            count[v[i]]++;
    }
    for (int k = 1; k <= 10; k++)
    {
        if (count[k] != 1)
            ok = 0;
    }
    check(ok, "vetor aleatorio deve ter os valores 1..N sem repeticao");

    check(vector_resize(&v, 10, 2) == 1, "resize 10 -> 2 (diminuir) deve funcionar");
    vector_destroy(&v, 2);
    check(v == NULL, "vector_destroy deve zerar o ponteiro");
    vector_destroy(&v, 2); /* second destroy: must do nothing */
    vector_destroy(NULL, 2);
}

/* ---------- Sequential search ---------- */

static void test_search(void)
{
    int v[4] = {7, 3, 9, 3};

    check(sequential_search(NULL, 4, 3) == -1, "busca em vetor NULL devolve -1");
    check(sequential_search(v, 0, 7) == -1, "busca em vetor vazio devolve -1");
    check(sequential_search(v, 4, 7) == 0, "valor na primeira posicao");
    check(sequential_search(v, 4, 3) == 1, "valor repetido devolve a primeira ocorrencia");
    check(sequential_search(v, 3, 3) == 1, "busca respeita o tamanho");
    check(sequential_search(v, 4, 5) == -1, "valor ausente devolve -1");
}

/* ---------- Array sorts ---------- */

/* Replays the steps of a sort on its own copy of the array, like the web page does with
   the exported log. At the end the copy must be equal to the sorted array. */
typedef struct {
    int values[MAX_TEST_SIZE];
    int size;
    int bad_step; /* 1 = some step had an invalid kind or position */
} Replay;

static void replay_step(int kind, int i, int j, int left_value, int right_value,
                        const int *array, int size, void *context)
{
    Replay *r = (Replay *)context;
    int aux;

    (void)left_value;
    (void)right_value;

    if (size != r->size || i < 0 || i >= size || j >= size)
    {
        r->bad_step = 1;
        return;
    }

    if (kind == STEP_COMPARE)
    {
        if (j < 0)
            r->bad_step = 1;
    }
    else if (kind == STEP_SWAP)
    {
        if (j < 0)
        {
            r->bad_step = 1;
            return;
        }
        aux = r->values[i];
        r->values[i] = r->values[j];
        r->values[j] = aux;
    }
    else if (kind == STEP_WRITE)
        r->values[i] = array[i]; /* the step comes after the write */
    else
        r->bad_step = 1;
}

/* Sorts input with every algorithm, with and without observer, and checks the result
   against the reference sort. name describes the input in the failure messages. */
static void check_all_sorts(const int *input, int size, const char *name)
{
    static int expected[MAX_TEST_SIZE];
    static int output[MAX_TEST_SIZE];
    static Replay replay;
    char description[160];
    Metrics m;
    StepObserver observer = {replay_step, &replay};

    memcpy(expected, input, size * sizeof(int));
    reference_sort(expected, size);

    for (int k = 0; k < SORT_COUNT; k++)
    {
        snprintf(description, sizeof(description), "%s ordena %s", sort_name(k), name);
        check(sort_run(k, input, output, size, &m) == 1 && same_array(output, expected, size),
              description);

        memcpy(replay.values, input, size * sizeof(int));
        replay.size = size;
        replay.bad_step = 0;
        snprintf(description, sizeof(description),
                 "%s: os passos de %s reaplicados dao o vetor ordenado", sort_name(k), name);
        check(sort_run_steps(k, input, output, size, &m, &observer) == 1 &&
              replay.bad_step == 0 && same_array(replay.values, expected, size), description);
    }
}

static void test_sorts(void)
{
    static int input[MAX_TEST_SIZE];
    static int output[MAX_TEST_SIZE];
    int sizes[] = {1, 2, 3, 4, 5, 8, 16, 17, 100, MAX_TEST_SIZE};
    int size_count = (int)(sizeof(sizes) / sizeof(sizes[0]));
    int kinds[] = {FILL_RANDOM, FILL_SORTED, FILL_REVERSED};
    int equal[6] = {4, 4, 4, 4, 4, 4};
    int two_values[7] = {2, 1, 2, 1, 2, 1, 2};
    int extremes[6] = {INT_MAX, INT_MIN, 0, -1, 1, INT_MAX};
    char name[60];
    Metrics m;

    for (int s = 0; s < size_count; s++)
    {
        for (int k = 0; k < 3; k++)
        {
            vector_fill(input, sizes[s], kinds[k]);
            snprintf(name, sizeof(name), "N = %d %s", sizes[s], vector_fill_name(kinds[k]));
            check_all_sorts(input, sizes[s], name);
        }
    }
    check_all_sorts(equal, 6, "todos os valores iguais");
    check_all_sorts(two_values, 7, "so dois valores repetidos");
    check_all_sorts(extremes, 6, "INT_MAX, INT_MIN, 0 e negativos");

    /* Invalid arguments */
    check(bubble_sort(NULL, 5, &m, NULL) == 0 && selection_sort(input, 5, NULL, NULL) == 0,
          "algoritmo com vetor ou metricas NULL deve falhar");
    check(sort_run(-1, input, output, 5, &m) == 0 && sort_run(SORT_COUNT, input, output, 5, &m) == 0,
          "sort_run com indice fora da tabela deve falhar");
    check(sort_run(0, NULL, output, 5, &m) == 0 && sort_run(0, input, NULL, 5, &m) == 0 &&
          sort_run(0, input, output, 5, NULL) == 0, "sort_run com ponteiro NULL deve falhar");
    check(sort_run(0, input, output, 0, &m) == 0, "sort_run com tamanho 0 deve falhar");
    check(sort_name(-1) == NULL && sort_name(SORT_COUNT) == NULL,
          "sort_name com indice invalido devolve NULL");

    /* Metrics of the best and worst cases (N = 10) */
    vector_fill(input, 10, FILL_SORTED);
    sort_run(0, input, output, 10, &m);
    check(m.comparisons == 9 && m.swaps == 0, "Bubble em dados ordenados: 9 comparacoes, 0 trocas");
    sort_run(1, input, output, 10, &m);
    check(m.comparisons == 9 && m.swaps == 0, "Insertion em dados ordenados: 9 comparacoes, 0 trocas");
    sort_run(6, input, output, 10, &m);
    check(m.comparisons == 45 && m.swaps == 0, "Selection em dados ordenados: 45 comparacoes, 0 trocas");
    vector_fill(input, 10, FILL_REVERSED);
    sort_run(0, input, output, 10, &m);
    check(m.swaps == 45, "Bubble em dados invertidos: 45 trocas");
    sort_run(2, input, output, 10, &m);
    check(m.memory_bytes > 0, "Merge Sort no vetor deve medir memoria extra");
    sort_run(0, input, output, 10, &m);
    check(m.memory_bytes == 0, "Bubble Sort nao usa memoria extra");
    sort_run(1, input, output, 1, &m);
    check(m.comparisons == 0 && m.swaps == 0, "vetor de 1 item: 0 comparacoes e 0 trocas");
}

/* ---------- Linked lists ---------- */

static void test_singly_list(void)
{
    SinglyList *l = slist_create();
    int v[3] = {3, 2, 1};
    int out[4];
    Metrics m;

    check(l != NULL, "slist_create deve funcionar");
    if (l == NULL)
        return;

    metrics_init(&m, "teste");
    check(slist_size(l) == 0 && slist_size(NULL) == 0, "lista simples nova esta vazia");
    check(slist_insertion_sort(l, &m) == 1 && slist_merge_sort(l, &m) == 1,
          "ordenar lista simples vazia funciona");
    check(slist_insertion_sort(NULL, &m) == 0 && slist_merge_sort(l, NULL) == 0,
          "ordenar lista simples com NULL deve falhar");
    check(slist_from_array(l, v, 0) == 0 && slist_from_array(l, NULL, 3) == 0 &&
          slist_from_array(NULL, v, 3) == 0, "slist_from_array com argumentos invalidos falha");
    check(slist_to_array(l, out, 1) == 0, "slist_to_array com tamanho diferente falha");

    check(slist_from_array(l, v, 1) == 1 && slist_merge_sort(l, &m) == 1 &&
          slist_to_array(l, out, 1) == 1 && out[0] == 3, "lista simples de 1 no");

    check(slist_from_array(l, v, 3) == 1 && slist_merge_sort(l, &m) == 1 &&
          slist_to_array(l, out, 3) == 1 && out[0] == 1 && out[2] == 3,
          "merge na lista simples invertida de 3 nos");
    check(slist_insert_front(l, 9) == 1 && slist_insertion_sort(l, &m) == 1 &&
          slist_to_array(l, out, 4) == 1 && out[0] == 1 && out[3] == 9,
          "lista simples continua valida depois do merge (insere no inicio e ordena de novo)");
    check(slist_memory_bytes(l) > 0 && slist_memory_bytes(NULL) == 0, "memoria da lista simples");

    /* Reversed data: 2 comparisons and 1 node moved per node after the first */
    check(slist_sort_run(0, v, 3, l, &m) == 1 && m.comparisons == 4 && m.swaps == 2,
          "Insertion na lista simples invertida: 2(n-1) comparacoes e n-1 nos movidos");
    check(slist_sort_run(1, v, 3, l, &m) == 1 && m.memory_bytes == 0,
          "Merge na lista simples nao usa memoria extra");
    check(slist_sort_run(2, v, 3, l, &m) == 0 && slist_sort_run(-1, v, 3, l, &m) == 0,
          "slist_sort_run com indice invalido falha");
    check(slist_sort_name(SLIST_SORT_COUNT) == NULL, "slist_sort_name invalido devolve NULL");

    slist_clear(l);
    check(slist_size(l) == 0, "slist_clear esvazia a lista");
    slist_clear(l); /* clear of an empty list */
    slist_destroy(&l);
    check(l == NULL, "slist_destroy zera o ponteiro");
    slist_destroy(&l);
    slist_destroy(NULL);
}

static void test_doubly_list(void)
{
    DoublyList *l = dlist_create();
    int v[3] = {3, 2, 1};
    int out[4];
    Metrics m;

    check(l != NULL, "dlist_create deve funcionar");
    if (l == NULL)
        return;

    metrics_init(&m, "teste");
    check(dlist_insertion_sort(l, &m) == 1 && dlist_merge_sort(l, &m) == 1,
          "ordenar lista dupla vazia funciona");
    check(dlist_insertion_sort(NULL, &m) == 0 && dlist_merge_sort(l, NULL) == 0,
          "ordenar lista dupla com NULL deve falhar");
    check(dlist_from_array(l, v, 0) == 0 && dlist_to_array(l, out, 2) == 0,
          "lista dupla com argumentos invalidos falha");

    /* One node: head and tail are the same node; inserting after it must use tail */
    check(dlist_from_array(l, v, 1) == 1 && dlist_insertion_sort(l, &m) == 1 &&
          dlist_insert_back(l, 1) == 1 && dlist_to_array(l, out, 2) == 1 &&
          out[0] == 3 && out[1] == 1, "lista dupla de 1 no: o tail continua certo");

    /* After the merge, tail must be the last node and every prev must be right:
       insert_back uses tail, and the insertion sort walks back with prev */
    check(dlist_from_array(l, v, 3) == 1 && dlist_merge_sort(l, &m) == 1 &&
          dlist_insert_back(l, 0) == 1 && dlist_to_array(l, out, 4) == 1 && out[3] == 0,
          "depois do merge na lista dupla o tail aponta para o ultimo no");
    check(dlist_insertion_sort(l, &m) == 1 && dlist_to_array(l, out, 4) == 1 &&
          out[0] == 0 && out[3] == 3, "depois do merge os ponteiros prev da lista dupla estao certos");
    /* The list now has 5 nodes and out has room for 4: the copy must be refused */
    check(dlist_insert_back(l, 10) == 1 && dlist_to_array(l, out, 4) == 0,
          "dlist_to_array com tamanho menor que a lista falha");

    check(dlist_sort_run(0, v, 3, l, &m) == 1 && m.swaps == 2,
          "Insertion na lista dupla invertida move n-1 nos");
    check(dlist_sort_run(DLIST_SORT_COUNT, v, 3, l, &m) == 0, "dlist_sort_run invalido falha");

    dlist_destroy(&l);
    check(l == NULL, "dlist_destroy zera o ponteiro");
    dlist_destroy(&l);
}

static void test_circular_list(void)
{
    CircularList *l = clist_create();
    int v[3] = {3, 2, 1};
    int out[4];
    Metrics m;

    check(l != NULL, "clist_create deve funcionar");
    if (l == NULL)
        return;

    metrics_init(&m, "teste");
    check(clist_insertion_sort(l, &m) == 1 && clist_merge_sort(l, &m) == 1,
          "ordenar lista circular vazia funciona");
    check(clist_to_array(l, out, 0) == 1, "clist_to_array de lista vazia com tamanho 0");
    check(clist_insertion_sort(NULL, &m) == 0 && clist_merge_sort(l, NULL) == 0,
          "ordenar lista circular com NULL deve falhar");

    /* One node: it points to itself */
    check(clist_from_array(l, v, 1) == 1 && clist_merge_sort(l, &m) == 1 &&
          clist_to_array(l, out, 1) == 1 && out[0] == 3, "lista circular de 1 no");

    /* After the sort the circle must be closed again and tail must be the last node:
       insert_back links the new node between tail and tail->next (the first one) */
    check(clist_from_array(l, v, 3) == 1 && clist_merge_sort(l, &m) == 1 &&
          clist_insert_back(l, 0) == 1 && clist_to_array(l, out, 4) == 1 &&
          out[0] == 1 && out[3] == 0, "depois do merge a lista circular continua fechada");
    check(clist_insertion_sort(l, &m) == 1 && clist_to_array(l, out, 4) == 1 &&
          out[0] == 0 && out[3] == 3, "insertion na lista circular depois do merge");

    check(clist_sort_run(1, v, 3, l, &m) == 1 && m.memory_bytes == 0,
          "Merge na lista circular nao usa memoria extra");
    check(clist_sort_run(-1, v, 3, l, &m) == 0, "clist_sort_run invalido falha");

    clist_clear(l);
    check(clist_size(l) == 0, "clist_clear esvazia a lista circular");
    clist_clear(l);
    clist_destroy(&l);
    check(l == NULL, "clist_destroy zera o ponteiro");
    clist_destroy(&l);
}

/* ---------- Stack (undo) ---------- */

static void test_stack(void)
{
    Stack *s = NULL;
    int v[3] = {10, 20, 30};
    SwapIndices p;
    SwapIndices swap = {0, 2};
    SwapIndices outside = {0, 5};

    check(stack_create(0, &s) == 0 && stack_create(-1, &s) == 0 && s == NULL,
          "pilha com capacidade 0 ou negativa nao e criada");
    check(stack_create(1, NULL) == 0, "stack_create com saida NULL falha");
    check(stack_create(1, &s) == 1, "pilha de capacidade 1 e criada");
    if (s == NULL)
        return;

    /* Empty stack */
    check(stack_undo_change(s, v, 3, &p) == 0, "desfazer com a pilha vazia falha");
    check(stack_redo_change(s, v, 3, &p) == 0 && stack_has_redo(s) == 0,
          "refazer sem nada desfeito falha");
    check(stack_pop(s, &p) == 0, "pop na pilha vazia falha");

    /* Two pushes with capacity 1: the stack has to grow */
    v[0] = 30;
    v[2] = 10;
    check(stack_push(s, swap) == 1, "push da troca 0 <-> 2");
    v[1] = 99;
    check(stack_push_write(s, 1, 20, 99) == 1, "push da escrita (pilha cresce de 1 para 2)");
    check(stack_push_write(s, -1, 0, 0) == 0, "escrita em posicao negativa e rejeitada");

    /* Undo the two changes, in reverse order (LIFO) */
    check(stack_undo_change(s, v, 3, &p) == 1 && v[1] == 20 && p.first == 1 && p.second == -1,
          "desfazer a escrita devolve o valor antigo");
    check(stack_undo_change(s, v, 3, &p) == 1 && v[0] == 10 && v[2] == 30,
          "desfazer a troca destroca as posicoes");
    check(stack_undo_change(s, v, 3, &p) == 0, "nao ha mais nada para desfazer");

    /* Redo both, then nothing is left to redo */
    check(stack_redo_change(s, v, 3, &p) == 1 && v[0] == 30, "refazer a troca");
    check(stack_redo_change(s, v, 3, &p) == 1 && v[1] == 99, "refazer a escrita");
    check(stack_redo_change(s, v, 3, &p) == 0 && stack_has_redo(s) == 0,
          "depois de refazer tudo nao ha mais o que refazer");

    /* A new push after an undo discards what could be redone */
    check(stack_undo_change(s, v, 3, &p) == 1 && stack_has_redo(s) == 1, "desfaz a escrita");
    check(stack_push(s, swap) == 1 && stack_has_redo(s) == 0, "push novo descarta o refazer");

    /* Invalid positions: nothing changes */
    check(stack_undo_change(s, v, 2, &p) == 0, "desfazer troca com posicao fora do vetor falha");
    check(stack_undo_change(s, NULL, 3, &p) == 0 && stack_undo_change(s, v, 3, NULL) == 0,
          "desfazer com argumentos NULL falha");
    check(stack_pop(s, &p) == 1 && p.first == 0 && p.second == 2, "pop devolve a ultima troca");
    check(stack_push(s, outside) == 1 && stack_undo_swap(s, v, 3) == 0,
          "stack_undo_swap com posicao fora do vetor falha");
    check(stack_push(NULL, swap) == 0 && stack_has_redo(NULL) == 0, "pilha NULL");

    stack_destroy(&s);
    check(s == NULL, "stack_destroy zera o ponteiro");
    stack_destroy(&s);
    stack_destroy(NULL);
}

/* ---------- Queue (batch) ---------- */

/* Same sequence as the exercise of the class slides (capacity 4):
   enqueue(10) enqueue(20) enqueue(30) dequeue() enqueue(40) enqueue(50).
   The last enqueue goes back to position 0 (circular queue). */
static void test_queue(void)
{
    Queue *q = NULL;
    BatchTest test = {0, 0};
    BatchTest out;
    int values[5] = {10, 20, 30, 40, 50};
    int ok = 1;

    check(queue_create(0, &q) == 0 && queue_create(-3, &q) == 0 && q == NULL,
          "fila com capacidade 0 ou negativa nao e criada");
    check(queue_create(4, NULL) == 0, "queue_create com saida NULL falha");
    check(queue_create(4, &q) == 1, "fila de capacidade 4 e criada");
    if (q == NULL)
        return;

    check(queue_dequeue(q, &out) == 0, "dequeue na fila vazia falha");

    for (int k = 0; k < 3; k++)
    {
        test.size = values[k];
        queue_enqueue(q, test);
    }
    check(queue_dequeue(q, &out) == 1 && out.size == 10, "primeiro a entrar e o primeiro a sair");
    test.size = 40;
    check(queue_enqueue(q, test) == 1, "enqueue(40)");
    test.size = 50;
    check(queue_enqueue(q, test) == 1 && queue_count(q) == 4, "enqueue(50) volta a posicao 0");
    test.size = 60;
    check(queue_enqueue(q, test) == 0 && queue_count(q) == 4, "enqueue na fila cheia falha");

    for (int k = 1; k < 5; k++)
    {
        if (queue_dequeue(q, &out) == 0 || out.size != values[k])
            ok = 0;
    }
    check(ok, "a ordem de saida e 20, 30, 40, 50");
    check(queue_count(q) == 0 && queue_dequeue(q, &out) == 0, "fila vazia de novo");
    check(queue_dequeue(q, NULL) == 0 && queue_enqueue(NULL, test) == 0 && queue_count(NULL) == 0,
          "fila ou saida NULL");

    queue_destroy(&q);
    check(q == NULL, "queue_destroy zera o ponteiro");
    queue_destroy(&q);
}

/* ---------- Export ---------- */

static void test_export(void)
{
    int v[3] = {3, 1, 2};
    int big[EXPORT_MAX_SIZE + 1];
    int out[3];
    Exporter *e = NULL;
    Metrics m;
    Metrics list[1];
    const char *structures[1] = {"Vetor"};
    char path[EXPORT_PATH_SIZE];
    StepObserver observer;

    vector_fill_sorted(big, EXPORT_MAX_SIZE + 1);
    check(export_open("Bubble Sort", "Ordenado", big, EXPORT_MAX_SIZE + 1, &e) == 0 && e == NULL,
          "exportar acima de EXPORT_MAX_SIZE e recusado");
    check(export_open("Bubble Sort", "Ordenado", v, 0, &e) == 0, "exportar vetor vazio e recusado");
    check(export_open(NULL, "Ordenado", v, 3, &e) == 0 && export_open("Bubble Sort", "Ordenado", v, 3, NULL) == 0,
          "export_open com argumentos NULL falha");
    check(export_path(NULL) == NULL, "export_path(NULL) devolve NULL");
    check(export_close(NULL, NULL, NULL) == 0 && export_close(&e, NULL, NULL) == 0,
          "export_close sem exportador falha");

    /* A real log of 3 items. The program must run from the root folder (logs/ exists). */
    if (export_open("Teste Casos Limite", "Aleatorio", v, 3, &e) == 0)
    {
        check(0, "export_open de 3 itens (rode a partir da pasta raiz do projeto)");
        return;
    }
    strcpy(path, export_path(e));
    observer.function = export_step;
    observer.context = e;
    export_step(99, 0, 1, 0, 0, v, 3, e); /* invalid kind: ignored, the JSON stays valid */
    export_step(STEP_SWAP, 0, 5, 0, 0, v, 3, e); /* invalid position: ignored */
    check(sort_run_steps(0, v, out, 3, &m, &observer) == 1, "ordenacao exportada de 3 itens");
    check(export_close(&e, out, &m) == 1 && e == NULL, "export_close grava o arquivo e zera o ponteiro");
    check(remove(path) == 0, "o log exportado existe (e foi apagado pelo teste)");

    /* Comparison report */
    metrics_init(&list[0], "Bubble Sort");
    check(export_report(list, structures, 0, 3, "Aleatorio", path) == 0,
          "comparativo sem resultados e recusado");
    check(export_report(list, structures, 1, 3, "Aleatorio", path) == 1 && remove(path) == 0,
          "comparativo de 1 resultado e gravado");
}

/* ---------- Other modules ---------- */

static void test_other_modules(void)
{
    Metrics m;
    StepView *view = NULL;
    int v[3] = {1, 2, 3};
    long long before;

    /* Memory counter */
    before = mem_current();
    check(mem_alloc(0) == NULL && mem_current() == before, "mem_alloc(0) devolve NULL e nao conta");
    mem_free(NULL, 100);
    check(mem_current() == before, "mem_free(NULL) nao muda o contador");

    /* Metrics: long names are cut, NULL is ignored */
    metrics_init(&m, "Um nome de algoritmo com mais de trinta caracteres");
    check(strlen(m.name) == sizeof(m.name) - 1, "nome longo e cortado em 29 caracteres");
    metrics_init(NULL, "x");
    metrics_init(&m, NULL);

    /* Benchmark size table */
    check(benchmark_size(-1) == 0 && benchmark_size(BENCHMARK_SIZE_COUNT) == 0,
          "benchmark_size com indice invalido devolve 0");

    /* Step view: only the cases that return before drawing (the screen needs ENTER) */
    check(step_view_create(NULL, 0, v, 3, &view) == 0 && step_view_create("x", 0, v, 0, &view) == 0 &&
          step_view_create("x", 0, NULL, 3, &view) == 0 && view == NULL,
          "step_view_create com argumentos invalidos falha");
    check(step_view_create("Teste", 0, v, 3, &view) == 1, "step_view_create funciona");
    step_view_show(99, 0, 1, 0, 0, v, 3, view);        /* invalid kind: ignored */
    step_view_show(STEP_SWAP, 0, 1, 0, 0, v, 2, view); /* size of another array: ignored */
    step_view_show(STEP_COMPARE, 0, 1, 1, 2, v, 3, view); /* pause_on_compare = 0: no pause */
    step_view_show(STEP_SWAP, 0, 1, 0, 0, NULL, 3, NULL);
    step_view_destroy(&view);
    check(view == NULL, "step_view_destroy zera o ponteiro");
    step_view_destroy(&view);
}

int main(void)
{
    srand(12345); /* fixed seed: the random data is the same in every run */

    test_vector();
    test_search();
    test_sorts();
    test_singly_list();
    test_doubly_list();
    test_circular_list();
    test_stack();
    test_queue();
    test_export();
    test_other_modules();

    /* Every module freed what it allocated */
    check(mem_current() == 0, "toda a memoria alocada foi liberada");

    printf("\n%d verificacoes, %d falhas. Memoria nao liberada: %lld bytes.\n",
           checks, failures, mem_current());
    if (failures == 0)
        printf("Todos os casos-limite passaram.\n");

    return (failures == 0) ? 0 : 1;
}
