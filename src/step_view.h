#ifndef STEP_VIEW_H
#define STEP_VIEW_H

/* Step-by-step mode (T26): the screen is redrawn after every step of the sort and the
   program waits for ENTER. Each element is drawn as a horizontal bar proportional to its
   value (the biggest value gets STEP_VIEW_BAR_WIDTH characters).
   Arrays with up to STEP_VIEW_FULL_SIZE elements are shown whole; bigger arrays show only
   the lines near the positions of the step (STEP_VIEW_NEAR lines before and after each),
   so any size works. */

#define STEP_VIEW_BAR_WIDTH 50
#define STEP_VIEW_FULL_SIZE 20
#define STEP_VIEW_NEAR 4

typedef struct StepView StepView;

/* Creates the state of one step-by-step execution.
   name is the algorithm name shown on the screen. If pause_on_compare is 0, the screen
   stops only on swaps and writes; comparisons are just counted.
   initial and size describe the source array for undo playback.
   Returns 1 on success and writes the new view in *out. If the playback cannot be
   allocated, the view still shows live steps. Returns 0 if the view cannot be created. */
int step_view_create(const char *name, int pause_on_compare, const int *initial, int size,
                     StepView **out);

/* Frees the view and sets the caller's pointer to NULL. */
void step_view_destroy(StepView **view);

/* Step function (same signature as StepFunction in sort.h).
   context must be the StepView created above. It draws the array marking positions i
   and j. Typing u + ENTER undoes one change on the playback array. ENTER replays a
   change and resumes the sort as soon as playback catches up. At the latest step,
   ENTER advances the sort. Typing f + ENTER finishes the sort. */
void step_view_show(int kind, int i, int j, int left_value, int right_value,
                    const int *array, int size, void *context);

#endif
