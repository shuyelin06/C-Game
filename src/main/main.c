#include <SDL2/SDL.h>
#include <stdio.h>

#include "../rendering/graphics.h"
#include "../physics/physics.h"

#include "game.h"

int main(int argc, char** argv){
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Initialize Window
    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 500, 0);
    SDL_SetWindowResizable(window, SDL_FALSE);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Initialize Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Game Variables
    struct Game game = {
        ._bird = {
            ._x = 50,
            ._y = 50,
            ._yVel = 0,
            ._width = 30,
            ._height = 30
        },
        ._pipes = NULL
    };
    Uint64 lastTime = SDL_GetTicks64();

    SDL_bool running = SDL_TRUE;
    while(running == SDL_TRUE){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }

        // Get the time now to find time elapsed
        Uint64 timeNow = SDL_GetTicks64();
        
        // Only update if time elapsed is greater than a millisecond
        if( timeNow - lastTime >= 1 ) {
            update(&game, timeNow - lastTime);
            lastTime = timeNow;
        }
        
        // Rendering
        render(renderer, &game);
    }

    return 0;
}