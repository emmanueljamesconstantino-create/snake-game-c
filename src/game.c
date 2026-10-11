#include "game.h"
#include <stdlib.h>
#include <time.h>

static void spawn_food(Game *game) {
    bool valid = false;
    while (!valid) {
        game->food.pos.x = rand() % GRID_WIDTH;
        game->food.pos.y = rand() % GRID_HEIGHT;
        
        valid = true;
        for (int i = 0; i < game->snake.length; i++) {
            if (game->snake.body[i].x == game->food.pos.x &&
                game->snake.body[i].y == game->food.pos.y) {
                valid = false;
                break;
            }
        }
    }
}

void game_init(Game *game) {
    srand((unsigned int)time(NULL));
    
    // Initialize snake at center
    game->snake.length = 3;
    game->snake.body[0].x = GRID_WIDTH / 2;
    game->snake.body[0].y = GRID_HEIGHT / 2;
    game->snake.body[1].x = GRID_WIDTH / 2 - 1;
    game->snake.body[1].y = GRID_HEIGHT / 2;
    game->snake.body[2].x = GRID_WIDTH / 2 - 2;
    game->snake.body[2].y = GRID_HEIGHT / 2;
    
    game->snake.dx = 1;
    game->snake.dy = 0;
    game->snake.next_dx = 1;
    game->snake.next_dy = 0;
    
    game->score = 0;
    game->frame_count = 0;
    game->state = GAME_START;
    
    spawn_food(game);
}

void game_reset(Game *game) {
    game->snake.length = 3;
    game->snake.body[0].x = GRID_WIDTH / 2;
    game->snake.body[0].y = GRID_HEIGHT / 2;
    game->snake.body[1].x = GRID_WIDTH / 2 - 1;
    game->snake.body[1].y = GRID_HEIGHT / 2;
    game->snake.body[2].x = GRID_WIDTH / 2 - 2;
    game->snake.body[2].y = GRID_HEIGHT / 2;
    
    game->snake.dx = 1;
    game->snake.dy = 0;
    game->snake.next_dx = 1;
    game->snake.next_dy = 0;
    
    game->score = 0;
    game->frame_count = 0;
    game->state = GAME_RUNNING;
    
    spawn_food(game);
}

void game_set_direction(Game *game, int dx, int dy) {
    // Prevent reversing into itself
    if (dx == -game->snake.dx && dy == -game->snake.dy) {
        return;
    }
    game->snake.next_dx = dx;
    game->snake.next_dy = dy;
}

void game_update(Game *game) {
    if (game->state != GAME_RUNNING) {
        return;
    }
    
    game->frame_count++;
    
    // Move snake every 10 frames (controls speed)
    if (game->frame_count % 10 != 0) {
        return;
    }
    
    // Update direction
    game->snake.dx = game->snake.next_dx;
    game->snake.dy = game->snake.next_dy;
    
    // Calculate new head position
    int new_x = game->snake.body[0].x + game->snake.dx;
    int new_y = game->snake.body[0].y + game->snake.dy;
    
    // Check wall collision (wrap around)
    if (new_x < 0) new_x = GRID_WIDTH - 1;
    if (new_x >= GRID_WIDTH) new_x = 0;
    if (new_y < 0) new_y = GRID_HEIGHT - 1;
    if (new_y >= GRID_HEIGHT) new_y = 0;
    
    // Check self collision
    for (int i = 0; i < game->snake.length; i++) {
        if (game->snake.body[i].x == new_x && game->snake.body[i].y == new_y) {
            game->state = GAME_OVER;
            return;
        }
    }
    
    // Move snake
    for (int i = game->snake.length - 1; i > 0; i--) {
        game->snake.body[i] = game->snake.body[i - 1];
    }
    game->snake.body[0].x = new_x;
    game->snake.body[0].y = new_y;
    
    // Check food collision
    if (game->snake.body[0].x == game->food.pos.x &&
        game->snake.body[0].y == game->food.pos.y) {
        if (game->snake.length < MAX_SNAKE_LENGTH) {
            game->snake.length++;
        }
        game->score += 10;
        spawn_food(game);
    }
}

bool game_is_running(Game *game) {
    return game->state == GAME_RUNNING || game->state == GAME_START;
}
