#include "scheduler.h"
#include "game_events.h"
#include "game.h"

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

    scheduler_add_task(game->scheduler, 500, game_resume, game);
}
