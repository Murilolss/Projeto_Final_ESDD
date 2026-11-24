#include <limits.h>
#include "memory.h"
#include "stack.h"

typedef struct
{
    SwapIndices positions;
    int is_write;
    int old_value;
    int new_value;
} ArrayChange;

#define STACK_MAX_CAPACITY (INT_MAX / (int)sizeof(ArrayChange))

struct Stack
{
    ArrayChange *changes;
    int top; /* Index of the next free slot after all recorded changes. */
    int cursor; /* Index of the next change to replay. */
    int capacity;
};

int stack_create(int initial_capacity, Stack **out)
{
    Stack *stack;

    if (out == NULL || initial_capacity <= 0 || initial_capacity > STACK_MAX_CAPACITY)
        return 0;

    stack = mem_alloc(sizeof(Stack));
    if (stack == NULL)
        return 0;

    stack->changes = mem_alloc(initial_capacity * sizeof(ArrayChange));
    if (stack->changes == NULL)
    {
        mem_free(stack, sizeof(Stack));
        return 0;
    }

    stack->top = 0;
    stack->cursor = 0;
    stack->capacity = initial_capacity;
    *out = stack;
    return 1;
}

void stack_destroy(Stack **stack)
{
    if (stack == NULL || *stack == NULL)
        return;

    mem_free((*stack)->changes, (*stack)->capacity * sizeof(ArrayChange));
    mem_free(*stack, sizeof(Stack));
    *stack = NULL;
}

static int stack_grow(Stack *stack)
{
    int new_capacity;
    ArrayChange *changes;

    if (stack->capacity == STACK_MAX_CAPACITY)
        return 0;

    if (stack->capacity <= STACK_MAX_CAPACITY / 2)
        new_capacity = 2 * stack->capacity;
    else
        new_capacity = STACK_MAX_CAPACITY;

    changes = mem_realloc(stack->changes, stack->capacity * sizeof(ArrayChange),
                          new_capacity * sizeof(ArrayChange));
    if (changes == NULL)
        return 0;

    stack->changes = changes;
    stack->capacity = new_capacity;
    return 1;
}

static int push_change(Stack *stack, ArrayChange change)
{
    if (stack == NULL)
        return 0;
    if (stack->cursor == stack->capacity && stack_grow(stack) == 0)
        return 0;

    stack->changes[stack->cursor] = change;
    stack->cursor++;
    stack->top = stack->cursor;
    return 1;
}

int stack_push(Stack *stack, SwapIndices swap)
{
    ArrayChange change = {swap, 0, 0, 0};

    return push_change(stack, change);
}

int stack_push_write(Stack *stack, int index, int old_value, int new_value)
{
    ArrayChange change = {{index, -1}, 1, old_value, new_value};

    if (index < 0)
        return 0;

    return push_change(stack, change);
}

int stack_pop(Stack *stack, SwapIndices *out)
{
    if (stack == NULL || out == NULL || stack->cursor == 0 ||
        stack->changes[stack->cursor - 1].is_write)
        return 0;

    stack->cursor--;
    stack->top = stack->cursor;
    *out = stack->changes[stack->cursor].positions;
    return 1;
}

static int apply_change(const ArrayChange *change, int *array, int size, int forward)
{
    int first = change->positions.first;
    int second = change->positions.second;
    int value;

    if (array == NULL || first < 0 || first >= size)
        return 0;

    if (change->is_write)
        array[first] = forward ? change->new_value : change->old_value;
    else
    {
        if (second < 0 || second >= size)
            return 0;
        value = array[first];
        array[first] = array[second];
        array[second] = value;
    }

    return 1;
}

int stack_undo_change(Stack *stack, int *array, int size, SwapIndices *out)
{
    if (stack == NULL || stack->cursor == 0 || out == NULL)
        return 0;
    if (!apply_change(&stack->changes[stack->cursor - 1], array, size, 0))
        return 0;

    stack->cursor--;
    *out = stack->changes[stack->cursor].positions;
    return 1;
}

int stack_has_redo(const Stack *stack)
{
    return stack != NULL && stack->cursor < stack->top;
}

int stack_redo_change(Stack *stack, int *array, int size, SwapIndices *out)
{
    if (!stack_has_redo(stack) || out == NULL)
        return 0;
    if (!apply_change(&stack->changes[stack->cursor], array, size, 1))
        return 0;

    *out = stack->changes[stack->cursor].positions;
    stack->cursor++;
    return 1;
}

int stack_undo_swap(Stack *stack, int *array, int size)
{
    SwapIndices positions;

    if (stack == NULL || stack->cursor == 0 || stack->changes[stack->cursor - 1].is_write)
        return 0;
    if (!stack_undo_change(stack, array, size, &positions))
        return 0;

    stack->top = stack->cursor;
    return 1;
}
