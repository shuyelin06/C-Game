#include "graphics.h"

static void drawBackground(SDL_Renderer *renderer);
static void drawBird(SDL_Renderer *renderer, struct Bird *bird);

void render(SDL_Renderer *renderer, struct Game *game) {
    // Draw Background
    drawBackground(renderer);
    
    // Draw Bird
    drawBird(renderer, &((*game)._bird));
    
    // Render All
    SDL_RenderPresent(renderer);
}

static void drawBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black Color
    SDL_RenderClear(renderer); // Black Screen
}

static void drawBird(SDL_Renderer *renderer, struct Bird *bird) {
    int x = (*bird)._x * PIXELS_PER_UNIT;
    int y = (*bird)._y * PIXELS_PER_UNIT;
    int width = ((*bird)._width * PIXELS_PER_UNIT) / 2;
    int height = ((*bird)._height * PIXELS_PER_UNIT) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White Color
    SDL_RenderDrawLine(renderer, 
        x - width, y - height, x - width, y + height);
    SDL_RenderDrawLine(renderer, 
        x - width, y + height, x + width, y + height);
    SDL_RenderDrawLine(renderer, 
        x + width, y + height, x + width, y - height);
    SDL_RenderDrawLine(renderer, 
        x + width, y - height, x - width, y - height);
}