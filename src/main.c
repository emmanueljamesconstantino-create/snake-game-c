#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "renderer.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    Game game;
    Renderer renderer;
    
    // Initialize renderer
    if (!renderer_init(&renderer)) {
        fprintf(stderr, "Failed to initialize renderer\n");
        return 1;
    }
    
    // Initialize game
    game_init(&game);
    
    // Main loop
    bool running = true;
    SDL_Event event;
    const uint8_t *keys;
    int last_score = 0;
    
    printf("=== SNAKE GAME ===\n");
    printf("Controls: Arrow Keys or WASD\n");
    printf("SPACE: Start/Pause\n");
    printf("R: Reset\n");
    printf("Q or ESC: Quit\n");
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            running = false;
                            break;
                            
                        case SDLK_SPACE:
                            if (game.state == GAME_START || game.state == GAME_OVER) {
                                if (game.state == GAME_OVER) {
                                    game_reset(&game);
                                } else {
                                    game.state = GAME_RUNNING;
                                }
                            }
                            break;
                            
                        case SDLK_r:
                            game_reset(&game);
                            break;
                            
                        case SDLK_UP:
                        case SDLK_w:
                            game_set_direction(&game, 0, -1);
                            break;
                            
                        case SDLK_DOWN:
                        case SDLK_s:
                            game_set_direction(&game, 0, 1);
                            break;
                            
                        case SDLK_LEFT:
                        case SDLK_a:
                            game_set_direction(&game, -1, 0);
                            break;
                            
                        case SDLK_RIGHT:
                        case SDLK_d:
                            game_set_direction(&game, 1, 0);
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        // Update game
        game_update(&game);
        
        // Check for score changes
        if (game.score != last_score) {
            printf("Score: %u\n", game.score);
            last_score = game.score;
        }
        
        // Render
        renderer_clear(&renderer);
        renderer_render(&renderer, &game);
        renderer_present(&renderer);
        
        // FPS cap (60 FPS)
        SDL_Delay(16);
    }
    
    printf("Final Score: %u\n", game.score);
    renderer_cleanup(&renderer);
    return 0;
}
