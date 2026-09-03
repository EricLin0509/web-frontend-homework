#ifndef GAME_EVENTS
#define GAME_EVENTS

#include "game.h"

typedef struct {
    Game *game;
    Uint64 token;
} IdleTaskData;

void game_resuming(void *arg);

void idle_timeout(void *arg);

bool idle_timeout_cancel(const Task *task);

#endif // GAME_EVENTS