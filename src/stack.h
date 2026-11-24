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

/* Records the indices of a swap and grows as needed. On success, discards any redo history.
   Returns 0 on failure and keeps the history intact. A caller that records before
   applying the swap can stop on failure without changing the array. */
int stack_push(Stack *stack, SwapIndices swap);

/* Removes the latest applied change if it is a swap, writes it to *out and discards
   any redo history. Returns 0 for NULL arguments, no applied changes or a latest write. */
int stack_pop(Stack *stack, SwapIndices *out);

/* Reverses and removes the latest applied change if it is a swap, discarding redo history.
   Returns 0 for NULL arguments, no applied changes, a latest write or an invalid index.
   On failure, the array and the history are unchanged. */
int stack_undo_swap(Stack *stack, int *array, int size);

/* Records a write at one position, including the value before and after it.
   On success, discards any redo history. Returns 0 if the write cannot be recorded. */
int stack_push_write(Stack *stack, int index, int old_value, int new_value);

/* Moves one change backward or forward on the playback array. On success, writes
   the affected positions to out. For a write, out->second is -1.
   Returns 0 at the end of the history in that direction or on invalid arguments. */
int stack_undo_change(Stack *stack, int *array, int size, SwapIndices *out);
int stack_redo_change(Stack *stack, int *array, int size, SwapIndices *out);

/* Returns 1 if there is a change to replay, or 0 otherwise. */
int stack_has_redo(const Stack *stack);

#endif
