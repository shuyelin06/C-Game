#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 500

int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_SetWindowResizable(window, SDL_TRUE);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    double r = 0; double g = 120; double b = 240;
    double size = 0;

    int x = 0;
    int y = 0;

    int pressed = 1;

    int running = 0;
    while(running == 0){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    pressed = 0;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    pressed = 1;
                    break;

                default:
                    break;
            }
        }

        SDL_GetMouseState(&x, &y);

        if ( pressed == 0 ) {
    
            r += (rand() % (rand() % 8 + 1)) * 3.14159 / 180;
            g += (rand() % (rand() % 8 + 1)) * 3.14159 / 180;
            b += (rand() % (rand() % 8 + 1)) * 3.14159 / 180;
            SDL_SetRenderDrawColor(renderer, 255 * SDL_sin(r), 255 * SDL_sin(g), 255 * SDL_sin(b), 255);
            if ( 0 < x && x < SCREEN_WIDTH ) {
                if ( 0 < y && y < SCREEN_HEIGHT ) {
                    
                    if ( size < 50 ) {
                        size += 0.75;
                    }
                    
                    for ( int i = -size / 2; i <= size / 2; i++ ) {
                        SDL_RenderDrawPoint(renderer, x + i, y + i);
                    }
                }
                
            }
        } else {
            size -= 0.35;

            if ( size > 0 ) {
                for ( int i = -size / 2; i <= size / 2; i++ ) {
                        SDL_RenderDrawPoint(renderer, x, y + i);
                }
            } else {
                size = 0;
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}