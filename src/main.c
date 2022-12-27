#include <stdio.h>

#include <components/game.h>

#include <rendering/graphics.h>
#include <physics/physics.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv){
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    // Initialize Image Loader
    if(IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Error in image loading");
    }

    // Initialize Window
    SDL_Window *window = SDL_CreateWindow("Umong As", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 500, 0);
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

    // Initialize Game Graphics
    if ( initializeGraphics(renderer) == GRAPHICS_INIT_FAIL ) {
        printf("Graphics Initialization Fail \n");
        return 1;
    }

    // Capture Keyboard State
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    // Program Running
    SDL_bool running = SDL_TRUE;
    while(running == SDL_TRUE){
        // Game 
        Game *game = newGame();

        // Update Timing
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
            // Hitbox Rendering
            if ( keyboard[SDL_SCANCODE_B] ) {
                debug(renderer, game);
            }
            // Render All
            SDL_RenderPresent(renderer);
        }
        
        freeGame(game);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    destroyGraphics();

    SDL_Quit();

    return 0;
}