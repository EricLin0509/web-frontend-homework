#ifndef PARTICLE_H
#define PARTICLE_H

#ifdef BENCHMARK_MODE
#define MAX_SNOWFLAKES  80000
#else
#define MAX_SNOWFLAKES 8000
#endif

#include <SDL3/SDL.h>

typedef struct {
    /* The position of each snowflake */
    float x[MAX_SNOWFLAKES];
    float y[MAX_SNOWFLAKES];

    float size[MAX_SNOWFLAKES]; // size
    float speed[MAX_SNOWFLAKES]; // fall speed
    float opacity[MAX_SNOWFLAKES]; // opacity
} Snowflake;

typedef struct {
    Snowflake snowflakes;
    int snowflake_count;

    /* The vertex and index arrays for snowflakes */
    SDL_Texture *snow_sprite; // A single snowflake texture
    SDL_Vertex *snow_vertices; // Vertex array for snowflakes
    int *snow_indices; // Index array for snowflakes
    int num_vertices;
    int num_indices;
} Snow;

bool init_snow(Snow *snow, SDL_Renderer *renderer);

void increase_snow_count(Snow *snow, int increment, uint32_t w, uint32_t h);

void update_snow(Snow *snow, uint32_t w, uint32_t h, float dt);

void render_snow(Snow *snow, SDL_Renderer *renderer);

#endif // PARTICLE_H