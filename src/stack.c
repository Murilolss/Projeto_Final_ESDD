#include <stdint.h>
#include "memory.h"
#include "stack.h"

struct Stack
{
    SwapIndices *swaps;
    size_t top; /* Index of the next free slot. */
    size_t capacity;
};

int stack_create(int initial_capacity, Stack **out)
{
    Stack *stack;

    if (out == NULL || initial_capacity <= 0 ||
        (size_t)initial_capacity > SIZE_MAX / sizeof(SwapIndices))
        return 0;

    stack = mem_alloc(sizeof(Stack));
    if (stack == NULL)
        return 0;

    stack->swaps = mem_alloc((size_t)initial_capacity * sizeof(SwapIndices));
    if (stack->swaps == NULL)
    {
        mem_free(stack, sizeof(Stack));
        return 0;
    }

    stack->top = 0;
    stack->capacity = (size_t)initial_capacity;
    *out = stack;
    return 1;
}

void stack_destroy(Stack **stack)
{
    if (stack == NULL || *stack == NULL)
        return;

    mem_free((*stack)->swaps, (*stack)->capacity * sizeof(SwapIndices));
    mem_free(*stack, sizeof(Stack));
    *stack = NULL;
}

static int stack_grow(Stack *stack)
{
    const size_t max_capacity = SIZE_MAX / sizeof(SwapIndices);
    size_t new_capacity;
    SwapIndices *swaps;

    if (stack->capacity == max_capacity)
        return 0;

    if (stack->capacity <= max_capacity / 2)
        new_capacity = 2 * stack->capacity;
    else
        new_capacity = max_capacity;

    swaps = mem_realloc(stack->swaps, stack->capacity * sizeof(SwapIndices),
                        new_capacity * sizeof(SwapIndices));
    if (swaps == NULL)
        return 0;

    stack->swaps = swaps;
    stack->capacity = new_capacity;
    return 1;
}

int stack_push(Stack *stack, SwapIndices swap)
{
    if (stack == NULL)
        return 0;
    if (stack->top == stack->capacity && stack_grow(stack) == 0)
        return 0;

    stack->swaps[stack->top] = swap;
    stack->top++;
    return 1;
}

int stack_pop(Stack *stack, SwapIndices *out)
{
    if (stack == NULL || out == NULL || stack->top == 0)
        return 0;

    stack->top--;
    *out = stack->swaps[stack->top];
    return 1;
}

int stack_undo_swap(Stack *stack, int *array, int size)
{
    SwapIndices swap;
    int value;

    if (stack == NULL || array == NULL || stack->top == 0)
        return 0;

    swap = stack->swaps[stack->top - 1];
    if (swap.first < 0 || swap.first >= size || swap.second < 0 || swap.second >= size)
        return 0;

    value = array[swap.first];
    array[swap.first] = array[swap.second];
    array[swap.second] = value;
    stack->top--;
    return 1;
}
