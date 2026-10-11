#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20
#define TILE_SIZE 30
#define MAX_SNAKE_LENGTH 400

typedef enum {
    GAME_RUNNING,
    GAME_OVER,
    GAME_START,
    GAME_PAUSED
} GameState;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    int dx;
    int dy;
    int next_dx;
    int next_dy;
} Snake;

typedef struct {
    Position pos;
} Food;

typedef struct {
    Snake snake;
    Food food;
    GameState state;
    uint32_t score;
    uint32_t frame_count;
} Game;

// Game functions
void game_init(Game *game);
void game_update(Game *game);
void game_reset(Game *game);
void game_set_direction(Game *game, int dx, int dy);
bool game_is_running(Game *game);

#endif
