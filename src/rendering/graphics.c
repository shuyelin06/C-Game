#include "graphics.h"

#include <stdio.h>

static void drawBackground(SDL_Renderer *renderer);
static void drawBird(SDL_Renderer *renderer, Bird *bird);
static void drawPipes(SDL_Renderer *renderer, struct Pipe *firstPipe);

void render(SDL_Renderer *renderer, Game *game) {
    // Draw Background
    drawBackground(renderer);

    // Draw Bird
    drawBird(renderer, game->_bird);
    
    // Draw Pipes
    drawPipes(renderer, game->_pipes->next);

    // Render All
    SDL_RenderPresent(renderer);
}

static void drawBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black Color
    SDL_RenderClear(renderer); // Black Screen
}

static void drawBird(SDL_Renderer *renderer, Bird *bird) {
    int x = bird->_x * PIXELS_PER_UNIT;
    int y = SCREEN_HEIGHT - bird->_y * PIXELS_PER_UNIT;
    int w = bird->_width * PIXELS_PER_UNIT / 2;
    int h = bird->_height * PIXELS_PER_UNIT / 2;  

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White Color
    SDL_RenderDrawLine(renderer, 
            x - w, y - h, x - w, y + h);
    SDL_RenderDrawLine(renderer, 
        x - w, y + h, x + w, y + h);
    SDL_RenderDrawLine(renderer, 
        x + w, y + h, x + w, y - h);
    SDL_RenderDrawLine(renderer, 
        x + w, y - h, x - w, y - h);
}

static void drawPipes(SDL_Renderer *renderer, struct Pipe *firstPipe) {
    struct Pipe *cur = firstPipe;

    while(cur) {
        int x = cur->_x * PIXELS_PER_UNIT;
        int pipeWidth = cur->_pipeWidth * PIXELS_PER_UNIT / 2;

        int gapY = SCREEN_HEIGHT - cur->_gapY * PIXELS_PER_UNIT;
        int gapHeight = cur->_gapHeight * PIXELS_PER_UNIT / 2;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White Color
        // Draw the Upper Pipe
        SDL_RenderDrawLine(renderer, 
            x - pipeWidth, 0, x - pipeWidth, gapY - gapHeight);
        SDL_RenderDrawLine(renderer, 
            x - pipeWidth, gapY - gapHeight, x + pipeWidth, gapY - gapHeight);
        SDL_RenderDrawLine(renderer, 
            x + pipeWidth, gapY - gapHeight, x + pipeWidth, 0);

        // Draw the Lower Pipe
        SDL_RenderDrawLine(renderer, 
            x - pipeWidth, SCREEN_HEIGHT, x - pipeWidth, gapY + gapHeight);
        SDL_RenderDrawLine(renderer, 
            x - pipeWidth, gapY + gapHeight, x + pipeWidth, gapY + gapHeight);
        SDL_RenderDrawLine(renderer, 
            x + pipeWidth, gapY + gapHeight, x + pipeWidth, SCREEN_HEIGHT);

        // Increment Pointer
        cur = cur->next;
    }
}