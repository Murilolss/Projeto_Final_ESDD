#define __USE_MINGW_ANSI_STDIO 1 /* enables %lld on MinGW (must come before stdio.h) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "step_view.h"
#include "sort.h"
#include "memory.h"
#include "stack.h"
#include "vector.h"

#define HISTORY_INITIAL_CAPACITY 16

struct StepView {
    const char *name;      /* algorithm name shown on the screen */
    int pause_on_compare;  /* 1 = also stops on comparisons */
    int skip;              /* 1 = the user typed f: no more pauses until the end */
    long long steps;       /* steps shown so far (comparisons + swaps + writes) */
    long long comparisons;
    long long changes;     /* swaps + writes */
    int size;
    int *playback;
    Stack *history;
    int undo_available;
};

int step_view_create(const char *name, int pause_on_compare, const int *initial, int size,
                     StepView **out)
{
    StepView *view;

    if (name == NULL || initial == NULL || size <= 0 || out == NULL)
        return 0;

    view = (StepView *)mem_alloc(sizeof(StepView));
    if (view == NULL)
        return 0;

    view->name = name;
    view->pause_on_compare = pause_on_compare;
    view->skip = 0;
    view->steps = 0;
    view->comparisons = 0;
    view->changes = 0;
    view->size = size;
    view->history = NULL;
    view->playback = vector_create(size);
    view->undo_available = 0;

    if (view->playback != NULL && stack_create(HISTORY_INITIAL_CAPACITY, &view->history))
    {
        memcpy(view->playback, initial, size * sizeof(int));
        view->undo_available = 1;
    }
    else
        vector_destroy(&view->playback, size);

    *out = view;
    return 1;
}

void step_view_destroy(StepView **view)
{
    if (view == NULL || *view == NULL)
        return;

    stack_destroy(&(*view)->history);
    vector_destroy(&(*view)->playback, (*view)->size);
    mem_free(*view, sizeof(StepView));
    *view = NULL;
}

/* Text of the step, e.g. "Troca: posicoes 3 e 4". */
static void print_step(int kind, int i, int j, int left_value, int right_value,
                       const int *array)
{
    if (kind == STEP_COMPARE)
        printf("Comparacao: valor %d (origem %d) com valor %d (origem %d)\n",
               left_value, i, right_value, j);
    else if (kind == STEP_SWAP)
        printf("Troca: posicoes %d e %d\n", i, j);
    else if (j >= 0)
        printf("Escrita: posicao %d recebeu o valor da posicao %d\n", i, j);
    else
        printf("Escrita: posicao %d recebeu o valor %d\n", i, array[i]);
}

/* Distance between two positions (always positive). */
static int distance(int a, int b)
{
    return (a > b) ? a - b : b - a;
}

/* A line is shown if the array is small, or if it is near position i or position j
   (j is -1 when there is no second position). */
static int is_visible(int p, int i, int j, int size)
{
    if (size <= STEP_VIEW_FULL_SIZE)
        return 1;
    if (distance(p, i) <= STEP_VIEW_NEAR)
        return 1;
    if (j >= 0 && distance(p, j) <= STEP_VIEW_NEAR)
        return 1;
    return 0;
}

/* Length of the bar of value: proportional to the biggest value of the array
   (biggest value = STEP_VIEW_BAR_WIDTH characters). long long avoids overflowing int
   in value * STEP_VIEW_BAR_WIDTH. A positive value always gets at least 1 character. */
static int bar_length(int value, int biggest)
{
    int length;

    if (value <= 0 || biggest <= 0)
        return 0;

    length = (int)((long long)value * STEP_VIEW_BAR_WIDTH / biggest);
    if (length == 0)
        length = 1;
    return length;
}

/* One line per visible element: position, value, a bar of '#' and a mark on the
   positions involved in the step. Hidden lines become a single "...". */
