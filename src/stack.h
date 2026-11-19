#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

typedef struct
{
    int first;
    int second;
} SwapIndices;

/* Creates an empty stack. Returns 0 on failure and leaves *out unchanged. */
int stack_create(int initial_capacity, Stack **out);

/* Frees the stack and sets the caller's pointer to NULL. */
void stack_destroy(Stack **stack);

/* Records a swap before the caller applies it. Grows as needed.
   Returns 0 on failure and keeps the history intact. */
int stack_push(Stack *stack, SwapIndices swap);

/* Removes the latest swap and writes it to *out.
   Returns 0 if the stack is NULL or empty, or out is NULL. */
int stack_pop(Stack *stack, SwapIndices *out);

/* Reverses the latest recorded swap on the same array and removes it from the history.
   Returns 0 if the array is NULL, the stack is NULL or empty, or an index is out of range.
   On failure, the array and the history are unchanged. */
int stack_undo_swap(Stack *stack, int *array, int size);

#endif
