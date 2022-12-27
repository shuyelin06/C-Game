#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <settings.h>
#include <components/game.h>

/*
    Graphics
*/

#define GRAPHICS_INIT_FAIL 0

void render(SDL_Renderer *renderer, Game *game);
void debug(SDL_Renderer *renderer, Game *game);

int initializeGraphics(SDL_Renderer *renderer); 
void destroyGraphics();