static void print_bars(int kind, int i, int j, const int *array, int size)
{
    int biggest = array[0];
    int hidden = 0; /* 1 = the previous line was hidden ("..." already printed) */
    int length;

    for (int p = 1; p < size; p++)
    {
        if (array[p] > biggest)
            biggest = array[p];
    }

    for (int p = 0; p < size; p++)
    {
        if (!is_visible(p, i, j, size))
        {
            if (!hidden)
                printf("  ...\n");
            hidden = 1;
            continue;
        }
        hidden = 0;

        length = bar_length(array[p], biggest);
        printf("%6d | %6d ", p, array[p]);
        for (int b = 0; b < length; b++)
            printf("#");
        for (int b = length; b < STEP_VIEW_BAR_WIDTH; b++)
            printf(" ");

        if (p == i || p == j)
            printf(" <-- %s", (kind == STEP_COMPARE) ? "origem" : "mudou");
        printf("\n");
    }
}

/* Reads the first character and discards the rest of the line. */
static int read_pause(void)
{
    int c;
    int first = getchar();

    /* Discards the rest of the line */
    c = first;
    while (c != '\n' && c != EOF)
        c = getchar();

    return first;
}

/* The observer runs after a change. Playback still has the previous values. */
static int record_change(StepView *view, int kind, int i, int j, const int *array)
{
    if (kind == STEP_SWAP)
    {
        SwapIndices swap = {i, j};
        if (!stack_push(view->history, swap))
            return 0;
        view->playback[j] = array[j];
    }
    else if (!stack_push_write(view->history, i, view->playback[i], array[i]))
        return 0;

    view->playback[i] = array[i];
    return 1;
}

static void show_history(const StepView *view, SwapIndices positions, int forward)
{
    system("cls");
    printf("%s - %s\n", view->name, forward ? "Alteracao reaplicada" : "Alteracao desfeita");
    print_bars(STEP_WRITE, positions.first, positions.second, view->playback, view->size);
    putchar('\n');
}

static void pause_at_step(StepView *view)
{
    SwapIndices positions;
    int command;

    for (;;)
    {
        if (view->undo_available)
            printf("ENTER = avancar | u + ENTER = desfazer | f + ENTER = ir ate o fim: ");
        else
            printf("ENTER = proximo passo | f + ENTER = ir ate o fim: ");

        command = read_pause();
        if (command == 'f' || command == 'F' || command == EOF)
        {
            view->skip = 1;
            return;
        }
        if (command == 'u' || command == 'U')
        {
            if (!view->undo_available)
                printf("Desfazer indisponivel.\n");
            else if (stack_undo_change(view->history, view->playback, view->size, &positions))
                show_history(view, positions, 0);
            else
                printf("Nenhuma alteracao para desfazer.\n");
        }
        else if (command == '\n')
        {
            if (!view->undo_available ||
                !stack_redo_change(view->history, view->playback, view->size, &positions))
                return;
            show_history(view, positions, 1);
        }
        else
            printf("Comando invalido.\n");
    }
}

void step_view_show(int kind, int i, int j, int left_value, int right_value,
                    const int *array, int size, void *context)
{
    /* context is the StepView the caller put in the StepObserver */
    StepView *view = (StepView *)context;

    if (view == NULL || array == NULL || size != view->size || view->skip)
        return;

    view->steps++;
    if (kind == STEP_COMPARE)
    {
        view->comparisons++;
        if (!view->pause_on_compare)
            return;
    }
    else
    {
        view->changes++;
        if (view->undo_available && !record_change(view, kind, i, j, array))
            view->undo_available = 0;
    }

    system("cls");
    printf("%s - passo %lld\n", view->name, view->steps);
    print_step(kind, i, j, left_value, right_value, array);
    printf("\n");
    print_bars(kind, i, j, array, size);
    printf("\nComparacoes: %lld   Trocas/escritas: %lld\n", view->comparisons, view->changes);
    if (!view->undo_available)
        printf("Desfazer indisponivel: faltou memoria para o historico.\n");
    pause_at_step(view);
}
