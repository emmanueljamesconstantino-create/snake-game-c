#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "game.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int window_width;
    int window_height;
} Renderer;

bool renderer_init(Renderer *renderer);
void renderer_cleanup(Renderer *renderer);
void renderer_clear(Renderer *renderer);
void renderer_render(Renderer *renderer, Game *game);
void renderer_present(Renderer *renderer);

#endif
