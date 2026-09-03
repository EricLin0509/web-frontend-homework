#include "scheduler.h"
#include <iostream>
#include <queue>

struct TaskOrder {
    bool operator()(const Task& a, const Task& b) const
    {
        return a.trigger_time > b.trigger_time; // The smaller trigger time comes first
    }
};

typedef struct Scheduler {
    std::priority_queue<Task, std::vector<Task>, TaskOrder> task_queue;
} Scheduler;

Scheduler *scheduler_create(void)
{
    return new Scheduler;
}

void scheduler_destroy(Scheduler **scheduler)
{
    if (!scheduler || !*scheduler) return;

    delete *scheduler;
}

void scheduler_add_task(Scheduler *scheduler, Uint64 relative_time, void (*callback)(void *arg), void *user_data)
{
    if (!scheduler || !callback) return;

    Uint64 trigger_time = relative_time + SDL_GetTicks() + 1; // Calculate the absolute trigger time
    scheduler->task_queue.push(Task{trigger_time, callback, user_data});
}

void scheduler_clear_tasks(Scheduler *scheduler)
{
    if (!scheduler) return;

    while (!scheduler->task_queue.empty())
    {
        scheduler->task_queue.pop(); // Remove all tasks from the queue
    }
}

void scheduler_process_tasks(Scheduler *scheduler)
{
    if (!scheduler) return;

    while (!scheduler->task_queue.empty() &&
            scheduler->task_queue.top().trigger_time <= SDL_GetTicks())
    {
        Task curr_task = scheduler->task_queue.top();
        scheduler->task_queue.pop();

        if (curr_task.callback)
            curr_task.callback(curr_task.user_data); // Execute the callback function
    }
}
