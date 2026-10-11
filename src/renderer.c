#include "renderer.h"
#include <stdio.h>

#define WINDOW_WIDTH (GRID_WIDTH * TILE_SIZE + 200)
#define WINDOW_HEIGHT (GRID_HEIGHT * TILE_SIZE)

bool renderer_init(Renderer *renderer) {
    renderer->window_width = WINDOW_WIDTH;
    renderer->window_height = WINDOW_HEIGHT;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    
    renderer->window = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!renderer->window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    renderer->renderer = SDL_CreateRenderer(
        renderer->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!renderer->renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(renderer->window);
        SDL_Quit();
        return false;
    }
    
    SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_BLEND);
    return true;
}

void renderer_cleanup(Renderer *renderer) {
    if (renderer->renderer) {
        SDL_DestroyRenderer(renderer->renderer);
    }
    if (renderer->window) {
        SDL_DestroyWindow(renderer->window);
    }
    SDL_Quit();
}

void renderer_clear(Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 15, 23, 42, 255);
    SDL_RenderClear(renderer->renderer);
}

static void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(r, &rect);
}

static void draw_grid(SDL_Renderer *r) {
    SDL_SetRenderDrawColor(r, 30, 41, 59, 128);
    for (int x = 0; x <= GRID_WIDTH; x++) {
        SDL_RenderDrawLine(r, x * TILE_SIZE, 0, x * TILE_SIZE, GRID_HEIGHT * TILE_SIZE);
    }
    for (int y = 0; y <= GRID_HEIGHT; y++) {
        SDL_RenderDrawLine(r, 0, y * TILE_SIZE, GRID_WIDTH * TILE_SIZE, y * TILE_SIZE);
    }
}

static void draw_text_simple(SDL_Renderer *r, const char *text, int x, int y, SDL_Color color) {
    // Simple text rendering using rectangles (no font file needed)
    // This is a placeholder - for production, use SDL_ttf
    (void)r;
    (void)text;
    (void)x;
    (void)y;
    (void)color;
}

void renderer_render(Renderer *renderer, Game *game) {
    // Draw background and grid
    draw_rect(renderer->renderer, 0, 0, GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE,
              (SDL_Color){11, 17, 32, 255});
    draw_grid(renderer->renderer);
    
    // Draw food (red circle-ish square)
    int food_x = game->food.pos.x * TILE_SIZE + 3;
    int food_y = game->food.pos.y * TILE_SIZE + 3;
    draw_rect(renderer->renderer, food_x, food_y, TILE_SIZE - 6, TILE_SIZE - 6,
              (SDL_Color){239, 68, 68, 255});
    
    // Draw snake
    for (int i = 0; i < game->snake.length; i++) {
        int sx = game->snake.body[i].x * TILE_SIZE + 2;
        int sy = game->snake.body[i].y * TILE_SIZE + 2;
        
        if (i == 0) {
            // Head - bright green
            draw_rect(renderer->renderer, sx, sy, TILE_SIZE - 4, TILE_SIZE - 4,
                      (SDL_Color){34, 197, 94, 255});
        } else {
            // Body - darker green
            draw_rect(renderer->renderer, sx, sy, TILE_SIZE - 4, TILE_SIZE - 4,
                      (SDL_Color){22, 163, 74, 255});
        }
    }
    
    // Draw UI panel on the right
    int ui_x = GRID_WIDTH * TILE_SIZE;
    draw_rect(renderer->renderer, ui_x, 0, 200, GRID_HEIGHT * TILE_SIZE,
              (SDL_Color){20, 28, 48, 255});
    
    // Draw borders
    SDL_SetRenderDrawColor(renderer->renderer, 34, 197, 94, 255);
    SDL_Rect border = {0, 0, GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE};
    SDL_RenderDrawRect(renderer->renderer, &border);
    
    // Draw status indicator
    SDL_Color status_color;
    if (game->state == GAME_RUNNING) {
        status_color = (SDL_Color){34, 197, 94, 255}; // Green
    } else if (game->state == GAME_OVER) {
        status_color = (SDL_Color){239, 68, 68, 255}; // Red
    } else {
        status_color = (SDL_Color){59, 130, 246, 255}; // Blue
    }
    draw_rect(renderer->renderer, ui_x + 20, 30, 160, 20, status_color);
}

void renderer_present(Renderer *renderer) {
    SDL_RenderPresent(renderer->renderer);
}
