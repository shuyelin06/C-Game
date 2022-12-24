#pragma once

#include <SDL2/SDL.h>

#include "../main/game.h"

/*
    Graphics
*/

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 500

#define PIXELS_PER_UNIT 5

void render(SDL_Renderer *renderer, Game *game);