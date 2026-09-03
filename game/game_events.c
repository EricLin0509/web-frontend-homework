#include "scheduler.h"
#include "game_events.h"

static void game_resume(void *arg)
{
    if (!arg) return;
    Game *game = (Game *)arg;
    game->state = GAME_RUNNING;
}

void game_resuming(void *arg)
{
    if (!arg) return;
    Game *game = (Game *)arg;
    game->state = GAME_RESUMING;

    scheduler_add_task(game->scheduler, 500, game_resume, NULL, NULL, game);
}

void idle_timeout(void *arg)
{
    if (!arg) return;
    IdleTaskData *data = (IdleTaskData *)arg;
    Game *game = data->game;

    game->mode_flags |= IDLE_MASK; // Set the refresh suspended flag
}

bool idle_timeout_cancel(const Task *task)
{
    if (!task) return true;
    IdleTaskData *data = (IdleTaskData *)task->user_data;
    Game *game = data->game;

    bool is_canceled = game->idle_token != data->token; // Check if the token matches the current token
    
    return is_canceled;
}
