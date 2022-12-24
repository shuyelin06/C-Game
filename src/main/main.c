#include <SDL2/SDL.h>

#include <stdio.h>

#include "../rendering/graphics.h"
#include "../physics/physics.h"

#include "game.h"

int main(int argc, char** argv){
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
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

    // Capture Keyboard State
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    // Program Running
    SDL_bool running = SDL_TRUE;
    while(running == SDL_TRUE){
        // Game Variables
        // Dummy Pipe (Head Node)
        struct Pipe *dummyHead = malloc(sizeof(struct Pipe));
        dummyHead->next = NULL;
        dummyHead->_x = -1;
        dummyHead->_pipeWidth = 0;

        // Bird
        Bird *bird = malloc(sizeof(Bird));
        bird->_x = 20;
        bird->_y = UPPER_Y / 2;
        bird->_yVel = 0;
        bird->_width = 6;
        bird->_height = 6;

        // Game
        Game *game = malloc(sizeof(Game));
        game->_bird = bird;
        game->_pipes = dummyHead;
        game->_gameOver = SDL_FALSE;
        game->score = 0;

        Uint64 lastTime = SDL_GetTicks64();

        SDL_bool gameRunning = SDL_TRUE;
        while ( gameRunning == SDL_TRUE && running == SDL_TRUE ) {
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        running = SDL_FALSE;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        game->_bird->_yVel = JUMP;
                        break;

                    default:
                        break;
                }
            }

            // If the game isn't over, update the game
            if (game->_gameOver == SDL_FALSE) {
                // Get the time now to find time elapsed
                Uint64 timeNow = SDL_GetTicks64();
                
                // Only update if time elapsed is greater than a millisecond
                if( timeNow - lastTime >= 1 ) {
                    update(game, timeNow - lastTime);
                    lastTime = timeNow;
                }
            } else {
                if ( keyboard[SDL_SCANCODE_SPACE] ) {
                    gameRunning = SDL_FALSE;
                }
            }
            
            // Rendering
            render(renderer, game);
        }

        free(dummyHead);
        free(bird);
        free(game);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}