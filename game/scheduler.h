#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <SDL3/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Scheduler Scheduler;

typedef struct {
    Uint64 trigger_time;
    void (*callback)(void *user_data);
    void *user_data;   
} Task;

Scheduler *scheduler_create(void);

void scheduler_destroy(Scheduler **scheduler);

/* Add a task to the scheduler */
/*
  * @param scheduler
  * the scheduler to add the task to
  * @param relative_time
  * the relative time in milliseconds
  * @param callback
  * the callback function to be called when the task is triggered
  * @param user_data
  * the user data to be passed to the callback function
*/
void scheduler_add_task(Scheduler *scheduler, Uint64 relative_time, void (*callback)(void *arg), void *user_data);

/* Clear all tasks from a scheduler */ 
void scheduler_clear_tasks(Scheduler *scheduler);

/* Process all tasks that are time out in the scheduler */
void scheduler_process_tasks(Scheduler *scheduler);

#ifdef __cplusplus
}
#endif

#endif // SCHEDULER_H